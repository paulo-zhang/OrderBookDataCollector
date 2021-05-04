#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace Start {
    class Configuration{
        public:
        string BinanceServer;
        string RedisServer;
        string MongoDBServer;

        string Serialize(){
            json j;
            j["BinanceServer"] = BinanceServer;
            j["RedisServer"] = RedisServer;
            j["MongoDBServer"] = MongoDBServer;

            return j.dump();
        }

        void Deserialize(string json){
            auto j = json::parse(json);
            BinanceServer = j["BinanceServer"];
            RedisServer = j["RedisServer"];
            MongoDBServer = j["MongoDBServer"];
        }
    };
}