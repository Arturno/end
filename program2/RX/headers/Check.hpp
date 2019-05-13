#ifndef CHK
#define CHK
/**
 * @file Check.hpp
 * @brief Plik przechowujacy klasę CheckPackets i funkcje przez nią wykorzystywane
 * 
 */
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <limits.h>
#include <unistd.h>
#include "../../TransmissionArrangement.hpp"
using namespace std;

#define TABLE_SIZE 1000
#define MTU 1500 
/**
 * @brief Klasa służąca sprawdzaniu pakietów przychodzących 
 * @details przechowuje ona tablicę do której dodawane są pakiety przychodzące po czym sprawdza kolejność i przekłamanie
 *          wyznaczając % błędnie odebranych bitów danych
 */
class CheckPackets
{
  public:
    char buffer[TABLE_SIZE][MTU] = {};  /**< bufor przechowujący przychhodzące pakiety*/

    int adding;                         /**< miejsce w tablicy w które powinien zostac dodany kolejny przychodzacy pakiet*/
    int check;                          /**< miejsce w tablicy w którym jest ostatni sprawdzony pakiet*/

    int packet_size;                    /**< rozmiar pakietów */

    int added;                          /**< liczba dodanych pakietów */
    int checked;                        /**< liczba sprawdzonych palietów*/
    int bit_errors;                     /**< liczva błędnie odebranych bitów*/
    int lost;                           /**< liczba straconych pakietów*/
    bool not_in_order;                  /**< flaga informujaca czy pakiety zostały odebrane w kolejności nadania*/
    bool err;                           /**< flaga informujaca o poważniejszym problemie podczas transmisji, np.: utrata wielu pakietów*/

    double errors;                      /**< % błędnie odebranych bitów */
    //int nrpakietu;

    /**
     * @brief Konstruktor klasy
     * @details Ustawia odpowiednie flagi, nie pobiera informacji od użytkownika
     */
    CheckPackets();
    /**
     * @brief metoda służąca do wyznaczenia miejsca w tablicy w którym powinien zostać dodany pakiet
     * 
     * @return char* zwraca wskaźnik do miejsca w tablicy w którym powinien zostać umieszczony następny przychodzący pakiet
     */
    char *add();
    /**
     * @brief 
     * 
     * @return int 
     */
    int spraw();
    /**
     * @brief wyznaczenie % błędnie odebranych bitów
     * 
     * @return double wartość % błędnie odebranych bitów do wszystkich odebranych
     */
    double pomiar();
    /**
     * @brief 
     * 
     */
    void test();
};
/**
 * @brief funkcja kontrolująca cały mechanizm sprawdzania
 * 
 * @param chk obiekt klasy CheckPackets
 * @param state zmienna stanu programu informujaca czy należy dalej wykonywać sprawdzanie
 */
void check(class CheckPackets &chk, int &state);
#endif
