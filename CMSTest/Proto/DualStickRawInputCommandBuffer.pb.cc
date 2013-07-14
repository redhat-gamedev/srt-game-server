// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DualStickRawInputCommandBuffer.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "DualStickRawInputCommandBuffer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace usx {
namespace geofactions {

namespace {

const ::google::protobuf::Descriptor* DualStickRawInputCommandBuffer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DualStickRawInputCommandBuffer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_DualStickRawInputCommandBuffer_2eproto() {
  protobuf_AddDesc_DualStickRawInputCommandBuffer_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "DualStickRawInputCommandBuffer.proto");
  GOOGLE_CHECK(file != NULL);
  DualStickRawInputCommandBuffer_descriptor_ = file->message_type(0);
  static const int DualStickRawInputCommandBuffer_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DualStickRawInputCommandBuffer, pbv2move_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DualStickRawInputCommandBuffer, pbv2shoot_),
  };
  DualStickRawInputCommandBuffer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DualStickRawInputCommandBuffer_descriptor_,
      DualStickRawInputCommandBuffer::default_instance_,
      DualStickRawInputCommandBuffer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DualStickRawInputCommandBuffer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DualStickRawInputCommandBuffer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DualStickRawInputCommandBuffer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_DualStickRawInputCommandBuffer_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DualStickRawInputCommandBuffer_descriptor_, &DualStickRawInputCommandBuffer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_DualStickRawInputCommandBuffer_2eproto() {
  delete DualStickRawInputCommandBuffer::default_instance_;
  delete DualStickRawInputCommandBuffer_reflection_;
}

void protobuf_AddDesc_DualStickRawInputCommandBuffer_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::box2d::protobuf_AddDesc_box2d_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n$DualStickRawInputCommandBuffer.proto\022\017"
    "usx.geofactions\032\013box2d.proto\"c\n\036DualStic"
    "kRawInputCommandBuffer\022\037\n\010pbv2Move\030\001 \002(\013"
    "2\r.box2d.PbVec2\022 \n\tpbv2Shoot\030\002 \002(\0132\r.box"
    "2d.PbVec2", 169);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "DualStickRawInputCommandBuffer.proto", &protobuf_RegisterTypes);
  DualStickRawInputCommandBuffer::default_instance_ = new DualStickRawInputCommandBuffer();
  DualStickRawInputCommandBuffer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_DualStickRawInputCommandBuffer_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_DualStickRawInputCommandBuffer_2eproto {
  StaticDescriptorInitializer_DualStickRawInputCommandBuffer_2eproto() {
    protobuf_AddDesc_DualStickRawInputCommandBuffer_2eproto();
  }
} static_descriptor_initializer_DualStickRawInputCommandBuffer_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DualStickRawInputCommandBuffer::kPbv2MoveFieldNumber;
const int DualStickRawInputCommandBuffer::kPbv2ShootFieldNumber;
#endif  // !_MSC_VER

DualStickRawInputCommandBuffer::DualStickRawInputCommandBuffer()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void DualStickRawInputCommandBuffer::InitAsDefaultInstance() {
  pbv2move_ = const_cast< ::box2d::PbVec2*>(&::box2d::PbVec2::default_instance());
  pbv2shoot_ = const_cast< ::box2d::PbVec2*>(&::box2d::PbVec2::default_instance());
}

DualStickRawInputCommandBuffer::DualStickRawInputCommandBuffer(const DualStickRawInputCommandBuffer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void DualStickRawInputCommandBuffer::SharedCtor() {
  _cached_size_ = 0;
  pbv2move_ = NULL;
  pbv2shoot_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DualStickRawInputCommandBuffer::~DualStickRawInputCommandBuffer() {
  SharedDtor();
}

void DualStickRawInputCommandBuffer::SharedDtor() {
  if (this != default_instance_) {
    delete pbv2move_;
    delete pbv2shoot_;
  }
}

void DualStickRawInputCommandBuffer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DualStickRawInputCommandBuffer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DualStickRawInputCommandBuffer_descriptor_;
}

const DualStickRawInputCommandBuffer& DualStickRawInputCommandBuffer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_DualStickRawInputCommandBuffer_2eproto();
  return *default_instance_;
}

DualStickRawInputCommandBuffer* DualStickRawInputCommandBuffer::default_instance_ = NULL;

DualStickRawInputCommandBuffer* DualStickRawInputCommandBuffer::New() const {
  return new DualStickRawInputCommandBuffer;
}

void DualStickRawInputCommandBuffer::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_pbv2move()) {
      if (pbv2move_ != NULL) pbv2move_->::box2d::PbVec2::Clear();
    }
    if (has_pbv2shoot()) {
      if (pbv2shoot_ != NULL) pbv2shoot_->::box2d::PbVec2::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DualStickRawInputCommandBuffer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .box2d.PbVec2 pbv2Move = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_pbv2move()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_pbv2Shoot;
        break;
      }

      // required .box2d.PbVec2 pbv2Shoot = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_pbv2Shoot:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_pbv2shoot()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void DualStickRawInputCommandBuffer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .box2d.PbVec2 pbv2Move = 1;
  if (has_pbv2move()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->pbv2move(), output);
  }

  // required .box2d.PbVec2 pbv2Shoot = 2;
  if (has_pbv2shoot()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->pbv2shoot(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* DualStickRawInputCommandBuffer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .box2d.PbVec2 pbv2Move = 1;
  if (has_pbv2move()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->pbv2move(), target);
  }

  // required .box2d.PbVec2 pbv2Shoot = 2;
  if (has_pbv2shoot()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->pbv2shoot(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int DualStickRawInputCommandBuffer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .box2d.PbVec2 pbv2Move = 1;
    if (has_pbv2move()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->pbv2move());
    }

    // required .box2d.PbVec2 pbv2Shoot = 2;
    if (has_pbv2shoot()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->pbv2shoot());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DualStickRawInputCommandBuffer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DualStickRawInputCommandBuffer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DualStickRawInputCommandBuffer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DualStickRawInputCommandBuffer::MergeFrom(const DualStickRawInputCommandBuffer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_pbv2move()) {
      mutable_pbv2move()->::box2d::PbVec2::MergeFrom(from.pbv2move());
    }
    if (from.has_pbv2shoot()) {
      mutable_pbv2shoot()->::box2d::PbVec2::MergeFrom(from.pbv2shoot());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DualStickRawInputCommandBuffer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DualStickRawInputCommandBuffer::CopyFrom(const DualStickRawInputCommandBuffer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DualStickRawInputCommandBuffer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_pbv2move()) {
    if (!this->pbv2move().IsInitialized()) return false;
  }
  if (has_pbv2shoot()) {
    if (!this->pbv2shoot().IsInitialized()) return false;
  }
  return true;
}

void DualStickRawInputCommandBuffer::Swap(DualStickRawInputCommandBuffer* other) {
  if (other != this) {
    std::swap(pbv2move_, other->pbv2move_);
    std::swap(pbv2shoot_, other->pbv2shoot_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DualStickRawInputCommandBuffer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DualStickRawInputCommandBuffer_descriptor_;
  metadata.reflection = DualStickRawInputCommandBuffer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace geofactions
}  // namespace usx

// @@protoc_insertion_point(global_scope)
