#ifndef CTX
#define CTX
/**
 * @file ControlTX.hpp
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
#include "../../TransmissionArrangement.hpp"

class Control
{
  public:
    int state;
    unsigned int counter;
    int delay;
    int to_send;
    int packet_group;
    int packet_size;
    /**
     * @brief Construct a new Control object
     * 
     */
    Control(int, int);
    /**
     * @brief 
     * 
     * @param bitrate 
     */
    void change_bitrate(int bitrate);
    /**
     * @brief 
     * 
     */
    void end_program();
};
/**
 * @brief 
 * 
 * @param state 
 * @param ctr 
 * @param socket_ 
 */
void ControlTX(int &state, class Control &ctr, int socket_);

#endif 