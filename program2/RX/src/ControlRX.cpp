#include "../headers/ControlRX.hpp"

ControlRX::ControlRX(int bitrate, int new_packet_size)
{
    state = 1;
    counter = 0;
    packet_size = new_packet_size;
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
    state = 0;
}

void Control_RX(ControlRX &ctr, int &bitrate, int socket_)
{
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
        cout<<"Zmieniono przelywnosc na: "<<bitrate<<endl;
        }
    }
}