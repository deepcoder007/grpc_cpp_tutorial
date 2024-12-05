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

#include "test_service.pb.h"
#include "test_service.grpc.pb.h"

using namespace test::app;
using namespace grpc;

class ManualServer final : public TestService::Service {
private:
    Status ProcessTick(ServerContext* sc, ServerReaderWriter<OrderRequest, OrderResponse>* stream) override {
        std::cout << "Received stream connection call from : " << sc->peer();
        stream->SendInitialMetadata();

        OrderResponse resp;
        while (1) {
            if (sc->IsCancelled()) {
                std::cout << " Server Context Cancelled, exiting ... ";
                return Status::CANCELLED;
            }
            if (not request_queue.empty()) {
                stream->Write(request_queue.front());
                request_queue.pop();
            }
            if (stream->Read(&resp)) {
                std::cout << resp.DebugString() << std::endl;
                std::cout << " resp ACK: " << resp.order_id();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return Status::OK;
    }
public:
    std::queue<OrderRequest> request_queue;
};


int main() {

    std::string server_address{"localhost:50051"};
    ManualServer service;

    OrderRequest req;

    /* OrderRequest mor; */
    {
        /* OrderRequest* new_req1 = mor.add_orders(); */
        /* new_req1->CopyFrom(req); */
        /* service.request_queue.push(mor); */
        OrderRequest new_req;
        new_req.set_order_id(1);
        new_req.set_client_id(2);
        service.request_queue.push(new_req);
    }
    {
        /* OrderRequest* new_req2 = mor.add_orders(); */
        /* new_req2->CopyFrom(req); */
        /* service.request_queue.push(mor); */
        OrderRequest new_req;
        new_req.set_order_id(3);
        new_req.set_client_id(4);
        service.request_queue.push(new_req);
    }
    {
        /* OrderRequest* new_req3 = mor.add_orders(); */
        /* new_req3->CopyFrom(req); */
        /* service.request_queue.push(mor); */
        OrderRequest new_req;
        new_req.set_order_id(5);
        new_req.set_client_id(6);
        service.request_queue.push(new_req);
    }

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server{builder.BuildAndStart()};
    server->Wait();

    return 0;
}
