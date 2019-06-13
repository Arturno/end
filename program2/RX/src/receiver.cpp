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
    ControlRX ctr(parameters.bitrate, parameters.packet_size);
    CheckPackets chk(parameters.packet_size, parameters.protocol);
    connect(socketTCP_, (struct sockaddr *)&TX_TCP, sizeof(TX_TCP));

    if (send(socketTCP_, buffer, sizeof(buffer), 0) <= 0)
    {
        perror("send() ERROR");
        exit(6);
    }
    //koniec ogolnego

    parameters.print();
    thread sterowanieProgramem(Control_RX, ref(ctr), socketTCP_);

    thread Output(meas_and_save, ref(parameters),ref(ctr), ref(chk));
    thread poz(position, ref(ctr));


    switch (parameters.protocol)
    {
    case 0:
    {
        odbieranieUDP(TX_meas, RX_meas, ctr.packet_size, ctr.counter, ctr.state, chk);
        break;
    }
    case 1:
    {
        odbieranieUDPLite(TX_meas, RX_meas, ctr.packet_size, parameters.coverage, ctr.counter, ctr.state);
        break;
    }
    case 2:
    {
        odbieranieTCP(TX_meas, RX_meas, ctr.packet_size, ctr.counter, ctr.state);
        break;
    }
    }
    

    Output.join();
    sterowanieProgramem.join();
    poz.join();

    shutdown(socketTCP_, SHUT_RDWR);
}

