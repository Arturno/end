#include "../headers/sendingPackets.hpp"

using namespace std;

void send_UDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size, int &delay, int &packet_group,unsigned int &counter, int &state)
{
    char buffer[packet_size] = {};
    srand(50);
    for (int i = 12; i < packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    buffer[packet_size] = '\0';
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
    while (state)
    {
        for (int i = 0; i < packet_group; i++)
        {
            sprintf(buffer, "%d", counter);
            if (sendto(socket_, buffer, sizeof(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            counter++;
        }
        usleep(delay);
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
void send_UDPLite(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size, int &delay, int &packet_group, int coverage,unsigned int &counter, int &state)
{
    char buffer[packet_group] = {};
    srand(50);
    unsigned int wyslane = 0;
    for (int i = 10; i < packet_group; i++)
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
    while (state)
    {
        for (int i = 0; i < packet_group; i++)
        {
            sprintf(buffer, "%d", wyslane);
            if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            wyslane++;
        }
        counter++;
        usleep(delay);
    }
    usleep(100000);
    if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
    {
        perror("sendto() ERROR");
        exit(5);
    };
    shutdown(socket_, SHUT_RDWR);
}
void send_TCP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size, int &delay, int &packet_group,unsigned int &counter, int &state)
{
    char buffer[packet_size] = {};
    srand(50);
    unsigned int wyslane = 0;
    for (int i = 10; i < packet_size; i++)
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
    while (state)
    {
        for (int i = 0; i <= packet_group; i++)
        {
            sprintf(buffer, "%d", wyslane);
            if (send(socket_, buffer, sizeof(buffer), 0) <= 0)
            {
                perror("send() ERROR");
                exit(6);
            }
            wyslane++;
        }
        counter++;
        usleep(delay);
    }
    shutdown(socket_, SHUT_RDWR);
}
