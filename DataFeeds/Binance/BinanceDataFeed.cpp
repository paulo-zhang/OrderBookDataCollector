#include <iostream>
#include "BinanceDataFeed.h"

using namespace std;

namespace DataFeeds
{
    namespace Binance
    {
        void BinanceDataFeed::Start(string server){
            cout << "Start(" << server << ")" << endl;
        }

        void BinanceDataFeed::Stop(){
            cout << "Stop()"<<endl;
        }
    }
}