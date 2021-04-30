#include <string>

using namespace std;

namespace OrderBookCollector
{
    namespace Common
    {
        class IStorage{
            void Start(string server);
            void Stop();
        };
    }
}