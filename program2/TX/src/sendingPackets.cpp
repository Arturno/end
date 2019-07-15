#include "../headers/sendingPackets.hpp"

using namespace std;

void send_UDP(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, ControlTX &ctr)
{
    //utworzenie pakietu o podanym przez użytkownika rozmiarze
    char buffer[ctr.packet_size] = {};
    srand(50);
    for (int i = 12; i < ctr.packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    buffer[ctr.packet_size] = '\0';
    //utworzenie i zbindowanie gniazda
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
    //funkcja odpowiadajaca za ciągłe wysyłanie pakietów
    while (ctr.state)
    {
        //funkcja realizująca wysłanie całej grupy pakietów
        for (int i = 0; i < ctr.packet_group; i++)
        {
            //nadanie pakietowi jego numeru
            sprintf(buffer, "%d", ctr.counter);
            //wysłanie pakietu do strony RX
            if (sendto(socket_, buffer, sizeof(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            //zwiększenie licznika wysłanych pakietów
            ctr.counter++;
        }
        //opóźnienie wysyłania pakietów w celu otrzymania zadanej przepływności
        usleep(ctr.delay);
    }

    //w przypadku zakonczenia działania programu program odczeka 0,1 sekundy i wysle pakiet w strone RX w celu poprawnego zakonczenia dzialania po stronie RX
    usleep(100000);
    if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
    {
        perror("sendto() ERROR");
        exit(5);
    };
    //zamknięcie gniazd
    shutdown(socket_, SHUT_RDWR);
}
void send_UDPLite(struct sockaddr_in TX_meas, struct sockaddr_in RX_meas, int coverage, ControlTX &ctr)
{
    //utworzenie pakietu o podanym przez użytkownika rozmiarze
    char buffer[ctr.packet_size] = {};
    srand(50);
    for (int i = 10; i < ctr.packet_size; i++)
    {
        buffer[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    buffer[ctr.packet_size] = '\0';

    //utworzenie i zbindowanie gniazda
    const int socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDPLITE);
    if (socket_ < 0)
    {
        perror("socket() ERROR");
        exit(2);
    }
    //przypisanie odpowiedniego kodowania
    setsockopt(socket_, SOL_UDPLITE, UDPLITE_SEND_CSCOV, &coverage, sizeof(int));
    if (bind(socket_, (struct sockaddr *)&TX_meas, sizeof(TX_meas)) < 0)
    {
        perror("bind() ERROR");
        exit(3);
    }

    //funkcja odpowiadajaca za ciągłe wysyłanie pakietów
    while (ctr.state)
    {
        //funkcja realizująca wysłanie całej grupy pakietów
        for (int i = 0; i < ctr.packet_group; i++)
        {
            //nadanie pakietowi jego numeru
            sprintf(buffer, "%d", ctr.counter);
            if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
            {
                perror("sendto() ERROR");
                exit(5);
            }
            //zwiększenie licznika wysłanych pakietów
            ctr.counter++;
        }
        //opóźnienie wysyłania pakietów w celu otrzymania zadanej przepływności
        usleep(ctr.delay);
    }
     //w przypadku zakonczenia działania programu program odczeka 0,1 sekundy i wysle pakiet w strone RX w celu poprawnego zakonczenia dzialania po stronie RX
    usleep(100000);
    if (sendto(socket_, buffer, strlen(buffer), 0, (struct sockaddr *)&RX_meas, sizeof(RX_meas)) < 0)
    {
        perror("sendto() ERROR");
        exit(5);
    };
    //zamknięcie gniazd
    shutdown(socket_, SHUT_RDWR);
}