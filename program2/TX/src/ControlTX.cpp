#include "../headers/ControlTX.hpp"

using namespace std;

Control::Control(int bitrate, int new_packet_size)
{
    state = 1;
    counter = 0;
    packet_size = new_packet_size;
    to_send = (bitrate * 1000000) / (packet_size * 8);
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

void Control::change_bitrate(int bitrate)
{
    to_send = (bitrate * 1000000) / (packet_size * 8);
    if ((to_send * 0.001) < 1)
    {
        packet_size = 1;
    }
    else
        packet_group = to_send * 0.001;
    delay = (packet_size * packet_group * 1000) / (bitrate * 250);
}


void Control::end_program()
{
    state = 0;
}
void ControlTX(int &state, class Control &ctr, int socket_)
{
    char change = {};
    char buffer[150];
    while (state)
    {
        cin >> change;
        switch (change)
        {
        case 'E':
            ctr.end_program();
            buffer[0] = 0;
            cout << "Koniec testu" << endl;
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            break;
        case 'M':
            int bitrate;
            bitrate = getNumber(1, 1000);
            ctr.change_bitrate(bitrate);
            cout<<"#############################################################################"<<endl;
            cout << "Zmieniono przepływoność na:" << bitrate << "Mb/s" << endl;
            cout<<"#############################################################################"<<endl;
            sprintf(buffer, "%d", bitrate);
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            break;
        default:
        {
            cin.clear();
            cin.sync();
            string cl;
            getline(cin, cl);
            cout << "Błędna wartość" << endl;
        }
        }
    }
}