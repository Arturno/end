#include "../headers/adaptation.hpp"

using namespace std;
void adaptation(ControlTX &ctr, int PID_time)
{
    sleep(1);
    int send_packets = ctr.counter / ctr.packet_group;
    int send;
    int if_send = 0;
    PID pid = PID(0.1, 500, -500, 0.1, 0.01, 0.5);
    while (ctr.state)
    {
        int previously_send = send_packets;
        int target_delay = 1000000 / (ctr.to_send/ctr.packet_group);
        usleep(PID_time*1000);
        if (previously_send <= send_packets)
        {
            send = send_packets - previously_send;
        }
        else
        {
            send = INT_MAX - previously_send + send_packets - INT_MIN;
        }
        //cout<<"Wyslano: "<<wyslane<<endl;
        if (send != 0)
        {
            double current_delay = (PID_time*1000) / send;
            double delay_diff = current_delay - target_delay;
            //cout<<"Roznica"<< roznica<<endl;
            //cout << "OP obecne:" << opoznienie_obecne << " " << opoznienie_docelowe << endl;
            //cout << "Opoznienie" << opoznienie << endl;
            double inc = pid.calculate(0, delay_diff);
            
            //cout << "inc " << inc << endl;
            ctr.delay += inc;
            //cout<<"OP:"<<opoznienie<<" INC:"<<inc<<endl;
            if(ctr.delay<0)
            {
                ctr.delay =0;
                //cout<<"MAX"<<endl;
            }
            if_send = 0;
        }
        else
        {
            if_send++;
            if (if_send == 10000000 / (PID_time*1000))
            {
                cout <<"Nie wysłano pakietu od 10s - koniec programu"<< endl;
                ctr.end_program();
                break;
            }
        }
    }
}
