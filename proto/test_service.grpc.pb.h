// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: test_service.proto
#ifndef GRPC_test_5fservice_2eproto__INCLUDED
#define GRPC_test_5fservice_2eproto__INCLUDED

#include "test_service.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace test {
namespace app {

class TestService final {
 public:
  static constexpr char const* service_full_name() {
    return "test.app.TestService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>> ProcessTick(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>>(ProcessTickRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>> AsyncProcessTick(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>>(AsyncProcessTickRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>> PrepareAsyncProcessTick(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>>(PrepareAsyncProcessTickRaw(context, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void ProcessTick(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::test::app::OrderResponse,::test::app::OrderRequest>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>* ProcessTickRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>* AsyncProcessTickRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::test::app::OrderResponse, ::test::app::OrderRequest>* PrepareAsyncProcessTickRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>> ProcessTick(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>>(ProcessTickRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>> AsyncProcessTick(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>>(AsyncProcessTickRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>> PrepareAsyncProcessTick(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>>(PrepareAsyncProcessTickRaw(context, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void ProcessTick(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::test::app::OrderResponse,::test::app::OrderRequest>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>* ProcessTickRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>* AsyncProcessTickRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::test::app::OrderResponse, ::test::app::OrderRequest>* PrepareAsyncProcessTickRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_ProcessTick_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status ProcessTick(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_ProcessTick : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ProcessTick() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_ProcessTick() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ProcessTick(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestProcessTick(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_ProcessTick<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_ProcessTick : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ProcessTick() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::test::app::OrderResponse, ::test::app::OrderRequest>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->ProcessTick(context); }));
    }
    ~WithCallbackMethod_ProcessTick() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ProcessTick(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::test::app::OrderResponse, ::test::app::OrderRequest>* ProcessTick(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef WithCallbackMethod_ProcessTick<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_ProcessTick : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ProcessTick() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_ProcessTick() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ProcessTick(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_ProcessTick : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ProcessTick() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_ProcessTick() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ProcessTick(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestProcessTick(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ProcessTick : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ProcessTick() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context) { return this->ProcessTick(context); }));
    }
    ~WithRawCallbackMethod_ProcessTick() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ProcessTick(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::test::app::OrderRequest, ::test::app::OrderResponse>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* ProcessTick(
      ::grpc::CallbackServerContext* /*context*/)
      { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace app
}  // namespace test


#endif  // GRPC_test_5fservice_2eproto__INCLUDED
