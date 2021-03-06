// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DualStickRawInputCommandBuffer.proto

#ifndef PROTOBUF_INCLUDED_DualStickRawInputCommandBuffer_2eproto
#define PROTOBUF_INCLUDED_DualStickRawInputCommandBuffer_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "box2d.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_DualStickRawInputCommandBuffer_2eproto 

namespace protobuf_DualStickRawInputCommandBuffer_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_DualStickRawInputCommandBuffer_2eproto
namespace redhatgamedev {
namespace srt {
class DualStickRawInputCommandBuffer;
class DualStickRawInputCommandBufferDefaultTypeInternal;
extern DualStickRawInputCommandBufferDefaultTypeInternal _DualStickRawInputCommandBuffer_default_instance_;
}  // namespace srt
}  // namespace redhatgamedev
namespace google {
namespace protobuf {
template<> ::redhatgamedev::srt::DualStickRawInputCommandBuffer* Arena::CreateMaybeMessage<::redhatgamedev::srt::DualStickRawInputCommandBuffer>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace redhatgamedev {
namespace srt {

// ===================================================================

class DualStickRawInputCommandBuffer : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:redhatgamedev.srt.DualStickRawInputCommandBuffer) */ {
 public:
  DualStickRawInputCommandBuffer();
  virtual ~DualStickRawInputCommandBuffer();

  DualStickRawInputCommandBuffer(const DualStickRawInputCommandBuffer& from);

  inline DualStickRawInputCommandBuffer& operator=(const DualStickRawInputCommandBuffer& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  DualStickRawInputCommandBuffer(DualStickRawInputCommandBuffer&& from) noexcept
    : DualStickRawInputCommandBuffer() {
    *this = ::std::move(from);
  }

  inline DualStickRawInputCommandBuffer& operator=(DualStickRawInputCommandBuffer&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DualStickRawInputCommandBuffer& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DualStickRawInputCommandBuffer* internal_default_instance() {
    return reinterpret_cast<const DualStickRawInputCommandBuffer*>(
               &_DualStickRawInputCommandBuffer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(DualStickRawInputCommandBuffer* other);
  friend void swap(DualStickRawInputCommandBuffer& a, DualStickRawInputCommandBuffer& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline DualStickRawInputCommandBuffer* New() const final {
    return CreateMaybeMessage<DualStickRawInputCommandBuffer>(NULL);
  }

  DualStickRawInputCommandBuffer* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<DualStickRawInputCommandBuffer>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const DualStickRawInputCommandBuffer& from);
  void MergeFrom(const DualStickRawInputCommandBuffer& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DualStickRawInputCommandBuffer* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .box2d.PbVec2 pbv2Move = 1;
  bool has_pbv2move() const;
  void clear_pbv2move();
  static const int kPbv2MoveFieldNumber = 1;
  private:
  const ::box2d::PbVec2& _internal_pbv2move() const;
  public:
  const ::box2d::PbVec2& pbv2move() const;
  ::box2d::PbVec2* release_pbv2move();
  ::box2d::PbVec2* mutable_pbv2move();
  void set_allocated_pbv2move(::box2d::PbVec2* pbv2move);

  // required .box2d.PbVec2 pbv2Shoot = 2;
  bool has_pbv2shoot() const;
  void clear_pbv2shoot();
  static const int kPbv2ShootFieldNumber = 2;
  private:
  const ::box2d::PbVec2& _internal_pbv2shoot() const;
  public:
  const ::box2d::PbVec2& pbv2shoot() const;
  ::box2d::PbVec2* release_pbv2shoot();
  ::box2d::PbVec2* mutable_pbv2shoot();
  void set_allocated_pbv2shoot(::box2d::PbVec2* pbv2shoot);

  // @@protoc_insertion_point(class_scope:redhatgamedev.srt.DualStickRawInputCommandBuffer)
 private:
  void set_has_pbv2move();
  void clear_has_pbv2move();
  void set_has_pbv2shoot();
  void clear_has_pbv2shoot();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::box2d::PbVec2* pbv2move_;
  ::box2d::PbVec2* pbv2shoot_;
  friend struct ::protobuf_DualStickRawInputCommandBuffer_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// DualStickRawInputCommandBuffer

// required .box2d.PbVec2 pbv2Move = 1;
inline bool DualStickRawInputCommandBuffer::has_pbv2move() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DualStickRawInputCommandBuffer::set_has_pbv2move() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DualStickRawInputCommandBuffer::clear_has_pbv2move() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::box2d::PbVec2& DualStickRawInputCommandBuffer::_internal_pbv2move() const {
  return *pbv2move_;
}
inline const ::box2d::PbVec2& DualStickRawInputCommandBuffer::pbv2move() const {
  const ::box2d::PbVec2* p = pbv2move_;
  // @@protoc_insertion_point(field_get:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Move)
  return p != NULL ? *p : *reinterpret_cast<const ::box2d::PbVec2*>(
      &::box2d::_PbVec2_default_instance_);
}
inline ::box2d::PbVec2* DualStickRawInputCommandBuffer::release_pbv2move() {
  // @@protoc_insertion_point(field_release:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Move)
  clear_has_pbv2move();
  ::box2d::PbVec2* temp = pbv2move_;
  pbv2move_ = NULL;
  return temp;
}
inline ::box2d::PbVec2* DualStickRawInputCommandBuffer::mutable_pbv2move() {
  set_has_pbv2move();
  if (pbv2move_ == NULL) {
    auto* p = CreateMaybeMessage<::box2d::PbVec2>(GetArenaNoVirtual());
    pbv2move_ = p;
  }
  // @@protoc_insertion_point(field_mutable:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Move)
  return pbv2move_;
}
inline void DualStickRawInputCommandBuffer::set_allocated_pbv2move(::box2d::PbVec2* pbv2move) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(pbv2move_);
  }
  if (pbv2move) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      pbv2move = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, pbv2move, submessage_arena);
    }
    set_has_pbv2move();
  } else {
    clear_has_pbv2move();
  }
  pbv2move_ = pbv2move;
  // @@protoc_insertion_point(field_set_allocated:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Move)
}

// required .box2d.PbVec2 pbv2Shoot = 2;
inline bool DualStickRawInputCommandBuffer::has_pbv2shoot() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DualStickRawInputCommandBuffer::set_has_pbv2shoot() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DualStickRawInputCommandBuffer::clear_has_pbv2shoot() {
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::box2d::PbVec2& DualStickRawInputCommandBuffer::_internal_pbv2shoot() const {
  return *pbv2shoot_;
}
inline const ::box2d::PbVec2& DualStickRawInputCommandBuffer::pbv2shoot() const {
  const ::box2d::PbVec2* p = pbv2shoot_;
  // @@protoc_insertion_point(field_get:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Shoot)
  return p != NULL ? *p : *reinterpret_cast<const ::box2d::PbVec2*>(
      &::box2d::_PbVec2_default_instance_);
}
inline ::box2d::PbVec2* DualStickRawInputCommandBuffer::release_pbv2shoot() {
  // @@protoc_insertion_point(field_release:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Shoot)
  clear_has_pbv2shoot();
  ::box2d::PbVec2* temp = pbv2shoot_;
  pbv2shoot_ = NULL;
  return temp;
}
inline ::box2d::PbVec2* DualStickRawInputCommandBuffer::mutable_pbv2shoot() {
  set_has_pbv2shoot();
  if (pbv2shoot_ == NULL) {
    auto* p = CreateMaybeMessage<::box2d::PbVec2>(GetArenaNoVirtual());
    pbv2shoot_ = p;
  }
  // @@protoc_insertion_point(field_mutable:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Shoot)
  return pbv2shoot_;
}
inline void DualStickRawInputCommandBuffer::set_allocated_pbv2shoot(::box2d::PbVec2* pbv2shoot) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(pbv2shoot_);
  }
  if (pbv2shoot) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      pbv2shoot = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, pbv2shoot, submessage_arena);
    }
    set_has_pbv2shoot();
  } else {
    clear_has_pbv2shoot();
  }
  pbv2shoot_ = pbv2shoot;
  // @@protoc_insertion_point(field_set_allocated:redhatgamedev.srt.DualStickRawInputCommandBuffer.pbv2Shoot)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace srt
}  // namespace redhatgamedev

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_DualStickRawInputCommandBuffer_2eproto
