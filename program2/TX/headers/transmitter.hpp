#ifndef TX
#define TX
/**
 * @file transmitter.hpp
 * @brief Plik przechowujący stronę nadawczą programu 
 * 
 */
#include <iostream>
#include <cstdio>
#include <stdlib.h>    
#include <string.h>    
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <thread>
#include "../../TransmissionArrangement.hpp"
#include "sendingPackets.hpp"
#include "adaptation.hpp"
#include "ControlTX.hpp"

/**
 * @brief Funkcja realizująca część nadawczą programu
 * 
 */
void transmitter();

#endif


