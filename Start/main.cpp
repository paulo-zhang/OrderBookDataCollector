#include <iostream>
#include "Platform.h"

using namespace std;
using namespace Start;

int main()
{
    cout <<"Hello main()." << endl;
    Platform p;
    p.Start();
    
    p.Stop();
   return 0;
}