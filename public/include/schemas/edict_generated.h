// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_EDICT_SCHEMAS_NETWORKING_H_
#define FLATBUFFERS_GENERATED_EDICT_SCHEMAS_NETWORKING_H_

#include "flatbuffers/flatbuffers.h"

#include "base_generated.h"

namespace Schemas {
namespace Networking {

struct StringIdentifier;

struct EntityUpdate;

struct ConnectData;

struct MessageHeader;

enum EntityUpdateType {
  EntityUpdateType_NONE = 0,
  EntityUpdateType_CREATE = 1,
  EntityUpdateType_DELETE = 2,
  EntityUpdateType_POSITION = 3,
  EntityUpdateType_ROTATION = 4,
  EntityUpdateType_MODEL_FILENAME = 5,
  EntityUpdateType_CLASSNAME = 6,
  EntityUpdateType_MIN = EntityUpdateType_NONE,
  EntityUpdateType_MAX = EntityUpdateType_CLASSNAME
};

inline EntityUpdateType (&EnumValuesEntityUpdateType())[7] {
  static EntityUpdateType values[] = {
    EntityUpdateType_NONE,
    EntityUpdateType_CREATE,
    EntityUpdateType_DELETE,
    EntityUpdateType_POSITION,
    EntityUpdateType_ROTATION,
    EntityUpdateType_MODEL_FILENAME,
    EntityUpdateType_CLASSNAME
  };
  return values;
}

inline const char **EnumNamesEntityUpdateType() {
  static const char *names[] = {
    "NONE",
    "CREATE",
    "DELETE",
    "POSITION",
    "ROTATION",
    "MODEL_FILENAME",
    "CLASSNAME",
    nullptr
  };
  return names;
}

inline const char *EnumNameEntityUpdateType(EntityUpdateType e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesEntityUpdateType()[index];
}

enum EntityUpdateData {
  EntityUpdateData_NONE = 0,
  EntityUpdateData_Vector3 = 1,
  EntityUpdateData_Matrix4x4 = 2,
  EntityUpdateData_StringIdentifier = 3,
  EntityUpdateData_MIN = EntityUpdateData_NONE,
  EntityUpdateData_MAX = EntityUpdateData_StringIdentifier
};

inline EntityUpdateData (&EnumValuesEntityUpdateData())[4] {
  static EntityUpdateData values[] = {
    EntityUpdateData_NONE,
    EntityUpdateData_Vector3,
    EntityUpdateData_Matrix4x4,
    EntityUpdateData_StringIdentifier
  };
  return values;
}

inline const char **EnumNamesEntityUpdateData() {
  static const char *names[] = {
    "NONE",
    "Vector3",
    "Matrix4x4",
    "StringIdentifier",
    nullptr
  };
  return names;
}

inline const char *EnumNameEntityUpdateData(EntityUpdateData e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesEntityUpdateData()[index];
}

template<typename T> struct EntityUpdateDataTraits {
  static const EntityUpdateData enum_value = EntityUpdateData_NONE;
};

template<> struct EntityUpdateDataTraits<Schemas::Vector3> {
  static const EntityUpdateData enum_value = EntityUpdateData_Vector3;
};

template<> struct EntityUpdateDataTraits<Schemas::Matrix4x4> {
  static const EntityUpdateData enum_value = EntityUpdateData_Matrix4x4;
};

template<> struct EntityUpdateDataTraits<StringIdentifier> {
  static const EntityUpdateData enum_value = EntityUpdateData_StringIdentifier;
};

bool VerifyEntityUpdateData(flatbuffers::Verifier &verifier, const void *obj, EntityUpdateData type);
bool VerifyEntityUpdateDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

enum MessageType {
  MessageType_NONE = 0,
  MessageType_CONNECT = 1,
  MessageType_CONNECT_ACK = 2,
  MessageType_CONNECT_NAK = 3,
  MessageType_DISCONNECT = 4,
  MessageType_DISCOVERY_PROBE = 5,
  MessageType_DISCOVERY_RESPONSE = 6,
  MessageType_ENTITY_UPDATE = 7,
  MessageType_CLIENT_UPDATE = 8,
  MessageType_MIN = MessageType_NONE,
  MessageType_MAX = MessageType_CLIENT_UPDATE
};

inline MessageType (&EnumValuesMessageType())[9] {
  static MessageType values[] = {
    MessageType_NONE,
    MessageType_CONNECT,
    MessageType_CONNECT_ACK,
    MessageType_CONNECT_NAK,
    MessageType_DISCONNECT,
    MessageType_DISCOVERY_PROBE,
    MessageType_DISCOVERY_RESPONSE,
    MessageType_ENTITY_UPDATE,
    MessageType_CLIENT_UPDATE
  };
  return values;
}

inline const char **EnumNamesMessageType() {
  static const char *names[] = {
    "NONE",
    "CONNECT",
    "CONNECT_ACK",
    "CONNECT_NAK",
    "DISCONNECT",
    "DISCOVERY_PROBE",
    "DISCOVERY_RESPONSE",
    "ENTITY_UPDATE",
    "CLIENT_UPDATE",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessageType(MessageType e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesMessageType()[index];
}

enum ConnectionNakReason {
  ConnectionNakReason_RESERVED = 0,
  ConnectionNakReason_ALREADY_CONNECTED = 1,
  ConnectionNakReason_NAME_UNAVAILABLE = 2,
  ConnectionNakReason_FULL = 3,
  ConnectionNakReason_MIN = ConnectionNakReason_RESERVED,
  ConnectionNakReason_MAX = ConnectionNakReason_FULL
};

inline ConnectionNakReason (&EnumValuesConnectionNakReason())[4] {
  static ConnectionNakReason values[] = {
    ConnectionNakReason_RESERVED,
    ConnectionNakReason_ALREADY_CONNECTED,
    ConnectionNakReason_NAME_UNAVAILABLE,
    ConnectionNakReason_FULL
  };
  return values;
}

inline const char **EnumNamesConnectionNakReason() {
  static const char *names[] = {
    "RESERVED",
    "ALREADY_CONNECTED",
    "NAME_UNAVAILABLE",
    "FULL",
    nullptr
  };
  return names;
}

inline const char *EnumNameConnectionNakReason(ConnectionNakReason e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesConnectionNakReason()[index];
}

enum MessageData {
  MessageData_NONE = 0,
  MessageData_ConnectData = 1,
  MessageData_EntityUpdate = 2,
  MessageData_MIN = MessageData_NONE,
  MessageData_MAX = MessageData_EntityUpdate
};

inline MessageData (&EnumValuesMessageData())[3] {
  static MessageData values[] = {
    MessageData_NONE,
    MessageData_ConnectData,
    MessageData_EntityUpdate
  };
  return values;
}

inline const char **EnumNamesMessageData() {
  static const char *names[] = {
    "NONE",
    "ConnectData",
    "EntityUpdate",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessageData(MessageData e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesMessageData()[index];
}

template<typename T> struct MessageDataTraits {
  static const MessageData enum_value = MessageData_NONE;
};

template<> struct MessageDataTraits<ConnectData> {
  static const MessageData enum_value = MessageData_ConnectData;
};

template<> struct MessageDataTraits<EntityUpdate> {
  static const MessageData enum_value = MessageData_EntityUpdate;
};

bool VerifyMessageData(flatbuffers::Verifier &verifier, const void *obj, MessageData type);
bool VerifyMessageDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct StringIdentifier FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4
  };
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ID) &&
           verifier.Verify(id()) &&
           verifier.EndTable();
  }
};

struct StringIdentifierBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(StringIdentifier::VT_ID, id);
  }
  explicit StringIdentifierBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  StringIdentifierBuilder &operator=(const StringIdentifierBuilder &);
  flatbuffers::Offset<StringIdentifier> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<StringIdentifier>(end);
    return o;
  }
};

inline flatbuffers::Offset<StringIdentifier> CreateStringIdentifier(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> id = 0) {
  StringIdentifierBuilder builder_(_fbb);
  builder_.add_id(id);
  return builder_.Finish();
}

inline flatbuffers::Offset<StringIdentifier> CreateStringIdentifierDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *id = nullptr) {
  return Schemas::Networking::CreateStringIdentifier(
      _fbb,
      id ? _fbb.CreateString(id) : 0);
}

struct EntityUpdate FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_EDICT_ID = 4,
    VT_TYPE = 6,
    VT_DATA_TYPE = 8,
    VT_DATA = 10
  };
  uint64_t edict_id() const {
    return GetField<uint64_t>(VT_EDICT_ID, 0);
  }
  bool KeyCompareLessThan(const EntityUpdate *o) const {
    return edict_id() < o->edict_id();
  }
  int KeyCompareWithValue(uint64_t val) const {
    const auto key = edict_id();
    if (key < val) {
      return -1;
    } else if (key > val) {
      return 1;
    } else {
      return 0;
    }
  }
  EntityUpdateType type() const {
    return static_cast<EntityUpdateType>(GetField<uint16_t>(VT_TYPE, 0));
  }
  EntityUpdateData data_type() const {
    return static_cast<EntityUpdateData>(GetField<uint8_t>(VT_DATA_TYPE, 0));
  }
  const void *data() const {
    return GetPointer<const void *>(VT_DATA);
  }
  template<typename T> const T *data_as() const;
  const Schemas::Vector3 *data_as_Vector3() const {
    return data_type() == EntityUpdateData_Vector3 ? static_cast<const Schemas::Vector3 *>(data()) : nullptr;
  }
  const Schemas::Matrix4x4 *data_as_Matrix4x4() const {
    return data_type() == EntityUpdateData_Matrix4x4 ? static_cast<const Schemas::Matrix4x4 *>(data()) : nullptr;
  }
  const StringIdentifier *data_as_StringIdentifier() const {
    return data_type() == EntityUpdateData_StringIdentifier ? static_cast<const StringIdentifier *>(data()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_EDICT_ID) &&
           VerifyField<uint16_t>(verifier, VT_TYPE) &&
           VerifyField<uint8_t>(verifier, VT_DATA_TYPE) &&
           VerifyOffset(verifier, VT_DATA) &&
           VerifyEntityUpdateData(verifier, data(), data_type()) &&
           verifier.EndTable();
  }
};

template<> inline const Schemas::Vector3 *EntityUpdate::data_as<Schemas::Vector3>() const {
  return data_as_Vector3();
}

template<> inline const Schemas::Matrix4x4 *EntityUpdate::data_as<Schemas::Matrix4x4>() const {
  return data_as_Matrix4x4();
}

template<> inline const StringIdentifier *EntityUpdate::data_as<StringIdentifier>() const {
  return data_as_StringIdentifier();
}

struct EntityUpdateBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_edict_id(uint64_t edict_id) {
    fbb_.AddElement<uint64_t>(EntityUpdate::VT_EDICT_ID, edict_id, 0);
  }
  void add_type(EntityUpdateType type) {
    fbb_.AddElement<uint16_t>(EntityUpdate::VT_TYPE, static_cast<uint16_t>(type), 0);
  }
  void add_data_type(EntityUpdateData data_type) {
    fbb_.AddElement<uint8_t>(EntityUpdate::VT_DATA_TYPE, static_cast<uint8_t>(data_type), 0);
  }
  void add_data(flatbuffers::Offset<void> data) {
    fbb_.AddOffset(EntityUpdate::VT_DATA, data);
  }
  explicit EntityUpdateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  EntityUpdateBuilder &operator=(const EntityUpdateBuilder &);
  flatbuffers::Offset<EntityUpdate> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<EntityUpdate>(end);
    return o;
  }
};

inline flatbuffers::Offset<EntityUpdate> CreateEntityUpdate(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t edict_id = 0,
    EntityUpdateType type = EntityUpdateType_NONE,
    EntityUpdateData data_type = EntityUpdateData_NONE,
    flatbuffers::Offset<void> data = 0) {
  EntityUpdateBuilder builder_(_fbb);
  builder_.add_edict_id(edict_id);
  builder_.add_data(data);
  builder_.add_type(type);
  builder_.add_data_type(data_type);
  return builder_.Finish();
}

struct ConnectData FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_USERNAME = 4,
    VT_CONN_ID = 6,
    VT_NAK_REASON = 8
  };
  const flatbuffers::String *username() const {
    return GetPointer<const flatbuffers::String *>(VT_USERNAME);
  }
  uint64_t conn_id() const {
    return GetField<uint64_t>(VT_CONN_ID, 0);
  }
  ConnectionNakReason nak_reason() const {
    return static_cast<ConnectionNakReason>(GetField<int64_t>(VT_NAK_REASON, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.Verify(username()) &&
           VerifyField<uint64_t>(verifier, VT_CONN_ID) &&
           VerifyField<int64_t>(verifier, VT_NAK_REASON) &&
           verifier.EndTable();
  }
};

struct ConnectDataBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_username(flatbuffers::Offset<flatbuffers::String> username) {
    fbb_.AddOffset(ConnectData::VT_USERNAME, username);
  }
  void add_conn_id(uint64_t conn_id) {
    fbb_.AddElement<uint64_t>(ConnectData::VT_CONN_ID, conn_id, 0);
  }
  void add_nak_reason(ConnectionNakReason nak_reason) {
    fbb_.AddElement<int64_t>(ConnectData::VT_NAK_REASON, static_cast<int64_t>(nak_reason), 0);
  }
  explicit ConnectDataBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ConnectDataBuilder &operator=(const ConnectDataBuilder &);
  flatbuffers::Offset<ConnectData> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ConnectData>(end);
    return o;
  }
};

inline flatbuffers::Offset<ConnectData> CreateConnectData(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> username = 0,
    uint64_t conn_id = 0,
    ConnectionNakReason nak_reason = ConnectionNakReason_RESERVED) {
  ConnectDataBuilder builder_(_fbb);
  builder_.add_nak_reason(nak_reason);
  builder_.add_conn_id(conn_id);
  builder_.add_username(username);
  return builder_.Finish();
}

inline flatbuffers::Offset<ConnectData> CreateConnectDataDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *username = nullptr,
    uint64_t conn_id = 0,
    ConnectionNakReason nak_reason = ConnectionNakReason_RESERVED) {
  return Schemas::Networking::CreateConnectData(
      _fbb,
      username ? _fbb.CreateString(username) : 0,
      conn_id,
      nak_reason);
}

struct MessageHeader FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TYPE = 4,
    VT_DATA_TYPE = 6,
    VT_DATA = 8
  };
  MessageType type() const {
    return static_cast<MessageType>(GetField<int64_t>(VT_TYPE, 0));
  }
  MessageData data_type() const {
    return static_cast<MessageData>(GetField<uint8_t>(VT_DATA_TYPE, 0));
  }
  const void *data() const {
    return GetPointer<const void *>(VT_DATA);
  }
  template<typename T> const T *data_as() const;
  const ConnectData *data_as_ConnectData() const {
    return data_type() == MessageData_ConnectData ? static_cast<const ConnectData *>(data()) : nullptr;
  }
  const EntityUpdate *data_as_EntityUpdate() const {
    return data_type() == MessageData_EntityUpdate ? static_cast<const EntityUpdate *>(data()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_TYPE) &&
           VerifyField<uint8_t>(verifier, VT_DATA_TYPE) &&
           VerifyOffset(verifier, VT_DATA) &&
           VerifyMessageData(verifier, data(), data_type()) &&
           verifier.EndTable();
  }
};

template<> inline const ConnectData *MessageHeader::data_as<ConnectData>() const {
  return data_as_ConnectData();
}

template<> inline const EntityUpdate *MessageHeader::data_as<EntityUpdate>() const {
  return data_as_EntityUpdate();
}

struct MessageHeaderBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(MessageType type) {
    fbb_.AddElement<int64_t>(MessageHeader::VT_TYPE, static_cast<int64_t>(type), 0);
  }
  void add_data_type(MessageData data_type) {
    fbb_.AddElement<uint8_t>(MessageHeader::VT_DATA_TYPE, static_cast<uint8_t>(data_type), 0);
  }
  void add_data(flatbuffers::Offset<void> data) {
    fbb_.AddOffset(MessageHeader::VT_DATA, data);
  }
  explicit MessageHeaderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MessageHeaderBuilder &operator=(const MessageHeaderBuilder &);
  flatbuffers::Offset<MessageHeader> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<MessageHeader>(end);
    return o;
  }
};

inline flatbuffers::Offset<MessageHeader> CreateMessageHeader(
    flatbuffers::FlatBufferBuilder &_fbb,
    MessageType type = MessageType_NONE,
    MessageData data_type = MessageData_NONE,
    flatbuffers::Offset<void> data = 0) {
  MessageHeaderBuilder builder_(_fbb);
  builder_.add_type(type);
  builder_.add_data(data);
  builder_.add_data_type(data_type);
  return builder_.Finish();
}

inline bool VerifyEntityUpdateData(flatbuffers::Verifier &verifier, const void *obj, EntityUpdateData type) {
  switch (type) {
    case EntityUpdateData_NONE: {
      return true;
    }
    case EntityUpdateData_Vector3: {
      return true;
    }
    case EntityUpdateData_Matrix4x4: {
      auto ptr = reinterpret_cast<const Schemas::Matrix4x4 *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case EntityUpdateData_StringIdentifier: {
      auto ptr = reinterpret_cast<const StringIdentifier *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyEntityUpdateDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyEntityUpdateData(
        verifier,  values->Get(i), types->GetEnum<EntityUpdateData>(i))) {
      return false;
    }
  }
  return true;
}

inline bool VerifyMessageData(flatbuffers::Verifier &verifier, const void *obj, MessageData type) {
  switch (type) {
    case MessageData_NONE: {
      return true;
    }
    case MessageData_ConnectData: {
      auto ptr = reinterpret_cast<const ConnectData *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case MessageData_EntityUpdate: {
      auto ptr = reinterpret_cast<const EntityUpdate *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyMessageDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyMessageData(
        verifier,  values->Get(i), types->GetEnum<MessageData>(i))) {
      return false;
    }
  }
  return true;
}

inline const Schemas::Networking::MessageHeader *GetMessageHeader(const void *buf) {
  return flatbuffers::GetRoot<Schemas::Networking::MessageHeader>(buf);
}

inline const Schemas::Networking::MessageHeader *GetSizePrefixedMessageHeader(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Schemas::Networking::MessageHeader>(buf);
}

inline bool VerifyMessageHeaderBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Schemas::Networking::MessageHeader>(nullptr);
}

inline bool VerifySizePrefixedMessageHeaderBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Schemas::Networking::MessageHeader>(nullptr);
}

inline void FinishMessageHeaderBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Schemas::Networking::MessageHeader> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedMessageHeaderBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Schemas::Networking::MessageHeader> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Networking
}  // namespace Schemas

#endif  // FLATBUFFERS_GENERATED_EDICT_SCHEMAS_NETWORKING_H_
