#ifndef TA_HH
#define TA_HH
/* \brief Klasa służąca do ustanowienia poczatkowych parametrow transmisji.
 *        Wykorzystywana po stronie odbiorczej i nadawczej.
 *        Strona odbiorcza przesyła stronie nadawczej wymagania co do parametrów transmisji.
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
{
  public:
    char name[100];     /** Dowolny ciąg znaków nadany przez użytkownika                           */
    time_t date;        /** Data rozpoczęcia testu                                                 */

    int packet_size;    /** Rozmiar pojedynczego pakietu                                           */
    int protocol;       /** Rodzaj zastosowanego do transmisji protokołu                           */
    int coverage;       /** W przypadku UDP-Lite, procent pokrycia pakietu sumą kodową             */ 
    int bitrate;        /** Wymagana przepływność                                                  */
    int PID_time;       /** Okres regulacji przepływności (częstotliwość wyznaczania korekcji PID) */
    /**
     * Konstruktor klasy po stronie odbiorczej.
     * Pobiera od uzytkownika niezbędne dane i tworzy z nich obiekt.
     */
    TransmissionArrangement();
    /**
     * Konstruktor klasy po stronie nadawczej.
     * Przyjmuje dane od srtony odbiorczej, odpowiednio je dzieli i tworzy identyczny obiekt po stronie nadawczej.
     * @param tab ciąg danych przesłany od strony nadawczej
     */
    TransmissionArrangement(char[] tab);
    void print();
    void getData();
    /**
     * metoda służąca przekształceniu oobiektu klasy w ciąg dany nadający się do wysłania
     * @param miejsce w ktorym zostanie zapisany przekształcony ciąg danych
     */
    void tochar(char[]);
};
    /**
     * funkcja służąca do pobierania danych od użytkownika i sprawdzania czy podana wartość jest liczbą z konkretnego zakresu
     * @param min minimalna dopuszczalna wartość
     * @param max maksymalna dopuszczalna wartość
     * @return wartość podana przez uzytkownika
     */
int getNumber(int min, int max);
#endif
