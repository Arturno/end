/**
 * @file measure.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <cstdio>
#include <fstream>

#include "ControlRX.hpp"
#include "Check.hpp"
using namespace std;
/**
 * @brief measure
 * 
 */
class Measure
{
    public:
    int position;
    int signal_level;
    int signal_quality;
    unsigned int received;
    unsigned int previously_received;
    double bitrate;
    double error;

    Measure();
    string getResult();
    void collectData(class ControlRX &ctr,class CheckPackets &chk);
    void getsignalinfo();
};

