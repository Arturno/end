#include "../headers/Check.hpp"

CheckPackets::CheckPackets(int packetsize, int protocol)
{
    adding = 1;
    check = 0;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    packet_size = packetsize;
}

char *CheckPackets::add()
{
    int temp = adding;
    adding = (adding + 1) % TABLE_SIZE;
    if (temp == check)
    {
        err = true;
        cout << "ADD TO FAST" << endl;
    }
    added++;
    return buffer[temp];
}

int CheckPackets::toCheck()
{
    if ((check + 2) % TABLE_SIZE == adding)
    {
        //cout << "CZEKA" << endl;
        return 1;
    }
    else
    {
        check = (check + 1) % TABLE_SIZE;
        //cout << "SPRAWDZONE " << sprawdzanie << endl;
        calculate();
        //cout << bufor[sprawdzanie] << endl;
        checked++;
        return 0;
    }
}

double CheckPackets::getResults()
{
    //cout << "DODANE " << dodane << endl;
    //cout << "SPRAWDZONE " << sprawdzone << endl;
    //cout << "BLAD" << blad << endl;
    errors = (double)((checked * packet_size) - bit_errors) / (checked * packet_size) * 100;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    return errors;
}

void check(class CheckPackets &chk, int &state)
{
    while (state)
    {
        if (chk.toCheck())
            usleep(1000);
    }
}
/*

void Sprawdzanie::spr()
{
    int nrpakietu;
    usleep(90000);
    if (((sprawdzanie + 1) % ROZMIAR_TABLICY) != dodawanie)
    {
        sprawdzanie = (sprawdzanie + 1) % ROZMIAR_TABLICY;
        //cout << "SPR" << sprawdzanie;
        nrpakietu = tablica[sprawdzanie];
        //cout << "AKT" << aktualny << "NRPAK" << nrpakietu << endl;
        if (aktualny == nrpakietu)
        {
            aktualny = (aktualny + 1) % 100;
        }
        else
        {
            if (aktualny < nrpakietu)
            {
                stracone += (nrpakietu - aktualny);
                aktualny = (nrpakietu + 1) % 100;
                cout << "stracone" <<stracone<< endl;
            }
            else
            {
                if (aktualny > nrpakietu)
                {
                    zamienione = true;
                    stracone--;
                    cout << "Zamienione" << endl;
                }
            }
        }
        sprawdzone++;
    }
}

void Sprawdzanie::wypisanie()
{
    cout<<"SPRAWDZONE: "<<sprawdzone<<endl;
    cout<<"Zamienione: "<<zamienione<<endl;
    cout<<"Stracone: "<<stracone<<endl;
}
*/
void CheckPackets::checkOrder(unsigned int received_packet)
{
    //fstream file;
    //file.open("test.txt", ios::app);
    //cout<< "A " << packet_number << "NR " << received_packet;
    //cout<< received_packet << endl;
    if (((packet_number - received_packet) % UINT_MAX) > 1000)
    {
        //packet_number = received_packet;
        lost++;
        err = true;
        //cout << "A" << packet_number << "NR" << received_packet << endl;
        //file<<" BLAD"<<endl;
    }
    if (packet_number == received_packet)
    {
        packet_number = (received_packet + 1) % UINT_MAX;
        //file<<" OK"<<endl;
    }
    else
    {
        if (packet_number < received_packet)
        {
            lost += (received_packet - packet_number);
            packet_number = (received_packet + 1) % UINT_MAX;
            //file<<" PN<RP"<<endl;
            //cout<<"stracone"<<endl;
        }
        else
        {
            if (packet_number > received_packet)
            {
                not_in_order = true;
                if(lost > 0)
                    lost--;
                //file<<" Zamienione"<<endl;
                //cout << "A" << packet_number << "NR" << received_packet << endl;
            }
        }
    }
    //file.close();
}
void CheckPackets::calculate()
{
    unsigned int received_packet;
    char temp[12];
    char buf[packet_size - 12];
    char original_package[packet_size - 12];
    srand(50);
    for (int i = 0; i < (packet_size - 12); i++)
    {
        original_package[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    original_package[packet_size - 12] = '\0';
    //wzor[100] = 'x';
    //cout<<"ODEBRANE"<<wzor<<endl;
    //if (((sprawdzanie + 1) % 100) != dodawanie)
    //{
    //cout<<"NRPakietu"<<nrpakietu<<endl;
    //cout<<"Dodawanie"<<spr.dodawanie<<endl;
    //cout<<"Sprawdzenie ak"<<spr.sprawdzanie<<endl;
    strncpy(temp, buffer[check], 12);
    received_packet = atoi(temp);
    strncpy(buf, &(buffer[check])[12], (packet_size - 12));
    //cout<<aktualny;
    //cout<<buf<<endl;
    //cout<<bufor<<endl;
    checkOrder(received_packet);

    //cout<<"WZ :"<<wzor<<" " <<"BU :"<<buf<<endl;
    if (protocol == 1)
    {
        for (int i = 0; i < packet_size - 12; i++)
        {
            if (original_package[i] != buf[i])
            {
                //cout<<"WZ :"<<wzor<<" " <<"BU :"<<buf<<endl;
                bit_errors++;
            }
        }
    }
    else
    {
        bit_errors = 0;
    }

    /*
            sprawdzone++;
            //cout << "OKOK" << endl;
            blad+=przeklamane;
            sprawdzanie = (sprawdzanie+1)%100;
        }
        /*
    cout<<"sprawdzone"<<spr.odebraneIsprawdzone<<endl;
    cout<<"blad"<<(double)spr.blad/((double)spr.odebraneIsprawdzone*20)*100<<endl<<endl;
    cout<<"stracone"<<spr.stracone<<endl;
    cout<<"zamienione"<<spr.zamienione<<endl;
    cout<<"err"<<spr.err<<endl;
    */
    // }
}