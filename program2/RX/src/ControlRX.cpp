#include "../headers/ControlRX.hpp"

ControlRX::ControlRX(int _bitrate, int new_packet_size)
{
    state = 1;
    counter = 0;
    bitrate = _bitrate;
    packet_size = new_packet_size;
    cout<<"Podaj pozycję nadajnika: "<<endl;
    start_position = getNumber(0,1000);
    position = 0;
    if (((bitrate * 1000000) / (packet_size * 8) * 0.001) < 1)
    {
        packet_group = 1;
    }
    else
    {
        packet_group = (bitrate * 1000000) / (packet_size * 8) * 0.001;
    }
}

void ControlRX::end_program()
{
    //zmiana stanu na zakonczenie programu
    state = 0;
}

void Control_RX(ControlRX &ctr, int socket_)
{
    char change = {};
    char buffer[150];
    //pobieranie danych od użytkownika dotyczących zmiany przepływności/zakonczeniu programu
    while (ctr.state)
    {
        cin >> change;
        switch (change)
        {
        case 'E':
            //kończenie programu
            ctr.end_program();
            cout << "Koniec testu" << endl;
            //przygotowanie pakietu i wysłanie do strony TX
            buffer[0] = 0;
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            break;
        case 'M':
            //zmiana przepływności
            ctr.bitrate = getNumber(1, 1000);
            cout<<"#############################################################################"<<endl;
            cout << "Zmieniono przepływoność na:" << ctr.bitrate << "Mb/s" << endl;
            cout<<"#############################################################################"<<endl;
            //przygotowanie pakietu i wysłanie do strony TX
            sprintf(buffer, "%d", ctr.bitrate);
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            break;
        default:
        {
            //czyszczenie flag w przypadku gdy podane dane są błędne
            cin.clear();
            cin.sync();
            string cl;
            getline(cin, cl);
            cout << "Błędna wartość" << endl;
        }
        }
    }
}