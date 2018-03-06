// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MODEL_SCHEMAS_MODEL_H_
#define FLATBUFFERS_GENERATED_MODEL_SCHEMAS_MODEL_H_

#include "flatbuffers/flatbuffers.h"

#include "base_generated.h"

namespace Schemas {
namespace Model {

struct Vertex;

struct Triangle;

struct Bone;

struct BoneState;

struct Keyframe;

struct Animation;

struct Model;

struct Vertex FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_BONE = 4,
    VT_POS = 6,
    VT_NORMAL = 8,
    VT_U = 10,
    VT_V = 12
  };
  uint64_t bone() const {
    return GetField<uint64_t>(VT_BONE, 0);
  }
  const Schemas::Vector3 *pos() const {
    return GetStruct<const Schemas::Vector3 *>(VT_POS);
  }
  const Schemas::Vector3 *normal() const {
    return GetStruct<const Schemas::Vector3 *>(VT_NORMAL);
  }
  float u() const {
    return GetField<float>(VT_U, 0.0f);
  }
  float v() const {
    return GetField<float>(VT_V, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_BONE) &&
           VerifyField<Schemas::Vector3>(verifier, VT_POS) &&
           VerifyField<Schemas::Vector3>(verifier, VT_NORMAL) &&
           VerifyField<float>(verifier, VT_U) &&
           VerifyField<float>(verifier, VT_V) &&
           verifier.EndTable();
  }
};

struct VertexBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_bone(uint64_t bone) {
    fbb_.AddElement<uint64_t>(Vertex::VT_BONE, bone, 0);
  }
  void add_pos(const Schemas::Vector3 *pos) {
    fbb_.AddStruct(Vertex::VT_POS, pos);
  }
  void add_normal(const Schemas::Vector3 *normal) {
    fbb_.AddStruct(Vertex::VT_NORMAL, normal);
  }
  void add_u(float u) {
    fbb_.AddElement<float>(Vertex::VT_U, u, 0.0f);
  }
  void add_v(float v) {
    fbb_.AddElement<float>(Vertex::VT_V, v, 0.0f);
  }
  explicit VertexBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  VertexBuilder &operator=(const VertexBuilder &);
  flatbuffers::Offset<Vertex> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Vertex>(end);
    return o;
  }
};

inline flatbuffers::Offset<Vertex> CreateVertex(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t bone = 0,
    const Schemas::Vector3 *pos = 0,
    const Schemas::Vector3 *normal = 0,
    float u = 0.0f,
    float v = 0.0f) {
  VertexBuilder builder_(_fbb);
  builder_.add_bone(bone);
  builder_.add_v(v);
  builder_.add_u(u);
  builder_.add_normal(normal);
  builder_.add_pos(pos);
  return builder_.Finish();
}

struct Triangle FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_VERTICES = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<Vertex>> *vertices() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Vertex>> *>(VT_VERTICES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_VERTICES) &&
           verifier.Verify(vertices()) &&
           verifier.VerifyVectorOfTables(vertices()) &&
           verifier.EndTable();
  }
};

struct TriangleBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_vertices(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Vertex>>> vertices) {
    fbb_.AddOffset(Triangle::VT_VERTICES, vertices);
  }
  explicit TriangleBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TriangleBuilder &operator=(const TriangleBuilder &);
  flatbuffers::Offset<Triangle> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Triangle>(end);
    return o;
  }
};

inline flatbuffers::Offset<Triangle> CreateTriangle(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Vertex>>> vertices = 0) {
  TriangleBuilder builder_(_fbb);
  builder_.add_vertices(vertices);
  return builder_.Finish();
}

inline flatbuffers::Offset<Triangle> CreateTriangleDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<Vertex>> *vertices = nullptr) {
  return Schemas::Model::CreateTriangle(
      _fbb,
      vertices ? _fbb.CreateVector<flatbuffers::Offset<Vertex>>(*vertices) : 0);
}

struct Bone FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_PARENT = 6,
    VT_NAME = 8
  };
  uint64_t id() const {
    return GetField<uint64_t>(VT_ID, 0);
  }
  uint64_t parent() const {
    return GetField<uint64_t>(VT_PARENT, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_ID) &&
           VerifyField<uint64_t>(verifier, VT_PARENT) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.Verify(name()) &&
           verifier.EndTable();
  }
};

struct BoneBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint64_t id) {
    fbb_.AddElement<uint64_t>(Bone::VT_ID, id, 0);
  }
  void add_parent(uint64_t parent) {
    fbb_.AddElement<uint64_t>(Bone::VT_PARENT, parent, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Bone::VT_NAME, name);
  }
  explicit BoneBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BoneBuilder &operator=(const BoneBuilder &);
  flatbuffers::Offset<Bone> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Bone>(end);
    return o;
  }
};

inline flatbuffers::Offset<Bone> CreateBone(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t id = 0,
    uint64_t parent = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  BoneBuilder builder_(_fbb);
  builder_.add_parent(parent);
  builder_.add_id(id);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Bone> CreateBoneDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t id = 0,
    uint64_t parent = 0,
    const char *name = nullptr) {
  return Schemas::Model::CreateBone(
      _fbb,
      id,
      parent,
      name ? _fbb.CreateString(name) : 0);
}

struct BoneState FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_BONE = 4,
    VT_POS = 6,
    VT_ROT = 8
  };
  uint64_t bone() const {
    return GetField<uint64_t>(VT_BONE, 0);
  }
  const Schemas::Vector3 *pos() const {
    return GetStruct<const Schemas::Vector3 *>(VT_POS);
  }
  const Schemas::Vector3 *rot() const {
    return GetStruct<const Schemas::Vector3 *>(VT_ROT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_BONE) &&
           VerifyField<Schemas::Vector3>(verifier, VT_POS) &&
           VerifyField<Schemas::Vector3>(verifier, VT_ROT) &&
           verifier.EndTable();
  }
};

struct BoneStateBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_bone(uint64_t bone) {
    fbb_.AddElement<uint64_t>(BoneState::VT_BONE, bone, 0);
  }
  void add_pos(const Schemas::Vector3 *pos) {
    fbb_.AddStruct(BoneState::VT_POS, pos);
  }
  void add_rot(const Schemas::Vector3 *rot) {
    fbb_.AddStruct(BoneState::VT_ROT, rot);
  }
  explicit BoneStateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  BoneStateBuilder &operator=(const BoneStateBuilder &);
  flatbuffers::Offset<BoneState> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<BoneState>(end);
    return o;
  }
};

inline flatbuffers::Offset<BoneState> CreateBoneState(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t bone = 0,
    const Schemas::Vector3 *pos = 0,
    const Schemas::Vector3 *rot = 0) {
  BoneStateBuilder builder_(_fbb);
  builder_.add_bone(bone);
  builder_.add_rot(rot);
  builder_.add_pos(pos);
  return builder_.Finish();
}

struct Keyframe FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TIME = 4,
    VT_BONESTATES = 6
  };
  uint64_t time() const {
    return GetField<uint64_t>(VT_TIME, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<BoneState>> *bonestates() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<BoneState>> *>(VT_BONESTATES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TIME) &&
           VerifyOffset(verifier, VT_BONESTATES) &&
           verifier.Verify(bonestates()) &&
           verifier.VerifyVectorOfTables(bonestates()) &&
           verifier.EndTable();
  }
};

struct KeyframeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_time(uint64_t time) {
    fbb_.AddElement<uint64_t>(Keyframe::VT_TIME, time, 0);
  }
  void add_bonestates(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<BoneState>>> bonestates) {
    fbb_.AddOffset(Keyframe::VT_BONESTATES, bonestates);
  }
  explicit KeyframeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  KeyframeBuilder &operator=(const KeyframeBuilder &);
  flatbuffers::Offset<Keyframe> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Keyframe>(end);
    return o;
  }
};

inline flatbuffers::Offset<Keyframe> CreateKeyframe(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t time = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<BoneState>>> bonestates = 0) {
  KeyframeBuilder builder_(_fbb);
  builder_.add_time(time);
  builder_.add_bonestates(bonestates);
  return builder_.Finish();
}

inline flatbuffers::Offset<Keyframe> CreateKeyframeDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t time = 0,
    const std::vector<flatbuffers::Offset<BoneState>> *bonestates = nullptr) {
  return Schemas::Model::CreateKeyframe(
      _fbb,
      time,
      bonestates ? _fbb.CreateVector<flatbuffers::Offset<BoneState>>(*bonestates) : 0);
}

struct Animation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_NAME = 4,
    VT_KEYFRAMES = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Keyframe>> *keyframes() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Keyframe>> *>(VT_KEYFRAMES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.Verify(name()) &&
           VerifyOffset(verifier, VT_KEYFRAMES) &&
           verifier.Verify(keyframes()) &&
           verifier.VerifyVectorOfTables(keyframes()) &&
           verifier.EndTable();
  }
};

struct AnimationBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Animation::VT_NAME, name);
  }
  void add_keyframes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Keyframe>>> keyframes) {
    fbb_.AddOffset(Animation::VT_KEYFRAMES, keyframes);
  }
  explicit AnimationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AnimationBuilder &operator=(const AnimationBuilder &);
  flatbuffers::Offset<Animation> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Animation>(end);
    return o;
  }
};

inline flatbuffers::Offset<Animation> CreateAnimation(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Keyframe>>> keyframes = 0) {
  AnimationBuilder builder_(_fbb);
  builder_.add_keyframes(keyframes);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Animation> CreateAnimationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const std::vector<flatbuffers::Offset<Keyframe>> *keyframes = nullptr) {
  return Schemas::Model::CreateAnimation(
      _fbb,
      name ? _fbb.CreateString(name) : 0,
      keyframes ? _fbb.CreateVector<flatbuffers::Offset<Keyframe>>(*keyframes) : 0);
}

struct Model FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MATERIAL = 4,
    VT_FRAMERATE = 6,
    VT_TRIANGLES = 8,
    VT_SKELETON = 10,
    VT_ANIMATIONS = 12
  };
  const flatbuffers::String *material() const {
    return GetPointer<const flatbuffers::String *>(VT_MATERIAL);
  }
  int16_t framerate() const {
    return GetField<int16_t>(VT_FRAMERATE, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Triangle>> *triangles() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Triangle>> *>(VT_TRIANGLES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Bone>> *skeleton() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Bone>> *>(VT_SKELETON);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Animation>> *animations() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Animation>> *>(VT_ANIMATIONS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_MATERIAL) &&
           verifier.Verify(material()) &&
           VerifyField<int16_t>(verifier, VT_FRAMERATE) &&
           VerifyOffset(verifier, VT_TRIANGLES) &&
           verifier.Verify(triangles()) &&
           verifier.VerifyVectorOfTables(triangles()) &&
           VerifyOffset(verifier, VT_SKELETON) &&
           verifier.Verify(skeleton()) &&
           verifier.VerifyVectorOfTables(skeleton()) &&
           VerifyOffset(verifier, VT_ANIMATIONS) &&
           verifier.Verify(animations()) &&
           verifier.VerifyVectorOfTables(animations()) &&
           verifier.EndTable();
  }
};

struct ModelBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_material(flatbuffers::Offset<flatbuffers::String> material) {
    fbb_.AddOffset(Model::VT_MATERIAL, material);
  }
  void add_framerate(int16_t framerate) {
    fbb_.AddElement<int16_t>(Model::VT_FRAMERATE, framerate, 0);
  }
  void add_triangles(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Triangle>>> triangles) {
    fbb_.AddOffset(Model::VT_TRIANGLES, triangles);
  }
  void add_skeleton(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Bone>>> skeleton) {
    fbb_.AddOffset(Model::VT_SKELETON, skeleton);
  }
  void add_animations(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Animation>>> animations) {
    fbb_.AddOffset(Model::VT_ANIMATIONS, animations);
  }
  explicit ModelBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ModelBuilder &operator=(const ModelBuilder &);
  flatbuffers::Offset<Model> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Model>(end);
    return o;
  }
};

inline flatbuffers::Offset<Model> CreateModel(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> material = 0,
    int16_t framerate = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Triangle>>> triangles = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Bone>>> skeleton = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Animation>>> animations = 0) {
  ModelBuilder builder_(_fbb);
  builder_.add_animations(animations);
  builder_.add_skeleton(skeleton);
  builder_.add_triangles(triangles);
  builder_.add_material(material);
  builder_.add_framerate(framerate);
  return builder_.Finish();
}

inline flatbuffers::Offset<Model> CreateModelDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *material = nullptr,
    int16_t framerate = 0,
    const std::vector<flatbuffers::Offset<Triangle>> *triangles = nullptr,
    const std::vector<flatbuffers::Offset<Bone>> *skeleton = nullptr,
    const std::vector<flatbuffers::Offset<Animation>> *animations = nullptr) {
  return Schemas::Model::CreateModel(
      _fbb,
      material ? _fbb.CreateString(material) : 0,
      framerate,
      triangles ? _fbb.CreateVector<flatbuffers::Offset<Triangle>>(*triangles) : 0,
      skeleton ? _fbb.CreateVector<flatbuffers::Offset<Bone>>(*skeleton) : 0,
      animations ? _fbb.CreateVector<flatbuffers::Offset<Animation>>(*animations) : 0);
}

inline const Schemas::Model::Model *GetModel(const void *buf) {
  return flatbuffers::GetRoot<Schemas::Model::Model>(buf);
}

inline const Schemas::Model::Model *GetSizePrefixedModel(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Schemas::Model::Model>(buf);
}

inline bool VerifyModelBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Schemas::Model::Model>(nullptr);
}

inline bool VerifySizePrefixedModelBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Schemas::Model::Model>(nullptr);
}

inline void FinishModelBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Schemas::Model::Model> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedModelBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Schemas::Model::Model> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Model
}  // namespace Schemas

#endif  // FLATBUFFERS_GENERATED_MODEL_SCHEMAS_MODEL_H_
