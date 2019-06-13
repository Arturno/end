#include "../headers/Measure.hpp"

Measure::Measure()
{

}

string Measure::getResult()
{
    string result;
    result += to_string(position) + ";";
    result += to_string(signal_level) + ";";
    result += to_string(signal_quality) + ";";
    result += to_string(received) + ";";
    result += to_string(bitrate) + ";";
    result += to_string(lost) + ";";
    if(not_in_order)
        result += "true;";
    else
        result +="false;";
    if(err)
        result += "true;";
    else
        result +="false;";
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
    position = ctr.start_position + ctr.position;
    bitrate = (double)received /(125000/ctr.packet_size);
    lost = chk.lost;
    err = chk.err;
    not_in_order = chk.not_in_order;
    error =chk.getResults();

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