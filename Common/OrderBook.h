#pragma once

#include <string>
#include <vector>

// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace Common
{
    struct Quote{
        string Price;
        string Quantity;
    };

    struct OrderBook {
        string EventType;
        long int EventTime;
        string Symbol;
        long int FirstId;
        long int FinalId;
        vector<Quote> Asks;
        vector<Quote> Bids;

        string Serialize() const{
            json j;
            j["e"] = EventType;
            j["E"] = EventTime;
            j["s"] = Symbol;
            j["U"] = FirstId;
            j["u"] = FinalId;
            
            auto asks = json::array();
            for(auto &q : Asks){
                auto quote = json::array();
                quote.push_back(q.Price);
                quote.push_back(q.Quantity);
                asks.push_back(move(quote));
            }
            j["a"] = asks;

            auto bids = json::array();
            for(auto &q : Bids){
                auto quote = json::array();
                quote.push_back(q.Price);
                quote.push_back(q.Quantity);
                bids.push_back(move(quote));
            }
            j["b"] = bids;

            return j.dump();
        }

        void Deserialize(const string &jsonStr){
            auto j = json::parse(jsonStr);
            
            EventType = j["e"];
            EventTime = j["E"];
            Symbol = j["s"];
            FirstId = j["U"];
            FinalId = j["u"];

            for(auto & e : j["b"]){
                Quote q;
                int i = 0;
                for(auto &v : e){
                    if(i == 0){
                        q.Price = v;
                        i ++;
                    }
                    else{
                        q.Quantity = v;
                    }
                }

                Bids.push_back(move(q));
            }

            for(auto & e : j["a"]){
                Quote q;
                int i = 0;
                for(auto &v : e){
                    if(i == 0){
                        q.Price = v;
                        i ++;
                    }
                    else{
                        q.Quantity = v;
                    }
                }

                Asks.push_back(move(q));
            }
        }
    };
}