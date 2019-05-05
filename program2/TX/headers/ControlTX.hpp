#ifndef CTX
#define CTX

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

    Control(int, int);
    void change_bitrate(int bitrate);
    void end_program();
};

void ControlTX(int &state, class Control &ctr, int socket_);

#endif 