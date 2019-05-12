#include "../headers/transmitter.hpp"

void transmitter()
{
    std::cout<<"OOK"<<std::endl;
    struct sockaddr_in TX_TCP = {
        .sin_family = AF_INET,
        .sin_port = htons(8888)};
    struct sockaddr_in TX_meas = {
        .sin_family = AF_INET,
        .sin_port = htons(8889)};
    struct sockaddr_in RX_TCP = {};
    struct sockaddr_in RX_meas = {};

    //czesc TCP
    if (inet_pton(AF_INET, "127.0.0.1", &TX_TCP.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }
    if (inet_pton(AF_INET, "127.0.0.1", &TX_meas.sin_addr) <= 0)
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

    socklen_t len = sizeof(TX_TCP);
    int opt = 1;
    setsockopt(socketTCP_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(socketTCP_, (struct sockaddr *)&TX_TCP, len) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    if (listen(socketTCP_, 10) < 0)
    {
        perror("listen() ERROR");
        exit(4);
    }
    char buffer[250];

    const int RXSocket = accept(socketTCP_, (struct sockaddr *)&RX_TCP, &len);
    if (RXSocket < 0)
    {
        perror("accept() ERROR");
    }

    memset(buffer, 0, sizeof(buffer));
    if (recv(RXSocket, buffer, sizeof(buffer), 0) <= 0)
    {
        perror("recv() ERROR");
        exit(5);
    }

    RX_meas = RX_TCP;
    RX_meas.sin_port = htons(9999);
    char buffer_ip[128] = {};
    std::cout << "IP RX:  ..........  " << inet_ntop(AF_INET, &RX_meas.sin_addr, buffer_ip, sizeof(buffer_ip)) << endl;
    std::cout << "port:  ...........  " << ntohs(RX_meas.sin_port) << endl;

    TransmissionArrangement parameters(buffer);
    parameters.print();
    ControlTX ctr(parameters.bitrate, parameters.packet_size);
    cout<<"#############################################################################"<<endl;
    cout<<"Sterowanie programem"<<endl;
    cout<<"M xxx - zmiana przepływności na wartość xxx Mb/s"<<endl;
    cout<<"E - zakonczenie pomiaru"<<endl;


        thread UserCommunication(Control_TX, ref(ctr), RXSocket);
        thread Adapt(adaptation, ref(ctr), parameters.PID_time);
        //thread pomiaaar(pomiar, ref(ster.stan), ref(ster.licznik), ref(ster.grupa_pakietow), ster.rozmiar_pakietu);

        switch (parameters.protocol)
        {
        case 0:
        {
            //thread wysylanie(wysylanieUDP, TX, RX, ref(parametry.rozmiar_pakietu), ref(ster.opoznienie), ref(ster.grupa_pakietow), ref(ster.licznik), ref(ster.stan));
            send_UDP(TX_meas, RX_meas, ctr.packet_size, ctr.delay, ctr.packet_group, ctr.counter, ctr.state);
            break;
        }
        case 1:
        {
            //thread wysylanie(wysylanieUDPLite, TX, RX, ref(parametry.rozmiar_pakietu), ref(ster.opoznienie), ref(ster.grupa_pakietow),parametry.kodowanie, ref(ster.licznik), ref(ster.stan));
            send_UDPLite(TX_meas, RX_meas, ctr.packet_size, ctr.delay, ctr.packet_group, parameters.coverage, ctr.counter, ctr.state);
            break;
        }
        case 2:
        {
            //thread wysylanie(wysylanieTCP, TX, RX, ref(parametry.rozmiar_pakietu), ref(ster.opoznienie), ref(ster.grupa_pakietow), ref(ster.licznik), ref(ster.stan));
            send_TCP(TX_meas, RX_meas, ctr.packet_size, ctr.delay, ctr.packet_group, ctr.counter, ctr.state);
            break;
        }
        }
    UserCommunication.join();
    Adapt.join();
        //pomiaaar.join();
    
    //wysylanie.join()
    //zamykanie gniazd
   
    shutdown(RXSocket, SHUT_RDWR);
    shutdown(socketTCP_, SHUT_RDWR);

}
