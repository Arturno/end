#ifndef TX
#define TX
/**
 * @file transmitter.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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

/**
 * @brief 
 * 
 */
void transmitter();

#endif


