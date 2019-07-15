#include "serial.hpp"
#include <time.h>
#include <iostream>
#include "ControlRX.hpp"
#define SPIKES 400
#define DIAMETER 5
/**
 * @file position.hpp
 * @brief Plik zawierający fukncje wykorzystywane do odbioru danych z enkodera
 */

/**
 * @brief funkcja cyklicznie pobierajaca dane od enkodera
 * 
 * @param position pozycja odebrana od enkodera
 * @param end zmienna stanu programu informujaca czy należy dalej odbierać dane
 */
void position(ControlRX &ctr);
struct position_t
/**
 * @brief stuktura przechowująca wartość zwracaną od enkodera
 * 
 */
{
    bool correctly_parsed;         /**< zmienna przechowująca informacje czy dane zostaly poprawnie sparsowane*/
    int position;                  /**< pozycja zwracana od enkodera*/ 
};
/**
 * @brief funkcja sprawdzająca czy dane które zostały odebrane od enkodera są poprawne
 * 
 * @param a pozycja odebrana od enkodera
 * @param b suma kontrolna
 * @param parsed zmienna przechowujaca informacje czy dane zostaly poprawnie sparsowane
 * @return true podana wartość może zostać uznana za poprawną
 * @return false podana wartość jest niepoprawna i zostanie odrzucona
 */
bool check(int a, int b, bool parsed);
/**
 * @brief funkcja pobierająca i parsująca dane od enkodera
 * 
 * @param fenc adres enkodera
 * @return int aktualna wartosc pozycji
 */
int getPosition(int fenc);
