#include "stdafx.h"
#include "server.h"
#include "entity_system.h"
#include "prop_common.h"

extern "C" {
	ENL_EXPORT iserver* server_dll_init() {
		return new server();
	}

	ENL_EXPORT void server_dll_shutdown(iserver* p) {
		delete static_cast<server*>(p);
	}
}

void server::init() {
	std::flush(std::cout);
	PRINT("server::init");
	
	gpGlobals->curtime = 0;

	m_thread_logic = std::thread([&]() {
		std::flush(std::cout);
		PRINT_DBG("Starting logic thread");
		size_t ticks = 0;
		using timestep = std::chrono::duration<std::chrono::high_resolution_clock::rep, std::ratio<1, server_tickrate>>;
		auto next_tick = std::chrono::high_resolution_clock::now() + timestep(1);

		gpGlobals->pEntSys = new entity_system();

		// Create test entity

		c_base_prop* pEnt = (c_base_prop*)CreateEntityNoSpawn("prop_dynamic");
		pEnt->set_model("data/models/wolf.emf");
		pEnt->spawn();

		while (!m_shutdown) {
			gpGlobals->pEntSys->update_entities();
			gpGlobals->curtime += (1.f / server_tickrate);
			std::this_thread::sleep_until(next_tick);
			next_tick += timestep(1);
		}

		if(gpGlobals->pEntSys) delete gpGlobals->pEntSys;
		gpGlobals->pEntSys = nullptr;
	});
}

void server::shutdown() {
	if(m_thread_logic.joinable())
		m_thread_logic.join();
	if (gpGlobals->pEntSys) delete gpGlobals->pEntSys;
}