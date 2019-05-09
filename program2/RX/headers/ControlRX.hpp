#ifndef CTX
#define CTX
/**
 * @file ControlRX.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <string.h>
#include <sys/socket.h>
using namespace std;

void ControlRX(int &stan, int &przeplywnosc, int socket_);

class SterowanieRX
/**
 * @brief 
 * 
 */
{
    public:
    int stan;
    int licznik;
    int polozenie;
    double stopa_bledow;

    /**
     * @brief Construct a new Sterowanie R X object
     * 
     */
    SterowanieRX(int );
};

#endif