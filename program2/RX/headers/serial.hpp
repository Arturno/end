#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define error_message printf
/**
 * @file serial.hpp
 * @brief Plik zawierający funckje wykorzystywane do połączenia z kontrolerem enkodera za pomocą portu szeregowego
 * 
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
/**
 * @brief funkcja ustawiająca parametry połączenia z kontrolerem
 * 
 * @param fd adres portu
 * @param speed prędkość  
 * @param parity protokół sprawdzania parzystości
 * @return int 
 */
int set_interface_attribs (int fd, int speed, int parity);
/**
 * @brief funkcja wyłączająca blokowanie portu
 * 
 * @param fd adres portu
 * @param should_block informacja o blokowaniu
 */
void set_blocking (int fd, int should_block);


#endif // SERIAL_H_INCLUDED
