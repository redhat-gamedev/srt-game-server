// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RawInputCommandBuffer.proto

#ifndef PROTOBUF_RawInputCommandBuffer_2eproto__INCLUDED
#define PROTOBUF_RawInputCommandBuffer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "DualStickRawInputCommandBuffer.pb.h"
// @@protoc_insertion_point(includes)

namespace usx {
namespace geofactions {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_RawInputCommandBuffer_2eproto();
void protobuf_AssignDesc_RawInputCommandBuffer_2eproto();
void protobuf_ShutdownFile_RawInputCommandBuffer_2eproto();

class RawInputCommandBuffer;

enum RawInputCommandBuffer_RawInputCommandBufferType {
  RawInputCommandBuffer_RawInputCommandBufferType_DUALSTICK = 0
};
bool RawInputCommandBuffer_RawInputCommandBufferType_IsValid(int value);
const RawInputCommandBuffer_RawInputCommandBufferType RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_MIN = RawInputCommandBuffer_RawInputCommandBufferType_DUALSTICK;
const RawInputCommandBuffer_RawInputCommandBufferType RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_MAX = RawInputCommandBuffer_RawInputCommandBufferType_DUALSTICK;
const int RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_ARRAYSIZE = RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_MAX + 1;

const ::google::protobuf::EnumDescriptor* RawInputCommandBuffer_RawInputCommandBufferType_descriptor();
inline const ::std::string& RawInputCommandBuffer_RawInputCommandBufferType_Name(RawInputCommandBuffer_RawInputCommandBufferType value) {
  return ::google::protobuf::internal::NameOfEnum(
    RawInputCommandBuffer_RawInputCommandBufferType_descriptor(), value);
}
inline bool RawInputCommandBuffer_RawInputCommandBufferType_Parse(
    const ::std::string& name, RawInputCommandBuffer_RawInputCommandBufferType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RawInputCommandBuffer_RawInputCommandBufferType>(
    RawInputCommandBuffer_RawInputCommandBufferType_descriptor(), name, value);
}
// ===================================================================

class RawInputCommandBuffer : public ::google::protobuf::Message {
 public:
  RawInputCommandBuffer();
  virtual ~RawInputCommandBuffer();

  RawInputCommandBuffer(const RawInputCommandBuffer& from);

  inline RawInputCommandBuffer& operator=(const RawInputCommandBuffer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RawInputCommandBuffer& default_instance();

  void Swap(RawInputCommandBuffer* other);

  // implements Message ----------------------------------------------

  RawInputCommandBuffer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RawInputCommandBuffer& from);
  void MergeFrom(const RawInputCommandBuffer& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef RawInputCommandBuffer_RawInputCommandBufferType RawInputCommandBufferType;
  static const RawInputCommandBufferType DUALSTICK = RawInputCommandBuffer_RawInputCommandBufferType_DUALSTICK;
  static inline bool RawInputCommandBufferType_IsValid(int value) {
    return RawInputCommandBuffer_RawInputCommandBufferType_IsValid(value);
  }
  static const RawInputCommandBufferType RawInputCommandBufferType_MIN =
    RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_MIN;
  static const RawInputCommandBufferType RawInputCommandBufferType_MAX =
    RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_MAX;
  static const int RawInputCommandBufferType_ARRAYSIZE =
    RawInputCommandBuffer_RawInputCommandBufferType_RawInputCommandBufferType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  RawInputCommandBufferType_descriptor() {
    return RawInputCommandBuffer_RawInputCommandBufferType_descriptor();
  }
  static inline const ::std::string& RawInputCommandBufferType_Name(RawInputCommandBufferType value) {
    return RawInputCommandBuffer_RawInputCommandBufferType_Name(value);
  }
  static inline bool RawInputCommandBufferType_Parse(const ::std::string& name,
      RawInputCommandBufferType* value) {
    return RawInputCommandBuffer_RawInputCommandBufferType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .usx.geofactions.RawInputCommandBuffer.RawInputCommandBufferType type = 1 [default = DUALSTICK];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType type() const;
  inline void set_type(::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType value);

  // required string UUID = 2;
  inline bool has_uuid() const;
  inline void clear_uuid();
  static const int kUUIDFieldNumber = 2;
  inline const ::std::string& uuid() const;
  inline void set_uuid(const ::std::string& value);
  inline void set_uuid(const char* value);
  inline void set_uuid(const char* value, size_t size);
  inline ::std::string* mutable_uuid();
  inline ::std::string* release_uuid();
  inline void set_allocated_uuid(::std::string* uuid);

  // optional .usx.geofactions.DualStickRawInputCommandBuffer dualStickRawInputCommandBuffer = 3;
  inline bool has_dualstickrawinputcommandbuffer() const;
  inline void clear_dualstickrawinputcommandbuffer();
  static const int kDualStickRawInputCommandBufferFieldNumber = 3;
  inline const ::usx::geofactions::DualStickRawInputCommandBuffer& dualstickrawinputcommandbuffer() const;
  inline ::usx::geofactions::DualStickRawInputCommandBuffer* mutable_dualstickrawinputcommandbuffer();
  inline ::usx::geofactions::DualStickRawInputCommandBuffer* release_dualstickrawinputcommandbuffer();
  inline void set_allocated_dualstickrawinputcommandbuffer(::usx::geofactions::DualStickRawInputCommandBuffer* dualstickrawinputcommandbuffer);

  // @@protoc_insertion_point(class_scope:usx.geofactions.RawInputCommandBuffer)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_uuid();
  inline void clear_has_uuid();
  inline void set_has_dualstickrawinputcommandbuffer();
  inline void clear_has_dualstickrawinputcommandbuffer();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* uuid_;
  ::usx::geofactions::DualStickRawInputCommandBuffer* dualstickrawinputcommandbuffer_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_RawInputCommandBuffer_2eproto();
  friend void protobuf_AssignDesc_RawInputCommandBuffer_2eproto();
  friend void protobuf_ShutdownFile_RawInputCommandBuffer_2eproto();

  void InitAsDefaultInstance();
  static RawInputCommandBuffer* default_instance_;
};
// ===================================================================


// ===================================================================

// RawInputCommandBuffer

// required .usx.geofactions.RawInputCommandBuffer.RawInputCommandBufferType type = 1 [default = DUALSTICK];
inline bool RawInputCommandBuffer::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RawInputCommandBuffer::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RawInputCommandBuffer::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RawInputCommandBuffer::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType RawInputCommandBuffer::type() const {
  return static_cast< ::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType >(type_);
}
inline void RawInputCommandBuffer::set_type(::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType value) {
  assert(::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType_IsValid(value));
  set_has_type();
  type_ = value;
}

// required string UUID = 2;
inline bool RawInputCommandBuffer::has_uuid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RawInputCommandBuffer::set_has_uuid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RawInputCommandBuffer::clear_has_uuid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RawInputCommandBuffer::clear_uuid() {
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    uuid_->clear();
  }
  clear_has_uuid();
}
inline const ::std::string& RawInputCommandBuffer::uuid() const {
  return *uuid_;
}
inline void RawInputCommandBuffer::set_uuid(const ::std::string& value) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(value);
}
inline void RawInputCommandBuffer::set_uuid(const char* value) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(value);
}
inline void RawInputCommandBuffer::set_uuid(const char* value, size_t size) {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  uuid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RawInputCommandBuffer::mutable_uuid() {
  set_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    uuid_ = new ::std::string;
  }
  return uuid_;
}
inline ::std::string* RawInputCommandBuffer::release_uuid() {
  clear_has_uuid();
  if (uuid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = uuid_;
    uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void RawInputCommandBuffer::set_allocated_uuid(::std::string* uuid) {
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    delete uuid_;
  }
  if (uuid) {
    set_has_uuid();
    uuid_ = uuid;
  } else {
    clear_has_uuid();
    uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .usx.geofactions.DualStickRawInputCommandBuffer dualStickRawInputCommandBuffer = 3;
inline bool RawInputCommandBuffer::has_dualstickrawinputcommandbuffer() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RawInputCommandBuffer::set_has_dualstickrawinputcommandbuffer() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RawInputCommandBuffer::clear_has_dualstickrawinputcommandbuffer() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RawInputCommandBuffer::clear_dualstickrawinputcommandbuffer() {
  if (dualstickrawinputcommandbuffer_ != NULL) dualstickrawinputcommandbuffer_->::usx::geofactions::DualStickRawInputCommandBuffer::Clear();
  clear_has_dualstickrawinputcommandbuffer();
}
inline const ::usx::geofactions::DualStickRawInputCommandBuffer& RawInputCommandBuffer::dualstickrawinputcommandbuffer() const {
  return dualstickrawinputcommandbuffer_ != NULL ? *dualstickrawinputcommandbuffer_ : *default_instance_->dualstickrawinputcommandbuffer_;
}
inline ::usx::geofactions::DualStickRawInputCommandBuffer* RawInputCommandBuffer::mutable_dualstickrawinputcommandbuffer() {
  set_has_dualstickrawinputcommandbuffer();
  if (dualstickrawinputcommandbuffer_ == NULL) dualstickrawinputcommandbuffer_ = new ::usx::geofactions::DualStickRawInputCommandBuffer;
  return dualstickrawinputcommandbuffer_;
}
inline ::usx::geofactions::DualStickRawInputCommandBuffer* RawInputCommandBuffer::release_dualstickrawinputcommandbuffer() {
  clear_has_dualstickrawinputcommandbuffer();
  ::usx::geofactions::DualStickRawInputCommandBuffer* temp = dualstickrawinputcommandbuffer_;
  dualstickrawinputcommandbuffer_ = NULL;
  return temp;
}
inline void RawInputCommandBuffer::set_allocated_dualstickrawinputcommandbuffer(::usx::geofactions::DualStickRawInputCommandBuffer* dualstickrawinputcommandbuffer) {
  delete dualstickrawinputcommandbuffer_;
  dualstickrawinputcommandbuffer_ = dualstickrawinputcommandbuffer;
  if (dualstickrawinputcommandbuffer) {
    set_has_dualstickrawinputcommandbuffer();
  } else {
    clear_has_dualstickrawinputcommandbuffer();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace geofactions
}  // namespace usx

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType>() {
  return ::usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_RawInputCommandBuffer_2eproto__INCLUDED
