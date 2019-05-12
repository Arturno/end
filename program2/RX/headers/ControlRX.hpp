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
class ControlRX
{
    public: 
    int state;
    unsigned int counter;
    int packet_group;
    int packet_size;
    int position;

    ControlRX(int, int);
    void end_program();

};
void Control_RX(ControlRX &ctr, int &bitrate, int socket_);

#endif