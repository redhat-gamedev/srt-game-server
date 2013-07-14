// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommandBuffer.proto

#ifndef PROTOBUF_CommandBuffer_2eproto__INCLUDED
#define PROTOBUF_CommandBuffer_2eproto__INCLUDED

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
#include "SecurityCommandBuffer.pb.h"
// @@protoc_insertion_point(includes)

namespace usx {
namespace geofactions {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_CommandBuffer_2eproto();
void protobuf_AssignDesc_CommandBuffer_2eproto();
void protobuf_ShutdownFile_CommandBuffer_2eproto();

class CommandBuffer;

enum CommandBuffer_CommandBufferType {
  CommandBuffer_CommandBufferType_SECURITY = 0
};
bool CommandBuffer_CommandBufferType_IsValid(int value);
const CommandBuffer_CommandBufferType CommandBuffer_CommandBufferType_CommandBufferType_MIN = CommandBuffer_CommandBufferType_SECURITY;
const CommandBuffer_CommandBufferType CommandBuffer_CommandBufferType_CommandBufferType_MAX = CommandBuffer_CommandBufferType_SECURITY;
const int CommandBuffer_CommandBufferType_CommandBufferType_ARRAYSIZE = CommandBuffer_CommandBufferType_CommandBufferType_MAX + 1;

const ::google::protobuf::EnumDescriptor* CommandBuffer_CommandBufferType_descriptor();
inline const ::std::string& CommandBuffer_CommandBufferType_Name(CommandBuffer_CommandBufferType value) {
  return ::google::protobuf::internal::NameOfEnum(
    CommandBuffer_CommandBufferType_descriptor(), value);
}
inline bool CommandBuffer_CommandBufferType_Parse(
    const ::std::string& name, CommandBuffer_CommandBufferType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CommandBuffer_CommandBufferType>(
    CommandBuffer_CommandBufferType_descriptor(), name, value);
}
// ===================================================================

class CommandBuffer : public ::google::protobuf::Message {
 public:
  CommandBuffer();
  virtual ~CommandBuffer();

  CommandBuffer(const CommandBuffer& from);

  inline CommandBuffer& operator=(const CommandBuffer& from) {
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
  static const CommandBuffer& default_instance();

  void Swap(CommandBuffer* other);

  // implements Message ----------------------------------------------

  CommandBuffer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandBuffer& from);
  void MergeFrom(const CommandBuffer& from);
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

  typedef CommandBuffer_CommandBufferType CommandBufferType;
  static const CommandBufferType SECURITY = CommandBuffer_CommandBufferType_SECURITY;
  static inline bool CommandBufferType_IsValid(int value) {
    return CommandBuffer_CommandBufferType_IsValid(value);
  }
  static const CommandBufferType CommandBufferType_MIN =
    CommandBuffer_CommandBufferType_CommandBufferType_MIN;
  static const CommandBufferType CommandBufferType_MAX =
    CommandBuffer_CommandBufferType_CommandBufferType_MAX;
  static const int CommandBufferType_ARRAYSIZE =
    CommandBuffer_CommandBufferType_CommandBufferType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CommandBufferType_descriptor() {
    return CommandBuffer_CommandBufferType_descriptor();
  }
  static inline const ::std::string& CommandBufferType_Name(CommandBufferType value) {
    return CommandBuffer_CommandBufferType_Name(value);
  }
  static inline bool CommandBufferType_Parse(const ::std::string& name,
      CommandBufferType* value) {
    return CommandBuffer_CommandBufferType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .usx.geofactions.CommandBuffer.CommandBufferType type = 1 [default = SECURITY];
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::usx::geofactions::CommandBuffer_CommandBufferType type() const;
  inline void set_type(::usx::geofactions::CommandBuffer_CommandBufferType value);

  // optional .usx.geofactions.SecurityCommandBuffer securityCommandBuffer = 2;
  inline bool has_securitycommandbuffer() const;
  inline void clear_securitycommandbuffer();
  static const int kSecurityCommandBufferFieldNumber = 2;
  inline const ::usx::geofactions::SecurityCommandBuffer& securitycommandbuffer() const;
  inline ::usx::geofactions::SecurityCommandBuffer* mutable_securitycommandbuffer();
  inline ::usx::geofactions::SecurityCommandBuffer* release_securitycommandbuffer();
  inline void set_allocated_securitycommandbuffer(::usx::geofactions::SecurityCommandBuffer* securitycommandbuffer);

  // @@protoc_insertion_point(class_scope:usx.geofactions.CommandBuffer)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_securitycommandbuffer();
  inline void clear_has_securitycommandbuffer();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::usx::geofactions::SecurityCommandBuffer* securitycommandbuffer_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_CommandBuffer_2eproto();
  friend void protobuf_AssignDesc_CommandBuffer_2eproto();
  friend void protobuf_ShutdownFile_CommandBuffer_2eproto();

  void InitAsDefaultInstance();
  static CommandBuffer* default_instance_;
};
// ===================================================================


// ===================================================================

// CommandBuffer

// required .usx.geofactions.CommandBuffer.CommandBufferType type = 1 [default = SECURITY];
inline bool CommandBuffer::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandBuffer::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandBuffer::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandBuffer::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::usx::geofactions::CommandBuffer_CommandBufferType CommandBuffer::type() const {
  return static_cast< ::usx::geofactions::CommandBuffer_CommandBufferType >(type_);
}
inline void CommandBuffer::set_type(::usx::geofactions::CommandBuffer_CommandBufferType value) {
  assert(::usx::geofactions::CommandBuffer_CommandBufferType_IsValid(value));
  set_has_type();
  type_ = value;
}

// optional .usx.geofactions.SecurityCommandBuffer securityCommandBuffer = 2;
inline bool CommandBuffer::has_securitycommandbuffer() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommandBuffer::set_has_securitycommandbuffer() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommandBuffer::clear_has_securitycommandbuffer() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommandBuffer::clear_securitycommandbuffer() {
  if (securitycommandbuffer_ != NULL) securitycommandbuffer_->::usx::geofactions::SecurityCommandBuffer::Clear();
  clear_has_securitycommandbuffer();
}
inline const ::usx::geofactions::SecurityCommandBuffer& CommandBuffer::securitycommandbuffer() const {
  return securitycommandbuffer_ != NULL ? *securitycommandbuffer_ : *default_instance_->securitycommandbuffer_;
}
inline ::usx::geofactions::SecurityCommandBuffer* CommandBuffer::mutable_securitycommandbuffer() {
  set_has_securitycommandbuffer();
  if (securitycommandbuffer_ == NULL) securitycommandbuffer_ = new ::usx::geofactions::SecurityCommandBuffer;
  return securitycommandbuffer_;
}
inline ::usx::geofactions::SecurityCommandBuffer* CommandBuffer::release_securitycommandbuffer() {
  clear_has_securitycommandbuffer();
  ::usx::geofactions::SecurityCommandBuffer* temp = securitycommandbuffer_;
  securitycommandbuffer_ = NULL;
  return temp;
}
inline void CommandBuffer::set_allocated_securitycommandbuffer(::usx::geofactions::SecurityCommandBuffer* securitycommandbuffer) {
  delete securitycommandbuffer_;
  securitycommandbuffer_ = securitycommandbuffer;
  if (securitycommandbuffer) {
    set_has_securitycommandbuffer();
  } else {
    clear_has_securitycommandbuffer();
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace geofactions
}  // namespace usx

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::usx::geofactions::CommandBuffer_CommandBufferType>() {
  return ::usx::geofactions::CommandBuffer_CommandBufferType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CommandBuffer_2eproto__INCLUDED
