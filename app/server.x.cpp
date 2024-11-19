#include <iostream>
#include <memory>
#include <queue>

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
                // stream->write(request_queue.front());
                // request_queue.pop();
            }
            if (stream->Read(&resp)) {
                std::cout << resp.DebugString() << std::endl;
            }
            std::this_thread::sleep_for(std::chroni::milliseconds(1));
        }

        return Status::OK;
    }
};


int main() {

    std::string server_address{"localhost:50051"};
    ManualServer service;

    OrderRequest req;

    MultiOrderRequest mor;
    OrderRequest* new_req1 = mor.add_orders();
    OrderRequest* new_req2 = mor.add_orders();
    OrderRequest* new_req3 = mor.add_orders();
    new_req1->CopyFrom(req);
    new_req2->CopyFrom(req);
    new_req3->CopyFrom(req);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server{builder.BuildAndStart()};
    server->Wait();

    return 0;
}
