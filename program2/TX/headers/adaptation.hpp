#ifndef AD
#define AD
/**
 * @file adaptation.hpp
 * @brief Plik zawierający funkcję odpowiadającą za dostosowanie czasu opóźnienia wysyłanych pakietów
 * 
 */
#include <iostream>
#include <unistd.h>
#include <climits>
#include "PID.hpp"
#include "ControlTX.hpp"
/**
 * @brief 
 * 
 * @param ctr obiekt informujący o stanie programu
 * @param PID_time częstotliwość wyznaczania korekty określona przez uzytkownika
 */
void adaptation(ControlTX &ctr, int PID_time);

#endif
