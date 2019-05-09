#ifndef RCV
#define RCV
/**
 * @file receiving.hpp
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
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <thread>
#include "Check.hpp"
#define SOL_UDPLITE 136
#define UDPLITE_RECV_CSCOV 11
/**
 * @brief 
 * 
 * @param TX 
 * @param RX 
 * @param rozmiar_pakietu 
 * @param licznik 
 * @param stan 
 * @param chk 
 */
void odbieranieUDP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &licznik, int &stan, class CheckPackets &chk);
/**
 * @brief 
 * 
 * @param TX 
 * @param RX 
 * @param rozmiar_pakietu 
 * @param kodowanie 
 * @param licznik 
 * @param stan 
 */
void odbieranieUDPLite(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int kodowanie, int &licznik, int &stan);
/**
 * @brief 
 * 
 * @param TX 
 * @param RX 
 * @param rozmiar_pakietu 
 * @param licznik 
 * @param stan 
 */
void odbieranieTCP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &licznik, int &stan);

#endif 