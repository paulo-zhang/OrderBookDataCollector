#pragma once

#include <string>
#include <vector>

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
        ulong EventTime;
        string Symbol;
        ulong FirstId;
        ulong FinalId;
        vector<Quote> Asks;
        vector<Quote> Bids;

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

                Bids.push_back(q);
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

                Asks.push_back(q);
            }
        }
    };
}