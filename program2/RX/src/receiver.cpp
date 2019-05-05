#include "../headers/receiver.hpp"


void receiver()
{

    std::cout<<"OK"<<std::endl;
    
    struct sockaddr_in TX_TCP = {
        .sin_family = AF_INET,
        .sin_port = htons(8888)};
    struct sockaddr_in TX_meas = {
        .sin_family = AF_INET,
        .sin_port = htons(8889)};
    struct sockaddr_in RX_TCP = {
        .sin_family = AF_INET,
        .sin_port = htons(9998)};
    struct sockaddr_in RX_meas = {
        .sin_family = AF_INET,
        .sin_port = htons(9999)};
    //cout << "TRYB RECEIVER" <<endl;

    if (inet_pton(AF_INET, "127.0.0.1", &TX_TCP.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }

    if (inet_pton(AF_INET, "127.0.0.1", &RX_TCP.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }
    if (inet_pton(AF_INET, "127.0.0.1", &TX_meas.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }
    if (inet_pton(AF_INET, "127.0.0.1", &RX_meas.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }
    const int socketTCP_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socketTCP_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    socklen_t len = sizeof(RX_TCP);
    int opt = 1;
    setsockopt(socketTCP_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(socketTCP_, (struct sockaddr *)&RX_TCP, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    char buffer[250];
    memset(buffer, 0, sizeof(buffer));
    TransmissionArrangement parameters;
    parameters.tochar(buffer);
    parameters.print();
    connect(socketTCP_, (struct sockaddr *)&TX_TCP, sizeof(TX_TCP));

    if (send(socketTCP_, buffer, sizeof(buffer), 0) <= 0)
    {
        perror("send() ERROR");
        exit(6);
    }
    //koniec ogolnego
    int pol=0;
    SterowanieRX sterRX(pol);
    CheckPackets chk;


    thread sterowanieProgramem(ControlRX, ref(sterRX.stan), ref(parameters.bitrate), socketTCP_);

    thread Output(meas_and_save, ref(parameters),ref(sterRX.polozenie), ref(sterRX.licznik), ref(sterRX.stan), ref(chk));
    //thread poz(pozycja, ref(sterRX.polozenie), ref(sterRX.stan));


    switch (parameters.protocol)
    {
    case 0:
    {
        odbieranieUDP(TX_meas, RX_meas, parameters.packet_size, sterRX.licznik, sterRX.stan, ref(chk));
        break;
    }
    case 1:
    {
        odbieranieUDPLite(TX_meas, RX_meas, parameters.packet_size, parameters.coverage,sterRX.licznik, sterRX.stan);
        break;
    }
    case 2:
    {
        odbieranieTCP(TX_meas, RX_meas, parameters.packet_size, sterRX.licznik, sterRX.stan);
        break;
    }
    }
    

    Output.join();
    sterowanieProgramem.join();
    //poz.join();

    shutdown(socketTCP_, SHUT_RDWR);
}

