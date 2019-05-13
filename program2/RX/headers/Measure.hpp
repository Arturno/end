/**
 * @file measure.hpp
 * @brief Plik przechowujący definicję klasy Measure oraz funkcje przez nią wykorzystywane.
 */
#include <iostream>
#include <cstdio>
#include <fstream>

#include "ControlRX.hpp"
#include "Check.hpp"
using namespace std;
/**
 * @brief measure
 * 
 */
class Measure
{
    public:
    int position;                           /**< pozycja strony odbiorczej, pobrana od enkodera*/
    int signal_level;                       /**< poziom sygnału WiFi odbieranego przez stronę odbiorczą */
    int signal_quality;                     /**< wyznaczona przez system jakość linku */
    unsigned int received;                  /**< liczba odebranych pakietów*/
    unsigned int previously_received;       /**< zmienna służąca do określenia liczby odebranych pakietów*/
    double bitrate;                         /**< przepływnosc wyznaczona na podstawie liczby pakietów*/
    double error;                           /**< procent błędnie odebranych bitów do ogolnej liczby przesłanych bitów*/

     /**
     * @brief Konstruktor klasy Measure
     * @details inicjalizuje obiekt klasy z wszystkimi wartościami ustawionymi na 0
     * 
     */
    Measure();
     /**
     * @brief wyznaczenie % błędnie odebranych bitów
     * @return zwraca dane w formie tekstowej, gotowej do zapisania do pliku
     */
    string getResult();
     /**
     * @brief metoda służąca do zbierania danych z róznych częsci programu
     * @param ctr obiekt klasy przechowujące dane o położeniu, stanie oraz liczbie odebranych pakietów
     * @param chk obiekt klasy wyznaczający błędy podczas transmisji
     */
    void collectData(class ControlRX &ctr,class CheckPackets &chk);
     /**
     * @brief metoda służąca do pobrania danych o poziomie sygnału i jakości linku z plików systemowych
     */
    void getsignalinfo();
};

