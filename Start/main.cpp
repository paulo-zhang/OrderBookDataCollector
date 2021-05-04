#include <iostream>
#include "Platform.h"

using namespace std;
using namespace Start;

int main()
{
    cout <<"Hello main()." << endl;
    Platform p;
    p.Start();

    cout << "Press any key to continue.";
    char c;
    do{
        cin >> c;
    }while(c != '\e');

    p.Stop();
   return 0;
}