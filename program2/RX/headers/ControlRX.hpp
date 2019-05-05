#ifndef CTX
#define CTX

#include <iostream>
#include <string.h>
#include <sys/socket.h>
using namespace std;

void ControlRX(int &stan, int &przeplywnosc, int socket_);

class SterowanieRX
{
    public:
    int stan;
    int licznik;
    int polozenie;
    double stopa_bledow;


    SterowanieRX(int );
};

#endif