#include <iostream>
#include "BinanceDataFeed.h"

using namespace std;

namespace DataFeeds
{
    namespace Binance
    {
        BinanceDataFeed::BinanceDataFeed() {

        }

        BinanceDataFeed::~BinanceDataFeed() {

        }
        
        void BinanceDataFeed::Start(string server){
            cout << "BinanceDataFeed::Start(" << server << ")" << endl;
        }

        void BinanceDataFeed::Stop(){
            cout << "BinanceDataFeed::Stop()"<<endl;
        }
    }
}