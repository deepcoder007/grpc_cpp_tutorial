#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <chrono>

/* #include <grpcpp/impl/codegen/completion_queue_impl.h> */
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/server_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpc/grpc.h>
#include <grpc/impl/codegen/connectivity_state.h>
#include <grpc/impl/codegen/gpr_types.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/channel.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/time.h>
#include <grpcpp/impl/codegen/client_callback.h>
// #include <grpcpp/impl/codegen/client_callback_impl.h>


#include "test_service.pb.h"
#include "test_service.grpc.pb.h"

using namespace test::app;
using namespace grpc;

class ManualOrderClient {
    /* class OrderProcessor : public grpc::experimental::ClientBidiReactor<OrderResponse, OrderRequest> { */
    class OrderProcessor : public grpc::ClientBidiReactor<OrderResponse, OrderRequest> {
        ManualOrderClient& m_parent;
        bool m_is_valid = false;

    public:
        explicit OrderProcessor(ManualOrderClient& parent) : m_parent{parent} {
        }

    public:
        void OnDone(const grpc::Status& status) override {
        }
        void OnReadInitialMetadataDone(bool ok) override {
        }
        void OnReadDone(bool ok) override {
            if (ok) {
                m_parent.clear_pending_action();
            }
        }
        void OnWriteDone(bool ok) override {
            if (ok) {
                m_parent.clear_pending_action();
            }
        }
        void OnWritesDoneDone(bool ok) override {
            if (ok) {
                m_parent.clear_pending_action();
            }
        }
    };
private:
    OrderProcessor m_async_processor;
    std::shared_ptr<grpc::Channel> m_grpc_channel;
    std::unique_ptr<TestService::Stub> m_stub;
    std::unique_ptr<grpc::ClientContext> m_grpc_context;
    bool m_action_pending = false;

public:
    explicit ManualOrderClient(const std::string& server_addr) 
        : m_async_processor{*this}
        , m_grpc_channel{grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials())}
        , m_stub{TestService::NewStub(m_grpc_channel)} {
        refresh_context(" ---- Message Stream Init ------ ");
    }
    ~ManualOrderClient() = default;

public:
    void refresh_context(const std::string& msg) {
        grpc_connectivity_state conn_state = m_grpc_channel->GetState(false);
        while (conn_state != GRPC_CHANNEL_READY) {
            conn_state = m_grpc_channel->GetState(true);
            std::cout << msg << std::endl;
            std::cout << "gRPC connectivity state: " << conn_state << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        m_grpc_context.reset();
        m_grpc_context = std::make_unique<grpc::ClientContext>();

        std::string x_api_key = "DUMMY";
        m_grpc_context.get()->AddMetadata("x-api-key", x_api_key);
        m_grpc_context.get()->AddMetadata("instance-id", "2");
        m_stub->experimental_async()->ProcessTick(m_grpc_context.get(), &m_async_processor);
        m_async_processor.StartCall();
    }
    bool is_ready() const {
        return m_grpc_channel->GetState(false) == GRPC_CHANNEL_READY;
    }
    bool read_msg(OrderRequest& msg) {
        if (m_action_pending) {
            return false;
        } else {
            m_async_processor.StartRead(&msg);
            m_action_pending = true;
            return true;
        }
    }
    bool write_msg(const OrderResponse& msg) {
        if (m_action_pending) {
            return false;
        } else {
            m_async_processor.StartWrite(&msg);
            m_action_pending = true;
            return true; 
        }
    }
    bool has_action_pending() const {
        return m_action_pending;
    }
    void clear_pending_action() {
        m_action_pending = false;
    }
};

int main() {
    
    ManualOrderClient client{"localhost:50051"};
    std::queue<OrderRequest> m_req_queue;

    while (1) {
        if (not client.is_ready()) {
            client.refresh_context(" fixing stream ----------");
        }
        OrderRequest order_req;
        client.read_msg(order_req);
        while (client.has_action_pending()) {
            std::this_thread::sleep_for(std::chrono::microseconds(300));
        }
        std::cout << " Read Order: " << order_req.order_id() << std::endl;
        m_req_queue.emplace(order_req);
        while (not m_req_queue.empty()) {
            OrderRequest& req = m_req_queue.front();
            m_req_queue.pop();
            std::cout << " req:" << req.client_id() << " : " << req.order_id() << std::endl;
            OrderResponse resp;
            resp.set_order_id(req.order_id());
            resp.set_client_id(req.client_id());
            client.write_msg(resp);
        }

    }


}
