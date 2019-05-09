#ifndef AD
#define AD
/**
 * @file adaptation.hpp
 * @author your name (you@domain.com)
 * @brief PRogram do adaptacji
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
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
 * @param ctr 
 * @param PID_time 
 */
void adaptation(Control &ctr, int PID_time);

#endif AD
