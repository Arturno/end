#ifndef TA_HH
#define TA_HH
/**
 * @file TransmissionArrangement.hpp
 * @author your name (you@domain.com)
 * @brief Parametry Transmisji
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctime>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

class TransmissionArrangement
/**
 *  \brief Klasa służąca do ustanowienia poczatkowych parametrow transmisji.
 *  \details Wykorzystywana po stronie odbiorczej i nadawczej.
 *               Strona odbiorcza przesyła stronie nadawczej wymagania co do parametrów transmisji.
 */
{
  public:
    char name[100];     /**< Dowolny ciąg znaków nadany przez użytkownika                           */
    time_t date;        /**< Data rozpoczęcia testu                                                 */

    int packet_size;    /**< Rozmiar pojedynczego pakietu                                           */
    int protocol;       /**< Rodzaj zastosowanego do transmisji protokołu                           */
    int coverage;       /**< W przypadku UDP-Lite, procent pokrycia pakietu sumą kodową             */ 
    int bitrate;        /**< Wymagana przepływność                                                  */
    int PID_time;       /**< Okres regulacji przepływności (częstotliwość wyznaczania korekcji PID) */

    /**
     * Konstruktor klasy po stronie odbiorczej.
     * Pobiera od uzytkownika niezbędne dane i tworzy z nich obiekt.
     */
    TransmissionArrangement();
    /**
     * Konstruktor klasy po stronie nadawczej.
     * Przyjmuje dane od srtony odbiorczej, odpowiednio je dzieli i tworzy identyczny obiekt po stronie nadawczej.
     * @param tablica[] ciąg danych przesłany od strony nadawczej
     */
    TransmissionArrangement(char[]);
    void print();
    void getDate();
    /**
     * \brief metoda służąca przekształceniu oobiektu klasy w ciąg dany nadający się do wysłania
     * @param tablica[] miejsce w ktorym zostanie zapisany przekształcony ciąg danych
     */
    void tochar(char[]);
};
/**
 * @brief Get the Number object
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int getNumber(int min, int max);
#endif
