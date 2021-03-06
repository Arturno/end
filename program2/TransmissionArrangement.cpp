#include "TransmissionArrangement.hpp"

int getNumber(int min, int max)
{
    int temp;
    string cl;
    while (1)
    {   
        //pobranie wartości od użytkownika
        cin >> temp;
        //sprawdzenie czy podana wartość to liczba
        if (!cin)
        {   
            //czyszczenie buforów i flag błędu
            cin.clear(); 
            cin.sync();
            getline(cin, cl);
            cout << "Podana wartość nie jest liczbą." << endl;
            continue;
        }
        //sprawdzenie czy podana wrtość mieści się w granicach
        if (temp > max || temp < min)
        {
            cout << "Podana wartość jesc spoza zakresu [" << min << "," << max << "]" << endl;
            continue;
        }
        break;
    }
    //jesli podana wartość jest liczbą z podanego zakresu zostaje zwrócona przez funkcję 
    return temp;
}

TransmissionArrangement::TransmissionArrangement()
{
    //pobranie danych od użytkownika
    cout << "Podaj nazwę testu:" << endl;
    cin >> name;
    cout << "Podaj wymaganą przepływność w Mb/s:" << endl;
    bitrate = getNumber(1, 1000);
    cout << "Podaj rozmiar ramki w B:" << endl;
    packet_size = getNumber(1, 1500);
    cout << "Podaj protokół [0 - UDP, 1 - UDP-Lite]:" << endl;
    protocol = getNumber(0, 2);
    if (protocol == 1)
    {
        cout << "Podaj poziom kodowania w %:" << endl;
        coverage = getNumber(0, 100);
    }
    else
        coverage = 100;
    cout << "Podaj czas adaptacji przepływności w ms:" << endl;
    PID_time = getNumber(0, 1000);
    date = time(NULL);
}
TransmissionArrangement::TransmissionArrangement(char tablica[])
{
    //zapisanie obiektu w formie tablicy podanej jako parametr metody
    int shift = 0;
    char transfer[4];
    strncpy(name, tablica, sizeof(name));
    shift += sizeof(name);
    strncpy(transfer, &tablica[shift], sizeof(transfer));
    bitrate = atoi(transfer);
    shift += sizeof(transfer);
    strncpy(transfer, &tablica[shift], sizeof(transfer));
    packet_size = atoi(transfer);
    shift += sizeof(transfer);
    strncpy(transfer, &tablica[shift], sizeof(transfer));
    protocol = atoi(transfer);
    shift += sizeof(transfer);
    strncpy(transfer, &tablica[shift], sizeof(transfer));
    coverage = atoi(transfer);
    shift += sizeof(transfer);
    strncpy(transfer, &tablica[shift], sizeof(transfer));
    PID_time = atoi(transfer);
    date = time(NULL);
}

void TransmissionArrangement::tochar(char tablica[])
{
    int shift = 0;
    char transfer[4];
    strncpy(tablica, name, sizeof(name));
    shift += sizeof(name);
    sprintf(transfer, "%d", bitrate);
    strncpy(&tablica[shift], transfer, sizeof(transfer));
    shift += sizeof(transfer);
    sprintf(transfer, "%d", packet_size);
    strncpy(&tablica[shift], transfer, sizeof(transfer));
    shift += sizeof(transfer);
    sprintf(transfer, "%d", protocol);
    strncpy(&tablica[shift], transfer, sizeof(transfer));
    shift += sizeof(transfer);
    sprintf(transfer, "%d", coverage);
    strncpy(&tablica[shift], transfer, sizeof(transfer));
    shift += sizeof(transfer);
    sprintf(transfer, "%d", PID_time);
    strncpy(&tablica[shift], transfer, sizeof(transfer));
}


void TransmissionArrangement::getDate()
{
    //pobranie daty i zapisanie jej w formacie YYYY-MM-DD hh:mm:ss
    date = time(NULL);
    tm *temp;
    temp = localtime(&date);
    cout << 1900 + temp->tm_year << "-" << setw(2) << setfill('0') << temp->tm_mon << "-" << setw(2) << setfill('0') << temp->tm_mday << " ";
    cout << setw(2) << setfill('0') << temp->tm_hour << ":" << setw(2) << setfill('0') << temp->tm_min << ":" << setw(2) << setfill('0') << temp->tm_sec << endl;
}
/*
void OgolneInfo::getAddress()
//wypisanie adresów i portów TX i RX
{
    char buffer_ip[128] = {};
    cout << "IP TX:  .............................  " << inet_ntop(AF_INET, &TX.sin_addr, buffer_ip, sizeof(buffer_ip)) << endl;
    cout << "port:  ..............................  " << ntohs(TX.sin_port) << endl;
    cout << "IP RX:  .............................  " << inet_ntop(AF_INET, &RX.sin_addr, buffer_ip, sizeof(buffer_ip)) << endl;
    cout << "port:  ..............................  " << ntohs(RX.sin_port) << endl;
}
*/
void TransmissionArrangement::print()
{
    //wypisanie zawartości obiektu
    cout << endl;
    cout << "#############################################################################" << endl;
    cout << "Nazwa testu:  .................................  " << name << endl;
    cout << "Data wykonania testu:  ........................  ";
    getDate();
    cout << "Wymagana przepływność:  .......................  ";
    if (bitrate == 0)
        cout << "MAX "
             << "Mb/s" << endl;
    else
        cout << bitrate << "Mb/s" << endl;
    cout << "Rozmiar ramki:  ...............................  " << packet_size << " B" << endl;
    cout << "Protokół:  ....................................  ";
    switch (protocol)
    {
    case 2:
        cout << "TCP" << endl;
        break;
    case 1:
        cout << "UDP-Lite" << endl;
        cout << "Poziom kodowania:  ............................  " << coverage << "%" << endl;
        break;
    case 0:
        cout << "UDP" << endl;
        break;
    }
    if (bitrate != 0)
        cout << "Czas adaptacji przepustowości w ms: ...........  " << PID_time << "ms" << endl;
}