#ifndef TA
#define TA

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
///klasa przechowująca podstawowe informacje o warunkach pomiaru, obiekty tej klasy są tworzone po obu stronach (odbiorczej i nadawczej)
{
  public:
    char name[100]; //nazwa pomiaru wysbrana przez użytkownika
    time_t date;     //data rozpoczęcia testu

    int packet_size;
    int protocol;
    int coverage;
    int bitrate;
    int PID_time;

    TransmissionArrangement();
    TransmissionArrangement(char[]);
    void print();
    void getData();
    void tochar(char[]);
};
//funkcja do sprawdzania danych wprowadzanych przez urzytkownika
int getNumber(int min, int max);
#endif