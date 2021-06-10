#pragma once

#include <vector>

#include <Common/IStorage.h>
#include <Common/OrderBook.h>

using namespace Common;
using namespace std;

namespace PlatformTest{
    namespace Mock{
        class StorageMockB : public IStorage {
            private:
            vector<OrderBook> orderBooks;
            public:
                void Start(const Configuration &config) override;
                void Stop() override;
                void SaveOrderBook(const OrderBook &orderBook) override;
                vector<OrderBook> GetAllOrderBooks();
        };

        void StorageMockB::Start(const Configuration &config){
            // When a fake storage starts, it does nothing.
        }

        void StorageMockB::Stop(){

        }

        void StorageMockB::SaveOrderBook(const OrderBook &orderBook){
            // Pretend to save to storage.
            orderBooks.push_back(orderBook);
        }

        vector<OrderBook> StorageMockB::GetAllOrderBooks(){
            // Query for verification
            return orderBooks;
        }
    }
}