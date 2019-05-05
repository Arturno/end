#ifndef TX
#define TX

#include <iostream>
#include <cstdio>
#include <stdlib.h>    // exit()
#include <string.h>    // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>
#include <thread>
#include "../../TransmissionArrangement.hpp"
#include "sendingPackets.hpp"
#include "adaptation.hpp"
#include "ControlTX.hpp"


void transmitter();

#endif


