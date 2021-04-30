#include <string>

using namespace std;

namespace OrderBookCollector
{
    namespace Common
    {
        class IDataFeed{
            void Start(string server);
            void Stop();
        };
    }
}