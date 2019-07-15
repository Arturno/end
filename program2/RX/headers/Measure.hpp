/**
 * @file Measure.hpp
 * @brief Plik zawierający definicję klasy Measure oraz funkcje przez nią wykorzystywane.
 */
#include <iostream>
#include <cstdio>
#include <fstream>

#include "ControlRX.hpp"
#include "Check.hpp"
using namespace std;
/**
 * @brief Klasa zbierająca wszystkie wyniki testu
 * @details Obiekt tej klasy zbiera informacje z:
 *          plików systemowych - poziom sygnału i jakość linku
 *          enkodera - położenie strony odbiorczej
 *          funkcji odpowiedzialnej za odbiór pakietów - uzyskana przepływność
 *          funkcji odpowiedzialnej za sprawdzanie przychodzących pakietów - błędnie odebrane bity
 */
class Measure
{
    public:
    double position;                        /**< pozycja strony odbiorczej, pobrana od enkodera*/
    string interface_name;                  /**< nazwa interfejsu WiFi */
    string channel;                         /**< kanał pracy WiFi*/
    float bt;                               /**< wyznaczona przepustowość kanału */
    int bandwidth;                          /**< szerokość kanału */
    int MCS;                                /**< (Modulation and Coding Index) schemat modulacji i kodowania */
    int NSS;                                /**< (Number of Spatial Stream) liczba strumieni */
    bool short_preable;                     /**< flaga informująca o długości odstepu ochronnego true - 400ns, false 800ns */
    int signal_level;                       /**< poziom sygnału WiFi odbieranego przez stronę odbiorczą */
    int signal_quality;                     /**< wyznaczona przez system jakość linku */
    unsigned int received;                  /**< liczba odebranych pakietów*/
    unsigned int previously_received;       /**< zmienna służąca do określenia liczby odebranych pakietów*/
    double bitrate;                         /**< przepływnosc wyznaczona na podstawie liczby pakietów*/
    double error;                           /**< procent błędnie odebranych bitów do ogolnej liczby przesłanych bitów*/
    int lost;                               /**< liczba utraconych pakietów */
    bool err;                               /**< flaga informujaca o wystapieniu błędu przy odbiorze/stracie dużej liczby pakietów */
    bool not_in_order;                      /**< flaga informujaca o kolejnosci odbierania pakietów true - pakiety odebrane w kolejnosci wysłania */
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
     * @brief metoda służąca do pobrania danych o poziomie sygnału i jakości linku z plików systemowych oraz parametrów kanału wykorzystanego podczas transmisji
     */
    void getsignalinfo();
};

