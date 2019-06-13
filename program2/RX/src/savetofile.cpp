#include "../headers/savetofile.hpp"
#include <fstream>

string cr_filename(class TransmissionArrangement parameters)
{
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

string signal_level()
{
    string signal_level;
    int link, level;
    string line;
    string quality;
    fstream file;
    file.open("/proc/net/wireless", ios::in);
    getline(file, line);
    getline(file, line);
    if(getline(file, line))
    {
        quality = line.substr(15,15);
        link=stoi(quality.substr(0,2));
        level=stoi(quality.substr(5,7));
    }
    else
        level =-256;
    file.close();
    signal_level = to_string(level) + ",\t" + to_string(link);
    return signal_level;
}

void meas_and_save(TransmissionArrangement &parameters , ControlRX &ctr, CheckPackets &chk)
{
    unsigned int  counter = 1;
    int timeout = 0;
    fstream file;
    string name = cr_filename(parameters);
    string temp = name.substr(name.find("_")+1, name.find("."));
    file.open(name, ios::app);
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
    file << "No; zadana_przeplywnosc; polozenie; poziom_sygnalu; jakosc_linku; odebrane_pakiety; przepływność; stracone_pakiety; flaga_zamiany; flaga_błledu; ber"<<endl;
    Measure meas;
    while (ctr.state)
    {
        sleep(1);
        meas.collectData(ctr,chk);
        file <<counter<<";"<< ctr.bitrate<<";"<<meas.getResult()<<endl;
        counter++;
        if(meas.received == 0)
            timeout++;
        else
            timeout = 0;
        if(timeout == 10)
            ctr.state =0;
    }
    file.close();
}

