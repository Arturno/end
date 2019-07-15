#include "../headers/ControlTX.hpp"

using namespace std;

ControlTX::ControlTX(int bitrate, int new_packet_size)
{
    //ustawienie stanu programu na ON 
    state = 1;
    //ustawienie licznika wysłanych pakietów na zero
    counter = 0;   
    //zapisanie rozmiaru pakietu                                     
    packet_size = new_packet_size;
    //obliczenie liczby pakietów do wysłania w ciagu 1 sekundy                     
    to_send = (bitrate * 1000000) / (packet_size * 8);  
    //obliczenie liczby pakietów w grupie 1 pakiet w grupie gdy liczba pakietów do wysłania w ciagu 1 sekundy jest mniejsza od 1000
    if ((to_send * 0.001) < 1)
    {
        packet_group = 1;
    }
    else
    {
        packet_group = to_send * 0.001;
        delay = (packet_size * packet_group * 1000) / (bitrate * 250);
    }
}

void ControlTX::change_bitrate(int bitrate)
{
    //obliczenie nowej liczby pakietów do wysłania w ciągu jednej sekundy
    to_send = (bitrate * 1000000) / (packet_size * 8);
    //wyznaczenie nowej liczby pakietów w grupie
    if ((to_send * 0.001) < 1)
    {
        packet_size = 1;
    }
    else
    {
        packet_group = to_send * 0.001;
        delay = (packet_size * packet_group * 1000) / (bitrate * 250);
    }
}


void ControlTX::end_program()
{   
    //zmiana stanu programu na OFF 
    state = 0;
}
void Control_TX(ControlTX &ctr, int socket_)
{

    int bitrate = 0;
    char buffer[150] = {};
    while (ctr.state)
    {
        //odebranie informacji sterującej od RX
        if (recv(socket_, buffer, sizeof(buffer), 0) <= 0)
        {
            perror("recv() ERROR");
            exit(5);
        }
        //sprawdzenie czy RX wysłał informacje o zakończeniu testu
        if(buffer[0] == 0)
        {
            //jeśli tak, program konczy działanie i informuje o tym użytkownika
            ctr.end_program();
            cout<<"Koniec testu"<<endl;
            break;
        }
        else
        {
            //zmiana przepływnosci na tą podaną przez użytkownika
            bitrate = atoi(buffer);
            ctr.change_bitrate(bitrate);
            cout<<"Zmieniono przelywnosc na: "<<bitrate<<endl;
        }
    }
}