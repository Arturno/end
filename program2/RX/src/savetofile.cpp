#include "../headers/Check.hpp"
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

void meas_and_save(class TransmissionArrangement &parameters,int &position,int &counter, int &state, class CheckPackets &chk)
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
    int previously_send = 0;
    int send = 0;
    int no_of_meas =0;
    while (state)
    {
        no_of_meas ++;
        previously_send = send;
        sleep(1);
        if (previously_send <= counter)
        {
            send = counter - previously_send;
        }
        else
        {
            send = INT_MAX - previously_send + counter - INT_MIN;
        }
        file << no_of_meas<<",\t "<<position<<",\t"<< signal_level()<<",\t " <<  send  << ",\t "<< (double)send /(125000/parameters.packet_size)<< ",\t "<< chk.pomiar()<<endl;
    }
    file.close();
}

