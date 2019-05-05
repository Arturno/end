#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define error_message printf

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);


#endif // SERIAL_H_INCLUDED
