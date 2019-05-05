#ifndef RX
#define RX

#include <iostream>
#include <cstdio>
#include <stdlib.h>    // exit()
#include <string.h>    // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>
#include <thread>
#include "../../TransmissionArrangement.hpp"
#include "receiving.hpp"
#include "savetofile.hpp"
#include "ControlRX.hpp"
#include "position.hpp"


void receiver();

#endif