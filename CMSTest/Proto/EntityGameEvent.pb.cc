// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: EntityGameEvent.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "EntityGameEvent.pb.h"

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

namespace gameevent {

namespace {

const ::google::protobuf::Descriptor* EntityGameEvent_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  EntityGameEvent_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* EntityGameEvent_EntityGameEventType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_EntityGameEvent_2eproto() {
  protobuf_AddDesc_EntityGameEvent_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "EntityGameEvent.proto");
  GOOGLE_CHECK(file != NULL);
  EntityGameEvent_descriptor_ = file->message_type(0);
  static const int EntityGameEvent_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EntityGameEvent, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EntityGameEvent, uuid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EntityGameEvent, entitytag_),
  };
  EntityGameEvent_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      EntityGameEvent_descriptor_,
      EntityGameEvent::default_instance_,
      EntityGameEvent_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EntityGameEvent, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(EntityGameEvent, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(EntityGameEvent));
  EntityGameEvent_EntityGameEventType_descriptor_ = EntityGameEvent_descriptor_->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_EntityGameEvent_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    EntityGameEvent_descriptor_, &EntityGameEvent::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_EntityGameEvent_2eproto() {
  delete EntityGameEvent::default_instance_;
  delete EntityGameEvent_reflection_;
}

void protobuf_AddDesc_EntityGameEvent_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025EntityGameEvent.proto\022\tgameevent\"\240\001\n\017E"
    "ntityGameEvent\022<\n\004type\030\001 \002(\0162..gameevent"
    ".EntityGameEvent.EntityGameEventType\022\014\n\004"
    "UUID\030\002 \001(\t\022\021\n\tentityTag\030\003 \002(\004\".\n\023EntityG"
    "ameEventType\022\n\n\006CREATE\020\000\022\013\n\007DESTROY\020\001", 197);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "EntityGameEvent.proto", &protobuf_RegisterTypes);
  EntityGameEvent::default_instance_ = new EntityGameEvent();
  EntityGameEvent::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_EntityGameEvent_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_EntityGameEvent_2eproto {
  StaticDescriptorInitializer_EntityGameEvent_2eproto() {
    protobuf_AddDesc_EntityGameEvent_2eproto();
  }
} static_descriptor_initializer_EntityGameEvent_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* EntityGameEvent_EntityGameEventType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EntityGameEvent_EntityGameEventType_descriptor_;
}
bool EntityGameEvent_EntityGameEventType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const EntityGameEvent_EntityGameEventType EntityGameEvent::CREATE;
const EntityGameEvent_EntityGameEventType EntityGameEvent::DESTROY;
const EntityGameEvent_EntityGameEventType EntityGameEvent::EntityGameEventType_MIN;
const EntityGameEvent_EntityGameEventType EntityGameEvent::EntityGameEventType_MAX;
const int EntityGameEvent::EntityGameEventType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int EntityGameEvent::kTypeFieldNumber;
const int EntityGameEvent::kUUIDFieldNumber;
const int EntityGameEvent::kEntityTagFieldNumber;
#endif  // !_MSC_VER

EntityGameEvent::EntityGameEvent()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void EntityGameEvent::InitAsDefaultInstance() {
}

EntityGameEvent::EntityGameEvent(const EntityGameEvent& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void EntityGameEvent::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0;
  uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  entitytag_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EntityGameEvent::~EntityGameEvent() {
  SharedDtor();
}

void EntityGameEvent::SharedDtor() {
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    delete uuid_;
  }
  if (this != default_instance_) {
  }
}

void EntityGameEvent::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* EntityGameEvent::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return EntityGameEvent_descriptor_;
}

const EntityGameEvent& EntityGameEvent::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_EntityGameEvent_2eproto();
  return *default_instance_;
}

EntityGameEvent* EntityGameEvent::default_instance_ = NULL;

EntityGameEvent* EntityGameEvent::New() const {
  return new EntityGameEvent;
}

void EntityGameEvent::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0;
    if (has_uuid()) {
      if (uuid_ != &::google::protobuf::internal::kEmptyString) {
        uuid_->clear();
      }
    }
    entitytag_ = GOOGLE_ULONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool EntityGameEvent::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .gameevent.EntityGameEvent.EntityGameEventType type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::gameevent::EntityGameEvent_EntityGameEventType_IsValid(value)) {
            set_type(static_cast< ::gameevent::EntityGameEvent_EntityGameEventType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_UUID;
        break;
      }

      // optional string UUID = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_UUID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_uuid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->uuid().data(), this->uuid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_entityTag;
        break;
      }

      // required uint64 entityTag = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_entityTag:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &entitytag_)));
          set_has_entitytag();
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

void EntityGameEvent::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .gameevent.EntityGameEvent.EntityGameEventType type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }

  // optional string UUID = 2;
  if (has_uuid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->uuid().data(), this->uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->uuid(), output);
  }

  // required uint64 entityTag = 3;
  if (has_entitytag()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->entitytag(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* EntityGameEvent::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .gameevent.EntityGameEvent.EntityGameEventType type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }

  // optional string UUID = 2;
  if (has_uuid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->uuid().data(), this->uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->uuid(), target);
  }

  // required uint64 entityTag = 3;
  if (has_entitytag()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->entitytag(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int EntityGameEvent::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .gameevent.EntityGameEvent.EntityGameEventType type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }

    // optional string UUID = 2;
    if (has_uuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->uuid());
    }

    // required uint64 entityTag = 3;
    if (has_entitytag()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->entitytag());
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

void EntityGameEvent::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const EntityGameEvent* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const EntityGameEvent*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void EntityGameEvent::MergeFrom(const EntityGameEvent& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_uuid()) {
      set_uuid(from.uuid());
    }
    if (from.has_entitytag()) {
      set_entitytag(from.entitytag());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void EntityGameEvent::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EntityGameEvent::CopyFrom(const EntityGameEvent& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EntityGameEvent::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000005) != 0x00000005) return false;

  return true;
}

void EntityGameEvent::Swap(EntityGameEvent* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(uuid_, other->uuid_);
    std::swap(entitytag_, other->entitytag_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata EntityGameEvent::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = EntityGameEvent_descriptor_;
  metadata.reflection = EntityGameEvent_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gameevent

// @@protoc_insertion_point(global_scope)