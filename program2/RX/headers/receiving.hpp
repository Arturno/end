#ifndef RCV
#define RCV

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

void odbieranieUDP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &licznik, int &stan, class CheckPackets &chk);
void odbieranieUDPLite(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int kodowanie, int &licznik, int &stan);
void odbieranieTCP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &licznik, int &stan);

#endif 