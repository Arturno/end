#include "../headers/savetofile.hpp"
#include <fstream>

string cr_filename(class TransmissionArrangement parameters)
{
    //utworzenie nazwy pliku na podstawie parametrów testu
    string filename = "results/";
    tm *temp;
    temp = localtime(&parameters.date);
    filename += parameters.name;
    string tempp;
    filename += '_';
    sprintf((char*)tempp.c_str(), "%d",1900 + temp->tm_year);
    filename += tempp.c_str();
    filename += '-';
    sprintf((char*)tempp.c_str(), "%d",temp->tm_mon);
    filename += tempp.c_str();
    filename += '-';
    sprintf((char*)tempp.c_str(), "%d",temp->tm_mday);
    filename += tempp.c_str();
    filename += '_';
    sprintf((char*)tempp.c_str(), "%d",temp->tm_hour);
    filename += tempp.c_str();
    filename += ':';
    sprintf((char*)tempp.c_str(), "%d",temp->tm_min);
    filename += tempp.c_str();
    filename += ':';
    sprintf((char*)tempp.c_str(), "%d",temp->tm_sec);
    filename += tempp.c_str();
    filename += ".csv";
    return filename;
}

void meas_and_save(TransmissionArrangement &parameters , ControlRX &ctr, CheckPackets &chk)
{
    //licznik zapisanych wyników, równoznaczny z liczbą sekund od początku testu
    unsigned int  counter = 1;
    //licznik, czasu w którym nie odebrano żadnego pakietu
    int timeout = 0;

    //utworzenie pliku z wynikami testu
    fstream file;
    string name = cr_filename(parameters);
    string temp = name.substr(name.find("_")+1, (name.length() - name.find("_") - 5));
    file.open(name, ios::app);

    //zapis ogólnych informacji i parametrów stałych podczas trwania testu
    file<<"#PARAMETRY: "<<endl;
    file << "Nazwa testu;"<<parameters.name<< endl;
    file << "Data testu;"<<temp<<endl;
    if(parameters.protocol == 0)
        file<<"Protokol;UDP ("<<parameters.protocol<<")"<<endl;
    else
        file<<"Protokół;UDP-Lite ("<<parameters.protocol<<")"<<endl;
    file<<"Rozmiar pakietu;"<<parameters.packet_size<<endl;
    if(parameters.protocol ==1)
    {
        file<<"Kodowanie;"<<parameters.coverage<<endl;
    };
    file << "#POMIARY: "<<endl;
    file << "No;zadana_przeplywnosc;polozenie;poziom_sygnalu;jakosc_linku;odebrane_pakiety;przeplywnosc;stracone_pakiety;flaga_zamiany;flaga_bledu;ber;kanal;przepustowosc_kanalu;szerokosc_kanalu;MCS;NSS;SGI"<<endl;
    cout << "No\tpolozenie poziom_sygn\tjakosc_linku\tprzeplywnosc\tstracone\tber"<<endl;

    //utworzenie obiektu do zbierania parametrów podczas testu
    Measure meas;
    while (ctr.state)
    {
        //odczekanie sekundy
        sleep(1);
        //pomiar parametrów 
        meas.collectData(ctr,chk);
        //zapisanie wszystkich parametrów do pliku
        file <<counter<<";"<< ctr.bitrate<<";"<<meas.getResult()<<endl;
        //wypisanie najważniejszych paraketrów w konsoli
        cout <<counter<<"\t"<< meas.position<<"\t "<<meas.signal_level<<"\t\t"<<meas.signal_quality<<"\t\t"<<meas.bitrate<<"\t\t"<< meas.lost<<"\t\t"<< meas.error<<endl;
        //zwiększenie licznika czasu
        counter++;
        //sprawdzenie czy w ostatniej sekundzie zostały odebrane jakiekolwiek pakiety
        if(meas.received == 0)
            timeout++;
        else
            timeout = 0;
        //w przypadku nieodebrania żadnego pakietu przez 10 sekund, program konczy pomiar
        if(timeout == 10)
        {
            ctr.state =0;
            cout<<"Nie odebrano pakietu od 10 sekund. Kończenie programu."<<endl;
        }
    }
    //zamkniecie pliku
    file.close();
}

