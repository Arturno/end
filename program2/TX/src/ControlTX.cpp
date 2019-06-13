#include "../headers/ControlTX.hpp"

using namespace std;

ControlTX::ControlTX(int bitrate, int new_packet_size)
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

void ControlTX::change_bitrate(int bitrate)
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


void ControlTX::end_program()
{
    state = 0;
}
void Control_TX(ControlTX &ctr, int socket_)
{
    int bitrate = 0;
    char buffer[150] = {};
    while (ctr.state)
    {
        if (recv(socket_, buffer, sizeof(buffer), 0) <= 0)
        {
            perror("recv() ERROR");
            exit(5);
        }
        if(buffer[0] == 0)
        {
            ctr.end_program();
            cout<<"Koniec testu"<<endl;
            break;
        }
        else
        {
        bitrate = atoi(buffer);
        ctr.change_bitrate(bitrate);
        cout<<"Zmieniono przelywnosc na: "<<bitrate<<endl;
        }
    }
}