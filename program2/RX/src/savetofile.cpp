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

    fstream file;
    file.open(cr_filename(parameters), ios::app);
    file<<"Protokół:        "<<parameters.protocol<<endl;
    file<<"Rozmiar pakietu: "<<parameters.packet_size<<endl;
    if(parameters.protocol ==1)
    {
        file<<"Kodowanie:       "<<parameters.coverage<<endl;
    };
    file << "Numer pomiaru, polozenie, poziom sygnału, jakość linku, liczba odebranych pakietów, przepływność"<<endl;
    Measure meas;
    while (ctr.state)
    {
        sleep(1);
        meas.collectData(ctr,chk);
        file <<meas.getResult()<<endl;
    }
    file.close();
}

