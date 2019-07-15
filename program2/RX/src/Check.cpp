#include "../headers/Check.hpp"

CheckPackets::CheckPackets(int packetsize, int protocol)
{
    adding = 1;
    check = 0;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    packet_size = packetsize;
}

char *CheckPackets::add()
{
    int temp = adding;

    //wyznaczanie pozycji w tabeli do wpisania pakitu
    adding = (adding + 1) % TABLE_SIZE;

    //sprawdzanie czy wyznaczone miejsce w tabeli jest wolne (pakiet został juz sprawdzony)
    if (temp == check)
    {
        err = true;
        cout << "ADD TO FAST" << endl;
    }
    added++;
    return buffer[temp];
}

int CheckPackets::toCheck()
{   
    //jesli miejsce do sprawdzenia jest równe miejscu w którym powinien zostac dodany pakiet to oznacza ze nie ma pakietu do sprawdzenia
    if ((check + 2) % TABLE_SIZE == adding)
    {
        return 1;
    }
    else
    {
        //przesunięcie pozycji do sprawdzenia o jeden 
        check = (check + 1) % TABLE_SIZE;
        //sprawdzenie poprawnosci odebrania pakietu
        calculate();
        checked++;
        return 0;
    }
}

double CheckPackets::getResults()
{
    //obliczenie błędu w odebranych pakietach
    errors = (double)((checked * packet_size) - bit_errors) / (checked * packet_size) * 100;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    return errors;
}

void check(class CheckPackets &chk, int &state)
{
    while (state)
    {   
        //sprawdzanie czy jest pakiet do sprawdzenia
        if (chk.toCheck())
            //jesli nie, sprawdzanie wstrzymuje się na 1000ns
            usleep(1000);
    }
}

void CheckPackets::checkOrder(unsigned int received_packet)
{
    //sprawdzenie czy nie ma zbyt dużej rozbieżności między numere poprzednio odebranego pakietu a obecnym
    if (((packet_number - received_packet) % UINT_MAX) > 1000)
    {
        lost++;
        err = true;
    }

    //sprawdzenie kolejności
    if (packet_number == received_packet)
    {
        packet_number = (received_packet + 1) % UINT_MAX;
    }
    //jeśli kolejność nie jest odpowiednia 
    else
    {   
        //sprawdzenie czy numer odebranego pakietu jest wiekszy od prognozowanego
        if (packet_number < received_packet)
        {
            //wyznaczenie liczby straconych pakietów
            lost += (received_packet - packet_number);
            packet_number = (received_packet + 1) % UINT_MAX;
        }
        else
        {
            //ustawienie flagi zmiany kolejnosci i zmniejszenie liczby utraconych pakietów
            not_in_order = true;
            if(lost > 0)
                lost--;
        }
    }
}
void CheckPackets::calculate()
{
    unsigned int received_packet;
    char temp[12];
    char buf[packet_size - 12];
    char original_package[packet_size - 12];

    //przygotowanie wzorcowego pakietu
    srand(50);
    for (int i = 0; i < (packet_size - 12); i++)
    {
        original_package[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    original_package[packet_size - 12] = '\0';

    //podział pakietu na numer pakietu i losowy ciąg znaków
    strncpy(temp, buffer[check], 12);
    received_packet = atoi(temp);
    strncpy(buf, &(buffer[check])[12], (packet_size - 12));

    //sprawdzenie kolejności odebranych pakietów
    checkOrder(received_packet);

    //jeśli użyty protokół to UDP-Lite - sprawdzenie poprawności odebranego pakietu
    if (protocol == 1)
    {
        for (int i = 0; i < packet_size - 12; i++)
        {
            if (original_package[i] != buf[i])
            {
                bit_errors++;
            }
        }
    }
    else
    {
        bit_errors = 0;
    }
}