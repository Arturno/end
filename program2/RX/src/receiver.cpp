#include "../headers/receiver.hpp"

void receiver()
{
    cout<<"TRYB ODBIORCY"<<endl;
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
    struct sockaddr_in RX_TCP;
    RX_TCP.sin_family = AF_INET;
    RX_TCP.sin_port = htons(9998)
    ;
    struct sockaddr_in RX_meas;
    RX_meas.sin_family = AF_INET;
    RX_meas.sin_port = htons(9999);
    cout << "Podaj adres strony nadawczej:" << endl;
    char IP_address[255];
    cin >> IP_address;

    if (inet_pton(AF_INET, IP_address, &TX_TCP.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }

    if (inet_pton(AF_INET, "127.0.0.1", &RX_TCP.sin_addr) <= 0)
    {
        perror("inet_pton() ERROR");
        exit(1);
    }
    if (inet_pton(AF_INET, IP_address, &TX_meas.sin_addr) <= 0)
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
    connect(socketTCP_, (struct sockaddr *)&TX_TCP, sizeof(TX_TCP));
    char buffer[250];
    memset(buffer, 0, sizeof(buffer));

    //tworzenie struktury zawierajacej informacje do strony TX 
    TransmissionArrangement parameters;
    parameters.tochar(buffer);

    //tworzenie struktury kontrolujacej dzialanie programu
    ControlRX ctr(parameters.bitrate, parameters.packet_size);

    //tworzenie struktury do sprawdzania przychodzacych pakietow
    CheckPackets chk(parameters.packet_size, parameters.protocol);


    //wysłanie parametrów do strony TX
    if (send(socketTCP_, buffer, sizeof(buffer), 0) <= 0)
    {
        perror("send() ERROR");
        exit(6);
    }
    
    //wątek do sterowania programem
    thread Control(Control_RX, ref(ctr), socketTCP_);

    //wątek do wypisywania wyników i zaisu ich do pliku
    thread Output(meas_and_save, ref(parameters), ref(ctr), ref(chk));

    //wątek do odbierania informacji o pozycji urządzenia
    thread Pos(position, ref(ctr));
    parameters.print();
    cout << "#############################################################################" << endl;
    cout << "Sterowanie programem" << endl;
    cout << "M xxx - zmiana przepływności na wartość xxx Mb/s" << endl;
    cout << "E - zakonczenie pomiaru" << endl;

    //odbieranie odpowiedniego typu pakietów
    switch (parameters.protocol)
    {
    case 0:
    {
        odbieranieUDP(TX_meas, RX_meas, ctr.packet_size, ctr.counter, ctr.state, chk);
        break;
    }
    case 1:
    {
        odbieranieUDPLite(TX_meas, RX_meas, ctr.packet_size,ctr.counter, ctr.state, chk, parameters.coverage);
        break;
    }
    }

    //konczenie wątków
    Output.join();
    Control.join();
    Pos.join();

    //zamykanie gniazd
    shutdown(socketTCP_, SHUT_RDWR);
}
