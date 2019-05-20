#include "../headers/adaptation.hpp"

using namespace std;
void adaptation(ControlTX &ctr, int PID_time)
{
    usleep(PID_time*1000);
    int send;
    int if_send = 0;
    PID pid = PID(PID_time*0.001, 200, -200, 0.1, 0.01, 0.5);
    while (ctr.state)
    {
        int previously_send = ctr.counter / ctr.packet_group;
        int target_delay = 1000000 / (ctr.to_send/ctr.packet_group);
        //cout<<ctr.counter<<endl;
        usleep(PID_time*1000);
        int send_packets = ctr.counter / ctr.packet_group;
        if (previously_send <= send_packets)
        {
            send = send_packets - previously_send;
        }
        else
        {
            send = UINT_MAX - previously_send + send_packets;
        }
        //cout<<"Counter:"<<ctr.counter<<endl;
        //cout<<"Wyslano: "<<send<<endl;
        if (send != 0)
        {
            double current_delay = (PID_time*1000) / send;
            double delay_diff = current_delay - target_delay;
            cout<<"Roznica "<< delay_diff<<endl;
            cout << "OP obecne:" << current_delay << " " << target_delay << endl;
            cout << "Opoznienie" << ctr.delay << endl;
            double inc = pid.calculate(0, delay_diff);
            
            //cout << "inc " << inc << endl;
            ctr.delay += inc;
            cout<<"OP:"<<ctr.delay<<" INC:"<<inc<<endl;
            if(ctr.delay < 0)
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
