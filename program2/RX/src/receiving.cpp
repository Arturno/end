#include "../headers/receiving.hpp"
using namespace std;

void odbieranieUDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas,int packet_size ,unsigned int &counter, int &state, class CheckPackets &chk)
{
    thread tututu(check, ref(chk), ref(state));
    const int socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    socklen_t len = sizeof(RX_meas);
    if (bind(socket_, (struct sockaddr *)&RX_meas, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    while (state)
    {
        //if(((spr.dodawanie+1)%100)==spr.sprawdzanie)
        //{
        //     cout<<"errrr"<<endl;
        // }
        if (recvfrom(socket_, chk.add(), packet_size, 0, (struct sockaddr *)&RX_meas, &len) < 0)
        {
            perror("recvfrom() ERROR");
            exit(4);
        }
        /*int nrpakietu;
        strncpy(przeniesienie, buffer, 10);
        nrpakietu = atoi(przeniesienie);
        cout<<nrpakietu<<" ";
        strncpy(bufor, &(buffer[10]),sizeof(bufor));
        cout<<bufor<<endl;*/
        counter++;
    }
    tututu.join();
    //spr.pomiar();
    shutdown(socket_, SHUT_RDWR);
}

void odbieranieUDPLite(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu, int kodowanie,unsigned int &licznik, int &stan)
{
    char buffer[rozmiar_pakietu] = {};
    const int socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDPLITE);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    setsockopt(socket_, SOL_UDPLITE, UDPLITE_RECV_CSCOV, &kodowanie, sizeof(int));
    socklen_t len = sizeof(RX);
    if (bind(socket_, (struct sockaddr *)&RX, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }
    while (stan)
    {
        if (recvfrom(socket_, buffer, sizeof(buffer), 0, (struct sockaddr *)&RX, &len) < 0)
        {
            perror("recvfrom() ERROR");
            exit(4);
        }
        licznik++;
    }
    shutdown(socket_, SHUT_RDWR);
}

void odbieranieTCP(struct sockaddr_in TX, struct sockaddr_in RX, int rozmiar_pakietu,unsigned int &licznik, int &stan)
{
    const int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[rozmiar_pakietu] = {};
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }

    socklen_t len = sizeof(TX);
    int opt = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(socket_, (struct sockaddr *)&RX, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    if (listen(socket_, 10) < 0)
    {
        perror("listen() ERROR");
        exit(4);
    }

    const int TXSocket = accept(socket_, (struct sockaddr *)&TX, &len);
    if (TXSocket < 0)
    {
        perror("accept() ERROR");
    }
    while (stan)
    {
        if (recv(TXSocket, buffer, sizeof(buffer), 0) <= 0)
        {
            perror("recv() ERROR");
            exit(5);
        }
        licznik++;
    }
    shutdown(TXSocket, SHUT_RDWR);
    shutdown(socket_, SHUT_RDWR);
}
