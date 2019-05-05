#include <iostream>
#include "TX/headers/transmitter.hpp"
#include "RX/headers/receiver.hpp"

using namespace std;

int main()
{
    int i;
    cout<<"Program do pomiaru przepływności łącza Wifi"<<endl;
    cout<<"0 - aby uruchomić w trybie TX"<<endl;
    cout<<"1 - aby uruchomić w trybie RX"<<endl;
    cin>>i;
    if(i==0)
    {
        transmitter();
    }
    else
    {
        receiver();
    }

   return 0;
}