#ifndef SAV
#define SAV
/**
 * @file savetofile.hpp
 * @brief Plik zawierający funkcje odpowiadające za zapis wyników testu do pliku
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
 * @brief funkcja generująca nazwę pliku
 * @details nazwa pliku składa się z nazwy podanej przez użytkownika oraz daty rozpoczęcia testu
 *          wszystkie pliki zawierające wyniki testu są zapisywane w oddzielnym katalogu o nazwie results
 * 
 * @param parameters obiekt klast TransmissionArrangement na podstawie, którego generowana jest nazwa pliku z wynikami
 * @return string nazwa pliku
 */
string cr_filename(class TransmissionArrangement parameters);

/**
 * @brief funkcja realizująca zapis wyników pomiarów do pliku 
 * @details funkcja tworzy obiekt klasy Measure z aktualnymi wartościami zczytanymi z odpowiednich częsci programu
 *          następnie otwiera plik i dopisuje do niego linijkę z wynikami za ostatnią sekundę
 * @param parameters parametry podane przez użytkownika
 * @param ctr stan programu oraz wartości liczników - odebranych pakietów i położenia
 * @param chk liczba błędnie odebranych bitów 
 */
void meas_and_save(class TransmissionArrangement &parameters, class ControlRX &ctr, class CheckPackets &chk);


#endif