#include "../headers/Measure.hpp"

Measure::Measure()
{
    //pobranie nazwy interface sieci WiFi używanego podczas testu
    string data;
    FILE *stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    string cmd = "iw dev";
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer);
        pclose(stream);
    }
    string temp;
    if (data.find("Interface") != std::string::npos)
    {
        temp = data.substr(data.find("Interface") + 10);
        interface_name = temp.substr(0, temp.find("\n"));
    }
}

string Measure::getResult()
{
    //pobieranie informacji z programu i zwracanie ich w formacie stringa
    string result;
    result += to_string(position) + ";";
    result += to_string(signal_level) + ";";
    result += to_string(signal_quality) + ";";
    result += to_string(received) + ";";
    result += to_string(bitrate) + ";";
    result += to_string(lost) + ";";
    if (not_in_order)
        result += "true;";
    else
        result += "false;";
    if (err)
        result += "true;";
    else
        result += "false;";
    result += to_string(error) + ";";
    result += channel + ";";
    result += to_string(bt) + ";";
    result += to_string(bandwidth) + ";";
    result += to_string(MCS) + ";";
    result += to_string(NSS) + ";";
    if (short_preable)
        result += "true";
    else
        result += "false";
    return result;
}

void Measure::collectData(ControlRX &ctr, CheckPackets &chk)
{
    //zbieranie informacji dotyczacych kanału radiowego
    getsignalinfo();

    //oblicznie odebranych pakietów
    if (previously_received <= ctr.counter)
    {
        received = ctr.counter - previously_received;
    }
    else
    {
        received = UINT_MAX - previously_received;
    }
    previously_received = ctr.counter;
    //aktualizacja pozycji
    position = ctr.start_position + ctr.position;
    //obliczanie osiągniętej przepływnosci
    bitrate = (double)received / (125000 / ctr.packet_size);
    //pobieranie flag dotyczacych odebranych pakietów, kolejnosci s poprawnosci testu
    lost = chk.lost;
    err = chk.err;
    not_in_order = chk.not_in_order;
    //pobranie informacji o błędach
    error = chk.getResults();
}

void Measure::getsignalinfo()
{
    //pobranie informacji 
    channel = "NO INFO";
    bt = 0;
    bandwidth = 20;
    MCS = 0;
    NSS = 0;
    short_preable = false;
    int link, level;
    string line;
    string quality;
    fstream file;

    //pobranie informacji o poziomie sygnalu i jakości linku z plików systemowych
    file.open("/proc/net/wireless", ios::in);
    getline(file, line);
    getline(file, line);
    if (getline(file, line))
    {
        quality = line.substr(15, 15);
        link = stoi(quality.substr(0, 2));
        level = stoi(quality.substr(5, 7));
    }
    else
        level = -256;
    file.close();
    signal_level = level;
    signal_quality = link;

    //pobieranie informacji o połączeniu radiowym z komendy iw dev <interface> info
    FILE *stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    string cmd;
    string data;
    string temp;
    cmd = "iw dev " + interface_name + " info";
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer);
        pclose(stream);
    }
    //parsowanie danych i zapisanie ich do zmiennych klasy Measure
    if (data.find("channel") != std::string::npos)
    {
        temp = data.substr(data.find("channel") + 8);
        channel = temp.substr(0, temp.find(","));
    }

    data = "";

    //pobieranie informacji o połączeniu radiowym z komendy iw dev <interface> station dump
    cmd = "iw dev " + interface_name + " station dump";
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer);
        pclose(stream);
    }
    //parsowanie danych i zapisanie ich do zmiennych klasy Measure
    if (data.find("rx bitrate") != std::string::npos)
    {
        line = data.substr(data.find("rx bitrate"));
        line = line.substr(0, line.find("\n"));
        temp = line.substr(12, line.find("MBit/s"));
        bt = stof(temp);
        if (line.find("MHz") != std::string::npos)
        {
            temp = line.substr(0, line.find("MHz"));
            bandwidth = stoi(temp.substr(temp.find_last_of(" ") + 1));
        }
        if (line.find("VHT-MCS") != std::string::npos)
        {
            temp = line[line.find("VHT-MCS") + 8];
            MCS = stoi(temp);
        }
        if (line.find("VHT-NSS") != std::string::npos)
        {
            temp = line[line.find("VHT-NSS") + 8];
            NSS = stoi(temp);
        }
        if (line.find("short GI") != std::string::npos)
            short_preable = true;
    }
}