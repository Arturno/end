#include "../headers/receivingPackets.hpp"
using namespace std;

void odbieranieUDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int packet_size, unsigned int &counter, int &state, class CheckPackets &chk)
{
    //wątek do sprawdzania pakietów
    thread check_packet(check, ref(chk), ref(state));

    //tworzenie gniazda
    const int socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    //ustawienie timeoutu na otrzymanie pakietów (10s)
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    if (setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Error");
    }
    socklen_t len = sizeof(RX_meas);
    if (bind(socket_, (struct sockaddr *)&RX_meas, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }
    //głowna funkcja odpowiedzialna za odbieranie pakietów
    while (state)
    {   
        //odbieranie pakietów
        if (recvfrom(socket_, chk.add(), packet_size, 0, (struct sockaddr *)&RX_meas, &len) < 0)
        {
            perror("recvfrom() ERROR");
            exit(4);
        }
        //zwiększanie licznika odebranych pakietów
        counter++;
    }
    //konczenie wątku do sprawdzania pakietów
    check_packet.join();

    //zamykanie gniazd
    shutdown(socket_, SHUT_RDWR);
}

void odbieranieUDPLite(struct sockaddr_in TX, struct sockaddr_in RX, int packet_size, unsigned int &counter, int &state, class CheckPackets &chk, int &coverage)
{
    //wątek do sprawdzania pakietów
    thread check_packet(check, ref(chk), ref(state));

    //tworzenie gniazda
    const int socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDPLITE);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }

    //ustawienie timeoutu na otrzymanie pakietów (10s)
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    if (setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Error");
    }
    //ustawienie kodowania pakietów 
    setsockopt(socket_, SOL_UDPLITE, UDPLITE_RECV_CSCOV, &coverage, sizeof(int));
    socklen_t len = sizeof(RX);
    if (bind(socket_, (struct sockaddr *)&RX, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    //głowna funkcja odpowiedzialna za odbieranie pakietów
    while (state)
    {
        //odbieranie pakietów
        if (recvfrom(socket_, chk.add(), packet_size, 0, (struct sockaddr *)&RX, &len) < 0)
        {
            perror("recvfrom() ERROR");
            exit(4);
        }
        //zwiększanie licznika odebranych pakietów
        counter++;
    }

    //konczenie wątku do sprawdzania pakietów
    check_packet.join();

    //zamykanie gniazd
    shutdown(socket_, SHUT_RDWR);
}
