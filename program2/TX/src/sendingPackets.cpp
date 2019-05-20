#include "../headers/sendingPackets.hpp"

using namespace std;

void send_UDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, ControlTX &ctr)
{
    char buffer[ctr.packet_size] = {};
    srand(50);
    for (int i = 12; i < ctr.packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    buffer[ctr.packet_size] = '\0';
    const int socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    if (bind(socket_, (struct sockaddr *)&TX_meas, sizeof(TX_meas)) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }
    while (ctr.state)
    {
        for (int i = 0; i < ctr.packet_group; i++)
        {
            sprintf(buffer, "%d", ctr.counter);
            if (sendto(socket_, buffer, sizeof(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            ctr.counter++;
        }
        usleep(ctr.delay);
        //cout << "Wsłano UDP" << endl;
    }
    usleep(100000);
    if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
    {
        perror("sendto() ERROR");
        exit(5);
    };

    shutdown(socket_, SHUT_RDWR);
}
void send_UDPLite(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int coverage, ControlTX &ctr)
{
    char buffer[ctr.packet_size] = {};
    srand(50);
    for (int i = 10; i < ctr.packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    const int socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDPLITE);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    setsockopt(socket_, SOL_UDPLITE, UDPLITE_SEND_CSCOV, &coverage, sizeof(int));
    if (bind(socket_, (struct sockaddr *)&TX_meas, sizeof(TX_meas)) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }
    while (ctr.state)
    {
        for (int i = 0; i < ctr.packet_group; i++)
        {
            sprintf(buffer, "%d", ctr.counter);
            if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            ctr.counter++;
        }
        usleep(ctr.delay);
    }
    usleep(100000);
    if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
    {
        perror("sendto() ERROR");
        exit(5);
    };
    shutdown(socket_, SHUT_RDWR);
}
void send_TCP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, ControlTX &ctr)
{
    char buffer[ctr.packet_size] = {};
    srand(50);
    for (int i = 10; i < ctr.packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    const int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    int opt = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(socket_, (struct sockaddr *)&TX_meas, sizeof(TX_meas)) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }
    connect(socket_, (struct sockaddr *)&RX_meas, sizeof(RX_meas));
    while (ctr.state)
    {
        for (int i = 0; i <= ctr.packet_group; i++)
        {
            sprintf(buffer, "%d", ctr.counter);
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            ctr.counter++;
        }
        usleep(ctr.delay);
    }
    shutdown(socket_, SHUT_RDWR);
}
