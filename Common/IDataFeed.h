#include <string>

using namespace std;

namespace Common
{
    class IDataFeed{
        virtual void Start(string server) = 0;
        virtual void Stop() = 0;
    };
}