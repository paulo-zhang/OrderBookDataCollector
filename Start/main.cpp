#include <iostream>
#include "Platform.h"

using namespace std;
using namespace Start;

int main()
{
    cout <<"Hello main()." << endl;
    Platform p;
    p.Start();

    cout << "Press Esc Enter to exit.\n";
    while(cin.get() != '\e');

    p.Stop();
   return 0;
}