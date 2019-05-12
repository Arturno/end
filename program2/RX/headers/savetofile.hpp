#ifndef SAV
#define SAV
/**
 * @file savetofile.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include "../../TransmissionArrangement.hpp"
#include "Measure.hpp"
#include "ControlRX.hpp"
using namespace std;
/**
 * @brief 
 * 
 * @param parameters 
 * @return string 
 */
string cr_filename(class TransmissionArrangement parameters);
/**
 * @brief 
 * 
 * @return string 
 */
string signal_level();
/**
 * @brief 
 * 
 * @param parameters 
 * @param position 
 * @param counter 
 * @param state 
 * @param chk 
 */
void meas_and_save(class TransmissionArrangement &parameters, class ControlRX &ctr, class CheckPackets &chk);


#endif