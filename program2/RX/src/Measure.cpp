#include "../headers/Measure.hpp"

Measure::Measure()
{

}

string Measure::getResult()
{
    string result;
    result += to_string(position) + "\t";
    result += to_string(signal_level) + "\t";
    result += to_string(signal_quality) + "\t";
    result += to_string(received) + "\t";
    result += to_string(bitrate) + "\t";
    result += to_string(error);
    return result;
} 

void Measure::collectData(ControlRX &ctr, CheckPackets &chk)
{
    getsignalinfo();
    if (previously_received <= ctr.counter)
    {
        received = ctr.counter - previously_received;
    }
    else
    {
        received = UINT_MAX - previously_received;
    }
    previously_received = ctr.counter;
    position = ctr.position;
    bitrate = (double)received /(125000/ctr.packet_size);
    error =chk.pomiar();

}

void Measure::getsignalinfo()
{
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
    signal_level = level;
    signal_quality = link;
}