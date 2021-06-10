#pragma once

#include <vector>

#include <Common/IStorage.h>
#include <Common/OrderBook.h>

using namespace Common;
using namespace std;

namespace PlatformTest{
    namespace Mock{
        class StorageMockA : public IStorage {
            private:
            vector<OrderBook> orderBooks;
            public:
                void Start(const Configuration &config) override;
                void Stop() override;
                void SaveOrderBook(const OrderBook &orderBook) override;
                vector<OrderBook> GetAllOrderBooks();
        };

        void StorageMockA::Start(const Configuration &config){
            // When a fake storage starts, it does nothing.
        }

        void StorageMockA::Stop(){

        }

        void StorageMockA::SaveOrderBook(const OrderBook &orderBook){
            // Pretend to save to storage.
            orderBooks.push_back(orderBook);
        }

        vector<OrderBook> StorageMockA::GetAllOrderBooks(){
            // Query for verification
            return orderBooks;
        }
    }
}