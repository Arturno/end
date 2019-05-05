#ifndef SAV
#define SAV

#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include "../../TransmissionArrangement.hpp"
using namespace std;
string cr_filename(class TransmissionArrangement parameters);
string signal_level();
void meas_and_save(class TransmissionArrangement &parameters,int &position,int &counter, int &state, class CheckPackets &chk);


#endif