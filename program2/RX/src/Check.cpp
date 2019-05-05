#include "../headers/Check.hpp"

CheckPackets::CheckPackets()
{
    adding = 1;
    check = 0;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    nrpakietu = 0;
    packet_size = 1000;
}

char *CheckPackets::add()
{
    int temp = adding;
    //cout << "ADDED " << temp << endl;
    adding = (adding + 1) % TABLE_SIZE;
    if (temp == check)
    {
        err = true;
        cout << "ADD TO FAST" << endl;
    }
    added++;
    return buffer[temp];
}

int CheckPackets::spraw()
{
    if ((check + 1) % TABLE_SIZE == adding)
    {
        //cout << "CZEKA" << endl;
        return 1;
    }
    else
    {
        check = (check + 1) % TABLE_SIZE;
        //cout << "SPRAWDZONE " << sprawdzanie << endl;
        test();
        //cout << bufor[sprawdzanie] << endl;
        checked++;
        return 0;
    }
}

double CheckPackets::pomiar()
{
    //cout << "DODANE " << dodane << endl;
    //cout << "SPRAWDZONE " << sprawdzone << endl;
    //cout << "BLAD" << blad << endl;
    bledybledy =(double)((checked * packet_size) - bit_errors) / (checked * packet_size)*100;
    added = 0;
    checked = 0;
    bit_errors = 0;
    lost = 0;
    not_in_order = false;
    err = false;
    return bledybledy;
}

void check(class CheckPackets &chk, int &state)
{
    while (state)
    {
        if (chk.spraw())
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
void CheckPackets::test()
{
    int nrpakietu;
    int przeklamane = 0;
    unsigned int aktualny = 0;
    char przeniesienie[12];
    char buf[packet_size - 12];
    char wzor[packet_size - 12];
    srand(50);
    for (int i = 0; i < (packet_size - 12); i++)
    {
        wzor[i] = ((rand() % ('z' - 'a')) + 'a');
    }
    wzor[packet_size-12]='\0';
    //wzor[100] = 'x';
    //cout<<"ODEBRANE"<<wzor<<endl;
    //if (((sprawdzanie + 1) % 100) != dodawanie)
    //{
        //cout<<"NRPakietu"<<nrpakietu<<endl;
        //cout<<"Dodawanie"<<spr.dodawanie<<endl;
        //cout<<"Sprawdzenie ak"<<spr.sprawdzanie<<endl;
        strncpy(przeniesienie, buffer[check], 12);
        nrpakietu = atoi(przeniesienie);
        strncpy(buf, &(buffer[check])[12], (packet_size - 12));
        //cout<<aktualny;
        //cout<<buf<<endl;
        //cout<<"A"<<aktualny<<"NR"<<nrpakietu<<endl;
        //cout<<bufor<<endl;
        /*
            if (((aktualny - nrpakietu) % INT_MAX) > (INT_MAX / 2))
            {
                aktualny = nrpakietu;
                stracone++;
                err = true;
                cout<<"BLAD"<<endl;
            }
            if (aktualny == nrpakietu)
            {
                aktualny = (aktualny + 1) % INT_MAX;
            }
            else
            {
                if (aktualny < nrpakietu)
                {
                    stracone += (nrpakietu - aktualny);
                    aktualny = (nrpakietu + 1) % INT_MAX;
                    cout<<"stracone"<<endl;
                }
                else
                {
                    if (aktualny > nrpakietu)
                    {
                        zamienione = true;
                        stracone--;
                        cout<<"Zamienione"<<endl;
                    }
                }
            }
            */
        //cout<<"WZ :"<<wzor<<" " <<"BU :"<<buf<<endl;
        for (int i = 0; i < packet_size - 12; i++)
        {
            if (wzor[i] != buf[i])
            {
                //cout<<"WZ :"<<wzor<<" " <<"BU :"<<buf<<endl;
                bit_errors++;
            }
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