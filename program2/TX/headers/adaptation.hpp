#ifndef AD
#define AD

#include <iostream>
#include <unistd.h>
#include <climits>
#include "PID.hpp"
#include "ControlTX.hpp"

void adaptation(Control &ctr, int PID_time);

#endif AD
