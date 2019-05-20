/**
 * @file sendingPackets.hpp
 * @brief Plik zawierający funkcje realizujące wysyłanie pakietów
 * 
 */
#ifndef SEND
#define SEND_
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
#include "ControlTX.hpp"
#define SOL_UDPLITE 136
#define UDPLITE_SEND_CSCOV 10
/**
 * @brief Funkcja wysyłająca pakiety z użyciem protokołu UDP
 * 
 * @param TX_meas Struktura zawierająca dane o adresach strony nadawczej
 * @param RX_meas Struktura zawierająca dane o adresach strony odbiorczej
 * @param ctr obiekt klasy ControlTX przechowujący stan programu i aktualne parametry
 */
void send_UDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, ControlTX &ctr);

/**
 * @brief 
 * 
 * @param TX_meas Struktura zawierająca dane o adresach strony nadawczej
 * @param RX_meas Struktura zawierająca dane o adresach strony odbiorczej
 * @param coverage Kodowanie wysyłanych pakietów w %
 * @param ctr obiekt klasy ControlTX przechowujący stan programu i aktualne parametry 
 */
void send_UDPLite(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int coverage, ControlTX &ctr);

/**
 * @brief 
 * 
 * @param TX_meas Struktura zawierająca dane o adresach strony nadawczej
 * @param RX_meas Struktura zawierająca dane o adresach strony odbiorczej
 * @param ctr obiekt klasy ControlTX przechowujący stan programu i aktualne parametry 
 */
void send_TCP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, ControlTX &ctr);

#endif