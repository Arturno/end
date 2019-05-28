#ifndef TX
#define TX
/**
 * @file transmitter.hpp
 * @brief Plik zawierający stronę nadawczą programu transmitter()
 * 
 */
//#include <cstdio>
//#include <stdlib.h>    
//#include <string.h>    
//#include <arpa/inet.h> 
//#include <sys/socket.h>
#include <thread>
#include "../../TransmissionArrangement.hpp"
#include "sendingPackets.hpp"
#include "adaptation.hpp"
#include "ControlTX.hpp"

/**
 * @brief Strona nadawcza programu
 * 
 */
void transmitter();

#endif


