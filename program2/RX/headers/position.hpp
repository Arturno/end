
#include "serial.hpp"
#include <time.h>
#include <iostream>


void position(int &position, int &end);

typedef struct{
    bool correctly_parsed;
    int position;         // position in meters
}position_t;

bool check(int a, int b, bool parsed);
int getPosition(int fenc);
