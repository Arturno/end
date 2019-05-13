#ifndef RCV
#define RCV
/**
 * @file receiving.hpp
 * @brief Plik z fukcjami do odbioru pakietów przesłanych za pomocą różnych protokołów
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
 * @brief Funkcja realizująca odbiór UDP
 * 
 * @param TX adres strony nadawczej
 * @param RX adres strony odbiorczej
 * @param packet_size rozmiar przesyłanego pakietu
 * @param counter liczba odebranych pakietów
 * @param state zmienna kontrolująca czy nadal nalezy odbirać pakiety
 * @param chk 
 */
void odbieranieUDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size ,unsigned int &counter, int &state, class CheckPackets &chk);
/**
 * @brief Funkcja realizująca odbiór UDP-Lite
 * 
 * @param TX adres strony nadawczej
 * @param RX adres strony odbiorczej
 * @param packet_size rozmiar przesyłanego pakietu
 * @param coverage kodowanie pakietu w %
 * @param counter liczba odebranych pakietów
 * @param state zmienna kontrolująca czy nadal nalezy odbirać pakiety
 */
void odbieranieUDPLite(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size, int coverage,unsigned int &counter, int &state);
/**
 * @brief 
 * 
 * @param TX adres strony nadawczej
 * @param RX adres strony odbiorczej
 * @param packet_size rozmiar przesyłanego pakietu
 * @param counter liczba odebranych pakietów
 * @param state zmienna kontrolująca czy nadal nalezy odbirać pakiety
 */
void odbieranieTCP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size,unsigned int &counter, int &state);

#endif 
