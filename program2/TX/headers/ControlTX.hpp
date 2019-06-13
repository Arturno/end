#ifndef CTX
#define CTX
/**
 * @file ControlTX.hpp
 * @brief Plik zawierający klasę ControlTX, kontrolującą stan programu po stronie nadawczej
 * 
 */
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include "../../TransmissionArrangement.hpp"
/**
 * @brief Klasa przechowująca stan programu i jego najważniejsze parametry.
 *        Odpowiedzialna również za sterowanie programem oraz komunikacje z użytkownikiem
 * 
 */
class ControlTX
{
  public:
    int state;                /**< Stan programu running/end*/
    unsigned int counter;     /**< Licznik wysłanych pakietów*/
    int delay;                /**< Opóźnienie pomiędzy wysyłaniem kolejnych paczek pakietów*/
    int to_send;              /**< Liczba pakietów, które powinny zostać wysłane w ciągu jednej sekundy aby uzyskać przepływność zadaną przez użytkownika*/
    int packet_group;         /**< Liczba pakietów w jednej grupie*/
    int packet_size;          /**< Rozmiar jednego pakietu*/
    

    /**
     * @brief Konstruktor obiektu klasy ControlTX
     * @param bitrate zadana przez użytkownika przepływność
     * @param packet_size zadany przez użytkownika rozmiar jednego pakietu
     */
    ControlTX(int bitrate, int packet_size);
    /**
     * @brief Metoda umożliwiająca zmianę zadanej przepływności podczas trwania programu
     * @param bitrate nowa przepływność
     */
    void change_bitrate(int bitrate);
    /**
     * @brief Metoda koncząca działanie programu
     * 
     */
    void end_program();
};
/**
 * @brief Funkcja umożliwiająca komunikację z użytkownikiem i stroną odbiorczą
 * @details Przechowuje ona obiekt klasy ControlTX, który odpowiada za modyfikowalne, podczas testu, parametry programu
 * @param ctr Obiekt klasy ControlTX
 * @param socket_ Gniazdo do komunikacji ze stroną odbiorczą
 */
void Control_TX(ControlTX &ctr, int socket_);

#endif 