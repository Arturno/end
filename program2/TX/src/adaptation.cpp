#include "../headers/adaptation.hpp"

using namespace std;
void adaptation(ControlTX &ctr, int PID_time)
{
    int send;                     /**< liczba wysłanych pakietów w ciągu ostatniego okresu adapacji */
    int if_send = 0;              /**< liczba okresów w, w których nie został wysłany ani jeden pakiet */

    //odczekanie jednego okresu adaptacji w celu uruchomienia wszystkich elementów programu
    usleep(PID_time*1000);

    //stworzenie obiekt regulatora PID z zadanymi parametrami
    PID pid = PID(PID_time*0.001, 200, -200, 0.1, 0.01, 0.5);

    //główna fukncja programu wyznaczająca korekcję opóżnienia co zadany przez użytkownika okres czasu
    while (ctr.state)
    {   
        //aktualna liczba wysłanych grup pakietów
        int previously_send = ctr.counter / ctr.packet_group;
        //wyznaczenie docelowego opoznienia pakietów
        int target_delay = 1000000 / (ctr.to_send/ctr.packet_group);
        //odczekanie jednego okresu adaptacji
        usleep(PID_time*1000);
        //liczba wysłanych grup pakietów wliczając jeden dodatkowy okres adaptacji
        int send_packets = ctr.counter / ctr.packet_group;

        //wyznaczenie i zapisanie do zmiennej send liczby grup pakietów wysłanych podczas jednego okresu czasu
        if (previously_send <= send_packets)
        {
            send = send_packets - previously_send;
        }
        else
        {
            send = UINT_MAX - previously_send + send_packets;
        }

        //sprawdzenie czy chociaż jedna grupa została wysłana
        if (send != 0)
        {
            //wyznaczenie opóznienia, na podstawie liczby wysłanych grup pakietów, oraz różnicy do opóżnienia docelowego
            double current_delay = (PID_time*1000) / send;
            double delay_diff = current_delay - target_delay;

            //obliczenie za pomocą regulatora PID korekty opóżnienia, tak aby różnica między aktualnym opóźnieniem i docelowym była równa zero
            double inc = pid.calculate(0, delay_diff);
            
            //aktualizacja opóźnienia
            ctr.delay += inc;

            //zabezpieczenie przed ujemnymi wartościami opóźnienia
            if(ctr.delay < 0)
            {
                ctr.delay =0;
            }

            //wyzorowanie licznika okresów, w których nie został wysłany przynajmniej jeden pakiet
            if_send = 0;
        }
        else
        {
            //zwiekszenie licznika okresów, w których nie został wysłany przynajmniej jeden pakiet 
            if_send++;
            //w przypadku gdy przez 10 ostatnich sekund nie został wysłany żaden pakiet program kończy działanie
            if (if_send == 10000000 / (PID_time*1000))
            {
                cout <<"Nie wysłano pakietu od 10s - koniec programu"<< endl;
                ctr.end_program();
                break;
            }
        }
    }
}
