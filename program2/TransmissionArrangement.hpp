#ifndef TA_HH
#define TA_HH
/**
 * @file TransmissionArrangement.hpp
 * @brief Plik zawierający klasę TransmissionArrangement oraz fukcje przez nią uzywane
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
 *  @brief Klasa służąca do ustanowienia poczatkowych parametrow transmisji.
 *  @details Wykorzystywana zarówno po stronie odbiorczej i nadawczej.
 *           strona odbiorcza przesyła stronie nadawczej wymagania co do parametrów transmisji.
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
     * @brief Konstruktor klasy po stronie odbiorczej.
     * @details Pobiera od uzytkownika niezbędne dane i tworzy z nich obiekt.
     */
    TransmissionArrangement();
    /**
     * @brief Konstruktor klasy po stronie nadawczej.
     * @details Przyjmuje dane od srtony odbiorczej, odpowiednio je dzieli i tworzy identyczny obiekt po stronie nadawczej.
     * @param tablica[] ciąg danych przesłany od strony nadawczej
     */
    TransmissionArrangement(char[]);
    /**
     * @brief Metoda służąca do wypisania zawartości obiektu TransmissionArrangement
     * 
     */
    void print();
    /**
     * @brief Metoda przekształcająca datę do formatu yyyy-mm-dd hh-mm-ss 
     * 
     */
    void getDate();
    /**
     * @brief metoda służąca przekształceniu oobiektu klasy w ciąg dany nadający się do wysłania
     * @param tablica[] miejsce w ktorym zostanie zapisany przekształcony ciąg danych
     */
    void tochar(char[]);
};
/**
 * @brief Fukcja służąca do pobierania i sprawdzania liczby od użytkownika
 * 
 * @param min minimalna dopuszczalna wartość 
 * @param max maksymalna dopuszczalna watrość
 * @return int zwraca podaną przez użytkownika liczbę jeśli jest poprawna
 */
int getNumber(int min, int max);
#endif
