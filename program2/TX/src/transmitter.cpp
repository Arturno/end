#include "../headers/transmitter.hpp"

void transmitter()
{
    std::cout<<"TRYB NADAWCY"<<std::endl;

    //utworzenie struktur przechowujacych informacje o obu stronach (TX i RX)

    //port po stronie TX do wymiany informacji sterujących z wykorzystaniem protokołu TCP
    struct sockaddr_in TX_TCP;
    TX_TCP.sin_family = AF_INET;
    TX_TCP.sin_port = htons(8888);

    //port po stronie TX do przeprowadzenia testu
    struct sockaddr_in TX_meas;
    TX_meas.sin_family = AF_INET;
    TX_meas.sin_port = htons(8889);

    //odpowiedniki powyższych portów przechowujące informacje o RX
    struct sockaddr_in RX_TCP = {};
    struct sockaddr_in RX_meas = {};

    //ustawienie adresacji po stronie TX
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

    //funkcja pozwalająca na ponowne użycie portu (umożliwia uruchamianie programu kilka razy z rzędu)
    int opt = 1;
    setsockopt(socketTCP_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //bindowanie socketu do portu
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
    cout<<"Oczekiwanie na przyłączenie się strony odbiorczej."<<endl;

    //oczekiwanie na przyjscie połączenie od strony RX
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
    //uzupełnienie informacji o stronie RX
    RX_meas = RX_TCP;
    RX_meas.sin_port = htons(9999);
    /* 
    char buffer_ip[128] = {};
    std::cout << "IP RX:  ..........  " << inet_ntop(AF_INET, &RX_meas.sin_addr, buffer_ip, sizeof(buffer_ip)) << endl;
    std::cout << "port:  ...........  " << ntohs(RX_meas.sin_port) << endl;
    */

    //stworzenie i wypisanie struktury TransmissionArrangement na podstawie informacji odebranych od RX
    TransmissionArrangement parameters(buffer);
    parameters.print();

    //stworzenie struktury odpowiadajacej za sterowanie programem
    ControlTX ctr(parameters.bitrate, parameters.packet_size);
    ControlTX &rrr = ctr;

    //wątek odpowiadający za komunikacje z użytkownikiem i stroną RX
    thread Control(Control_TX, ref(ctr), RXSocket);

    //wątek odpowiadajacy za sterowanie nadawaniem pakietów tak aby uzyskać zadaną przepływność
    thread Adapt(adaptation, ref(ctr), parameters.PID_time);

        //thread pomiaaar(pomiar, ref(ster.stan), ref(ster.licznik), ref(ster.grupa_pakietow), ster.rozmiar_pakietu);

    //wysyłanie pakietów do strony RX
    switch (parameters.protocol)
    {
        case 0:
        {
            send_UDP(TX_meas, RX_meas, rrr);
            break;
        }
        case 1:
        {
            send_UDPLite(TX_meas, RX_meas, parameters.coverage, ctr);
            break;
        }
    }

    //oczekiwanie na zakończenie wątków
    Control.join();
    Adapt.join();
    
    //zamykanie gniazd
    shutdown(RXSocket, SHUT_RDWR);
    shutdown(socketTCP_, SHUT_RDWR);

}
