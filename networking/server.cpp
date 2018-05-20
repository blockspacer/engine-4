#include "stdafx.h"
#include <net/server.h>
#include <thread>

net::server::server() : m_pCurTime(nullptr) {
	socket_t s;
	struct sockaddr_in server;
	int slen;
	WSADATA wsa;

	slen = sizeof(server);
#if defined(PLAT_WINDOWS)
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		PRINT_ERR("net::server::ctor: can't init WS: " << WSAGetLastError());
		return;
	}
#endif

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == invalid_socket) {
#if defined(PLAT_WINDOWS)
		PRINT_ERR("net::server::ctor: can't open socket: " << WSAGetLastError());
#elif defined(PLAT_LINUX)
		PRINT_ERR("net::server::ctor: can't open socket: " << strerror());
#endif
		return;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(net::port);

	if (bind(s, (sockaddr*)&server, slen) == net::socket_error) {
#if defined(PLAT_WINDOWS)
		PRINT_ERR("net::server::ctor: can't bind socket: " << WSAGetLastError());
#elif defined(PLAT_LINUX)
		PRINT_ERR("net::server::ctor: can't bind socket: " << strerror());
#endif
		close_socket(s);
		return;
	}

	m_socket = s;
	m_listening = true;

	add_handles(); // server_handles.cpp

	std::thread t([&]() {
		auto socket = get_socket();
		PRINT_DBG("net::server: receiver thread is running");
		while (true) {
			char buf[4096];
			int recv_len;
			sockaddr_in from;
			int slen = sizeof(from);

			if ((recv_len = recvfrom(socket, buf, 4096, 0, (sockaddr*)&from, &slen)) != net::socket_error) {
				char addrbuf[64];
				inet_ntop(AF_INET, &from.sin_addr, addrbuf, 64);
				//PRINT_DBG("net::server::thread: received " << recv_len << " bytes from " << addrbuf);
				auto verifier = flatbuffers::Verifier((const uint8_t*)buf, recv_len);
				if (Schemas::Networking::VerifyMessageHeaderBuffer(verifier)) {
					auto msghdr = Schemas::Networking::GetMessageHeader(buf);
					ASSERT(msghdr->Verify(verifier));

					auto msgtype = (*msghdr).type();

					if (m_handlers.count(msgtype)) {
						m_handlers[msgtype](from, *msghdr, recv_len);
					} else {
						PRINT_DBG("net::server::thread: unhandleable message type: " << Schemas::Networking::EnumNameMessageType(msgtype));
					}
				} else {
					PRINT_ERR("net::server: verify failed!");
				}
			}
		}
	});
	t.detach();
}

net::server::~server() {
	if (m_listening) {
		close_socket(m_socket);
	}
}

void net::server::on_connect() {

}

void net::server::update_state(const ent_id id, const edict_t & e) {
	edict_t& ed = m_edicts[id];
	if (!ed.active && e.active) {
		ed.active = true;
	}
	if (ed.active) {
		memcpy(&ed, &e, sizeof(edict_t));
		ed.updated = true;
	}
}

void net::server::unicast_update(const entity_update & upd, const net::client_desc & cd) {
	if (!cd.slot_active)
		return;

	flatbuffers::FlatBufferBuilder fbb;
	flatbuffers::Offset<flatbuffers::String> off_model;
	if (upd.model) {
		off_model = fbb.CreateString(upd.model);
	}
	Schemas::Vector3 pos(upd.pos[0], upd.pos[1], upd.pos[2]);
	Schemas::Vector3 rot(upd.rot[0], upd.rot[1], upd.rot[2]);
	Schemas::Networking::EntityUpdateBuilder eub(fbb);
	if (!off_model.IsNull())
		eub.add_model(off_model);
	eub.add_edict_id(upd.edict);
	eub.add_pos(&pos);
	eub.add_rot(&rot);
	auto off_upd = eub.Finish();

	Schemas::Networking::MessageHeaderBuilder mhb(fbb);
	mhb.add_type(Schemas::Networking::MessageType::MessageType_ENTITY_UPDATE);
	mhb.add_data_type(Schemas::Networking::MessageData::MessageData_EntityUpdate);
	mhb.add_data(off_upd.Union());

	Schemas::Networking::FinishMessageHeaderBuffer(fbb, mhb.Finish());

	send_to_client(cd.addr, fbb.GetBufferPointer(), fbb.GetSize());
}

void net::server::broadcast_update(const entity_update& upd) {
	flatbuffers::FlatBufferBuilder fbb;
	flatbuffers::Offset<flatbuffers::String> off_model;
	if (upd.model) {
		off_model = fbb.CreateString(upd.model);
	}
	Schemas::Vector3 pos(upd.pos[0], upd.pos[1], upd.pos[2]);
	Schemas::Vector3 rot(upd.rot[0], upd.rot[1], upd.rot[2]);
	Schemas::Networking::EntityUpdateBuilder eub(fbb);
	if (!off_model.IsNull())
		eub.add_model(off_model);
	eub.add_edict_id(upd.edict);
	eub.add_pos(&pos);
	eub.add_rot(&rot);
	if(m_pCurTime)
		eub.add_last_update(*m_pCurTime);
	else
		eub.add_last_update(0.f);
	auto off_upd = eub.Finish();

	Schemas::Networking::MessageHeaderBuilder mhb(fbb);
	mhb.add_type(Schemas::Networking::MessageType::MessageType_ENTITY_UPDATE);
	mhb.add_data_type(Schemas::Networking::MessageData::MessageData_EntityUpdate);
	mhb.add_data(off_upd.Union());

	Schemas::Networking::FinishMessageHeaderBuffer(fbb, mhb.Finish());

	for (const auto& client : m_clients) {
		if (client.slot_active)
			send_to_client(client.addr, fbb.GetBufferPointer(), fbb.GetSize());
	}
}

void net::server::send_to_client(const sockaddr_in & client, const void * pBuf, size_t nSiz) {
	size_t nSent = 0;
	if ((nSent = sendto(m_socket, (char*)pBuf, nSiz, 0, (sockaddr*)&client, sizeof(client))) == net::socket_error) {
#if defined(PLAT_WINDOWS)
		auto iErr = WSAGetLastError();
		char buf[256];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, iErr, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), buf, 256, NULL);
		PRINT_ERR("net::server::sendtoclient: (" << iErr << ") " << buf);
#endif
	}
	if (nSent != nSiz) {
		//PRINT_DBG("nSent=" << nSent << ", nSiz=" << nSiz);
	} else {
		//PRINT_DBG("net::server::send_to_client: sent " << nSent << " bytes");
	}
	ASSERT(nSent == nSiz);
}

net::client_desc * net::server::get_client_desc(const sockaddr_in& addr) {
	for (size_t i = 0; i < get_max_players(); i++) {
		net::client_desc& c = m_clients[i];
		if (!c.slot_active)
			continue;
		if (c.addr == addr)
			return &c;
	}
	return nullptr;
}

net::client_desc * net::server::get_client_desc(const std::string_view& username) {
	for (size_t i = 0; i < get_max_players(); i++) {
		net::client_desc& c = m_clients[i];
		if (!c.slot_active)
			continue;
		if (c.username == username)
			return &c;
	}
	return nullptr;
}

void net::server::push_updates() {
	size_t n = 0;
	for (size_t i = 0; i < net::max_edicts; i++) {
		edict_t& e = m_edicts[i];
		if (e.active && e.updated) {
			entity_update upd;
			upd.edict = i;
			upd.pos[0] = e.position[0]; upd.pos[1] = e.position[1]; upd.pos[2] = e.position[2];
			upd.rot[0] = e.rotation2[0]; upd.rot[1] = e.rotation2[1]; upd.rot[2] = e.rotation2[2];
			upd.model = e.modelname;

			broadcast_update(upd);
			e.updated = false;
			n++;
		}
	}
	//if(n)
	//	PRINT_DBG("net::server::push_updates: n=" << n);
}

void net::server::push_full_update(const net::client_desc& cd) {
	for (size_t i = 0; i < net::max_edicts; i++) {
		edict_t& e = m_edicts[i];
		if (e.active) {
			entity_update upd;
			upd.edict = i;
			upd.pos[0] = e.position[0]; upd.pos[1] = e.position[1]; upd.pos[2] = e.position[2];
			upd.rot[0] = e.rotation2[0]; upd.rot[1] = e.rotation2[1]; upd.rot[2] = e.rotation2[2];
			upd.model = e.modelname;

			unicast_update(upd, cd);
			e.updated = false;
		}
	}
	PRINT_DBG("net::server::push_full_update: updated " << cd.username);
}
