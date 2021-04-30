#include <iostream>
#include <DataFeeds/Binance/BinanceDataFeed.h>

using namespace std;
using namespace DataFeeds::Binance;

int main()
{
    BinanceDataFeed feed;
    feed.Start("server from main");
    cout <<"Hello main()." << endl;
    feed.Stop();
   return 0;
}