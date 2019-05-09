#include "serial.hpp"
#include <time.h>
#include <iostream>
/**
 * @brief 
 * 
 * @param position 
 * @param end 
 */

void position(int &position, int &end);
typedef struct
/**
 * @brief 
 * 
 */
{
    bool correctly_parsed;
    int position;         // position in meters
}position_t;
/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param parsed 
 * @return true 
 * @return false 
 */
bool check(int a, int b, bool parsed);
/**
 * @brief Get the Position object
 * 
 * @param fenc 
 * @return int 
 */
int getPosition(int fenc);
