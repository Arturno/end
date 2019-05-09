#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define error_message printf
/**
 * @file serial.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
/**
 * @brief Set the interface attribs object
 * 
 * @param fd 
 * @param speed 
 * @param parity 
 * @return int 
 */
int set_interface_attribs (int fd, int speed, int parity);
/**
 * @brief Set the blocking object
 * 
 * @param fd 
 * @param should_block 
 */
void set_blocking (int fd, int should_block);


#endif // SERIAL_H_INCLUDED
