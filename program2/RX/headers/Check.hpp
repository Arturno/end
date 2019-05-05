#ifndef CHK
#define CHK

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <limits.h>
#include <unistd.h>
#include "../../TransmissionArrangement.hpp"
using namespace std;

#define TABLE_SIZE 1000
#define MTU 1500

class CheckPackets
{
  public:
    char buffer[TABLE_SIZE][MTU] = {};

    int adding;
    int check;

    int packet_size;

    int added;
    int checked;
    int bit_errors;
    int lost;
    bool not_in_order;
    bool err;


    double bledybledy;
    int nrpakietu;
    //  int aktualny;
    CheckPackets();
    /*    void dod(int liczba);
    void kolejnosc();
    void spr();
    void wypisanie();

*/
    char *add();
    int spraw();
    double pomiar();
    void test();
};
void check(class CheckPackets &chk, int &state);
#endif
