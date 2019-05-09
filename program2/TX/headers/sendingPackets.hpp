#ifndef SEND_
#define SEND_
/**
 *  \file cos tam cos tam wysyłanie
 *  \details Wykorzystywana po stronie odbiorczej i nadawczej.
 *               Strona odbiorcza przesyła stronie nadawczej wymagania co do parametrów transmisji.
 */
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#define SOL_UDPLITE 136
#define UDPLITE_SEND_CSCOV 10

void send_UDP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &delay, int &packet_group, unsigned int &counter, int &state);
void send_UDPLite(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &delay, int &packet_group, int coverage, unsigned int &counter, int &state);
void send_TCP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int &delay, int &packet_group, unsigned int &counetr, int &state);

#endif