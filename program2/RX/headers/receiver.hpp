#ifndef RX
#define RX
/**
 * @file receiver.hpp
 * @brief Plik zawierający część programu po stronie odbiorczej receiver()
 */
#include <cstdio>
#include <stdlib.h>    // exit()
#include <string.h>    // memset()
#include <arpa/inet.h> // inet_pton()
#include <sys/socket.h>
#include <thread>
#include "../../TransmissionArrangement.hpp"
#include "receivingPackets.hpp"
#include "savetofile.hpp"
#include "ControlRX.hpp"
#include "position.hpp"

/**
 * @brief Strona odbiorcza programu
 * @details fukcja realizująca część odbiorczą programu 
 *          odpowiada za komunikację z użytkownikiem, odbiór, pomiar i zapis danych do pliku
 * 
 */
void receiver();

#endif
