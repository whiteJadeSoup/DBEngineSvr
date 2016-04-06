// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: offline_message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "offline_message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace IM {

namespace {

const ::google::protobuf::Descriptor* OfflineCach_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  OfflineCach_reflection_ = NULL;
const ::google::protobuf::Descriptor* OfflineMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  OfflineMessage_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_offline_5fmessage_2eproto() {
  protobuf_AddDesc_offline_5fmessage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "offline_message.proto");
  GOOGLE_CHECK(file != NULL);
  OfflineCach_descriptor_ = file->message_type(0);
  static const int OfflineCach_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineCach, user_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineCach, messages_),
  };
  OfflineCach_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      OfflineCach_descriptor_,
      OfflineCach::default_instance_,
      OfflineCach_offsets_,
      -1,
      -1,
      -1,
      sizeof(OfflineCach),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineCach, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineCach, _is_default_instance_));
  OfflineMessage_descriptor_ = file->message_type(1);
  static const int OfflineMessage_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineMessage, send_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineMessage, content_),
  };
  OfflineMessage_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      OfflineMessage_descriptor_,
      OfflineMessage::default_instance_,
      OfflineMessage_offsets_,
      -1,
      -1,
      -1,
      sizeof(OfflineMessage),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineMessage, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(OfflineMessage, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_offline_5fmessage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      OfflineCach_descriptor_, &OfflineCach::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      OfflineMessage_descriptor_, &OfflineMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_offline_5fmessage_2eproto() {
  delete OfflineCach::default_instance_;
  delete OfflineCach_reflection_;
  delete OfflineMessage::default_instance_;
  delete OfflineMessage_reflection_;
}

void protobuf_AddDesc_offline_5fmessage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025offline_message.proto\022\002IM\"D\n\013OfflineCa"
    "ch\022\017\n\007user_id\030\001 \001(\003\022$\n\010messages\030\002 \003(\0132\022."
    "IM.OfflineMessage\"2\n\016OfflineMessage\022\017\n\007s"
    "end_id\030\001 \001(\003\022\017\n\007content\030\002 \001(\tb\006proto3", 157);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "offline_message.proto", &protobuf_RegisterTypes);
  OfflineCach::default_instance_ = new OfflineCach();
  OfflineMessage::default_instance_ = new OfflineMessage();
  OfflineCach::default_instance_->InitAsDefaultInstance();
  OfflineMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_offline_5fmessage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_offline_5fmessage_2eproto {
  StaticDescriptorInitializer_offline_5fmessage_2eproto() {
    protobuf_AddDesc_offline_5fmessage_2eproto();
  }
} static_descriptor_initializer_offline_5fmessage_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int OfflineCach::kUserIdFieldNumber;
const int OfflineCach::kMessagesFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

OfflineCach::OfflineCach()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:IM.OfflineCach)
}

void OfflineCach::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

OfflineCach::OfflineCach(const OfflineCach& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:IM.OfflineCach)
}

void OfflineCach::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  user_id_ = GOOGLE_LONGLONG(0);
}

OfflineCach::~OfflineCach() {
  // @@protoc_insertion_point(destructor:IM.OfflineCach)
  SharedDtor();
}

void OfflineCach::SharedDtor() {
  if (this != default_instance_) {
  }
}

void OfflineCach::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* OfflineCach::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OfflineCach_descriptor_;
}

const OfflineCach& OfflineCach::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_offline_5fmessage_2eproto();
  return *default_instance_;
}

OfflineCach* OfflineCach::default_instance_ = NULL;

OfflineCach* OfflineCach::New(::google::protobuf::Arena* arena) const {
  OfflineCach* n = new OfflineCach;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void OfflineCach::Clear() {
  user_id_ = GOOGLE_LONGLONG(0);
  messages_.Clear();
}

bool OfflineCach::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:IM.OfflineCach)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 user_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &user_id_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_messages;
        break;
      }

      // repeated .IM.OfflineMessage messages = 2;
      case 2: {
        if (tag == 18) {
         parse_messages:
          DO_(input->IncrementRecursionDepth());
         parse_loop_messages:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_messages()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_loop_messages;
        input->UnsafeDecrementRecursionDepth();
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:IM.OfflineCach)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:IM.OfflineCach)
  return false;
#undef DO_
}

void OfflineCach::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:IM.OfflineCach)
  // optional int64 user_id = 1;
  if (this->user_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->user_id(), output);
  }

  // repeated .IM.OfflineMessage messages = 2;
  for (unsigned int i = 0, n = this->messages_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->messages(i), output);
  }

  // @@protoc_insertion_point(serialize_end:IM.OfflineCach)
}

::google::protobuf::uint8* OfflineCach::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:IM.OfflineCach)
  // optional int64 user_id = 1;
  if (this->user_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->user_id(), target);
  }

  // repeated .IM.OfflineMessage messages = 2;
  for (unsigned int i = 0, n = this->messages_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->messages(i), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:IM.OfflineCach)
  return target;
}

int OfflineCach::ByteSize() const {
  int total_size = 0;

  // optional int64 user_id = 1;
  if (this->user_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->user_id());
  }

  // repeated .IM.OfflineMessage messages = 2;
  total_size += 1 * this->messages_size();
  for (int i = 0; i < this->messages_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->messages(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void OfflineCach::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const OfflineCach* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const OfflineCach>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void OfflineCach::MergeFrom(const OfflineCach& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  messages_.MergeFrom(from.messages_);
  if (from.user_id() != 0) {
    set_user_id(from.user_id());
  }
}

void OfflineCach::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OfflineCach::CopyFrom(const OfflineCach& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OfflineCach::IsInitialized() const {

  return true;
}

void OfflineCach::Swap(OfflineCach* other) {
  if (other == this) return;
  InternalSwap(other);
}
void OfflineCach::InternalSwap(OfflineCach* other) {
  std::swap(user_id_, other->user_id_);
  messages_.UnsafeArenaSwap(&other->messages_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata OfflineCach::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = OfflineCach_descriptor_;
  metadata.reflection = OfflineCach_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// OfflineCach

// optional int64 user_id = 1;
void OfflineCach::clear_user_id() {
  user_id_ = GOOGLE_LONGLONG(0);
}
 ::google::protobuf::int64 OfflineCach::user_id() const {
  // @@protoc_insertion_point(field_get:IM.OfflineCach.user_id)
  return user_id_;
}
 void OfflineCach::set_user_id(::google::protobuf::int64 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:IM.OfflineCach.user_id)
}

// repeated .IM.OfflineMessage messages = 2;
int OfflineCach::messages_size() const {
  return messages_.size();
}
void OfflineCach::clear_messages() {
  messages_.Clear();
}
const ::IM::OfflineMessage& OfflineCach::messages(int index) const {
  // @@protoc_insertion_point(field_get:IM.OfflineCach.messages)
  return messages_.Get(index);
}
::IM::OfflineMessage* OfflineCach::mutable_messages(int index) {
  // @@protoc_insertion_point(field_mutable:IM.OfflineCach.messages)
  return messages_.Mutable(index);
}
::IM::OfflineMessage* OfflineCach::add_messages() {
  // @@protoc_insertion_point(field_add:IM.OfflineCach.messages)
  return messages_.Add();
}
::google::protobuf::RepeatedPtrField< ::IM::OfflineMessage >*
OfflineCach::mutable_messages() {
  // @@protoc_insertion_point(field_mutable_list:IM.OfflineCach.messages)
  return &messages_;
}
const ::google::protobuf::RepeatedPtrField< ::IM::OfflineMessage >&
OfflineCach::messages() const {
  // @@protoc_insertion_point(field_list:IM.OfflineCach.messages)
  return messages_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int OfflineMessage::kSendIdFieldNumber;
const int OfflineMessage::kContentFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

OfflineMessage::OfflineMessage()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:IM.OfflineMessage)
}

void OfflineMessage::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

OfflineMessage::OfflineMessage(const OfflineMessage& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:IM.OfflineMessage)
}

void OfflineMessage::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  send_id_ = GOOGLE_LONGLONG(0);
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

OfflineMessage::~OfflineMessage() {
  // @@protoc_insertion_point(destructor:IM.OfflineMessage)
  SharedDtor();
}

void OfflineMessage::SharedDtor() {
  content_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void OfflineMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* OfflineMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return OfflineMessage_descriptor_;
}

const OfflineMessage& OfflineMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_offline_5fmessage_2eproto();
  return *default_instance_;
}

OfflineMessage* OfflineMessage::default_instance_ = NULL;

OfflineMessage* OfflineMessage::New(::google::protobuf::Arena* arena) const {
  OfflineMessage* n = new OfflineMessage;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void OfflineMessage::Clear() {
  send_id_ = GOOGLE_LONGLONG(0);
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool OfflineMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:IM.OfflineMessage)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 send_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &send_id_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_content;
        break;
      }

      // optional string content = 2;
      case 2: {
        if (tag == 18) {
         parse_content:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->content().data(), this->content().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "IM.OfflineMessage.content"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:IM.OfflineMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:IM.OfflineMessage)
  return false;
#undef DO_
}

void OfflineMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:IM.OfflineMessage)
  // optional int64 send_id = 1;
  if (this->send_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->send_id(), output);
  }

  // optional string content = 2;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "IM.OfflineMessage.content");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->content(), output);
  }

  // @@protoc_insertion_point(serialize_end:IM.OfflineMessage)
}

::google::protobuf::uint8* OfflineMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:IM.OfflineMessage)
  // optional int64 send_id = 1;
  if (this->send_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->send_id(), target);
  }

  // optional string content = 2;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), this->content().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "IM.OfflineMessage.content");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->content(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:IM.OfflineMessage)
  return target;
}

int OfflineMessage::ByteSize() const {
  int total_size = 0;

  // optional int64 send_id = 1;
  if (this->send_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->send_id());
  }

  // optional string content = 2;
  if (this->content().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->content());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void OfflineMessage::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const OfflineMessage* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const OfflineMessage>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void OfflineMessage::MergeFrom(const OfflineMessage& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from.send_id() != 0) {
    set_send_id(from.send_id());
  }
  if (from.content().size() > 0) {

    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
}

void OfflineMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OfflineMessage::CopyFrom(const OfflineMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OfflineMessage::IsInitialized() const {

  return true;
}

void OfflineMessage::Swap(OfflineMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void OfflineMessage::InternalSwap(OfflineMessage* other) {
  std::swap(send_id_, other->send_id_);
  content_.Swap(&other->content_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata OfflineMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = OfflineMessage_descriptor_;
  metadata.reflection = OfflineMessage_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// OfflineMessage

// optional int64 send_id = 1;
void OfflineMessage::clear_send_id() {
  send_id_ = GOOGLE_LONGLONG(0);
}
 ::google::protobuf::int64 OfflineMessage::send_id() const {
  // @@protoc_insertion_point(field_get:IM.OfflineMessage.send_id)
  return send_id_;
}
 void OfflineMessage::set_send_id(::google::protobuf::int64 value) {
  
  send_id_ = value;
  // @@protoc_insertion_point(field_set:IM.OfflineMessage.send_id)
}

// optional string content = 2;
void OfflineMessage::clear_content() {
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& OfflineMessage::content() const {
  // @@protoc_insertion_point(field_get:IM.OfflineMessage.content)
  return content_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void OfflineMessage::set_content(const ::std::string& value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IM.OfflineMessage.content)
}
 void OfflineMessage::set_content(const char* value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IM.OfflineMessage.content)
}
 void OfflineMessage::set_content(const char* value, size_t size) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IM.OfflineMessage.content)
}
 ::std::string* OfflineMessage::mutable_content() {
  
  // @@protoc_insertion_point(field_mutable:IM.OfflineMessage.content)
  return content_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* OfflineMessage::release_content() {
  
  return content_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void OfflineMessage::set_allocated_content(::std::string* content) {
  if (content != NULL) {
    
  } else {
    
  }
  content_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:IM.OfflineMessage.content)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace IM

// @@protoc_insertion_point(global_scope)