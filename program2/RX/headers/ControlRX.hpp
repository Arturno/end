#ifndef CTX
#define CTX
/**
 * @file ControlRX.hpp
 * @brief Plik zawierający klasę ControlRX, kontrolującą stan programu po stronie odbiorczej 
 * 
 */
#include <iostream>
#include <string.h>
#include <sys/socket.h>
using namespace std;
/**
 * @brief Klasa przechowująca stan programu i jego najważniejsze parametry.
 *        Odpowiedzialna również za sterowanie programem oraz komunikacje z użytkownikiem
 * 
 */
class ControlRX
{
    public: 
    int state;                  /**<stan programu running/end*/
    unsigned int counter;       /**<licznik odebranych pakietów*/
    int packet_group;           /**<liczba pakietów w grupie*/
    int packet_size;            /**<rozmiar pojedynczego pakietu*/
    int position;               /**<położenie strony odbiorczej*/

    /**
     * @brief Konstruktor obiektu klasy ControlRX
     * 
     * @param bitrate zadana przez użytkownika przepływność
     * @param packet_size zadany przez użytkownika rozmiar pakietu 
     */
    ControlRX(int bitrate, int packet_size);

    /**
     * @brief funkcja kończąca działanie programu
     * @details Po wywołaniu zmienia wartość zmiennej state na 0 co powoduje zakonczenie wykonywania się wszystkich funkcji programu
     * 
     */
    void end_program();

};
/**
 * @brief Funkcja umożliwiająca komunikację z użytkownikiem i stroną odbiorczą
 * @details Przechowuje ona obiekt klasy ControlRX, który odpowiada za modyfikowalne, podczas testu, parametry programu
 * @param ctr Obiekt klasy ControlRX 
 * @param socket_ Gniazdo do komunikacji ze stroną odbiorczą
 */
void Control_RX(ControlRX &ctr,int &bitrate, int socket_);

#endif