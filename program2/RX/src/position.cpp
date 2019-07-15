
#include "../headers/position.hpp"

void position(ControlRX &ctr)
{
    //otwarcie portu szerwgowego w celu odbierania informacji z enkodera
    int fenc = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
    if (fenc < 0)
    {
        error_message("error %d opening %s: %s", errno, "/dev/ttyACM0", strerror(errno));
        exit(1);
    }
    //ustawienie prędkości do 115,200 bps, wyłączenie sprawdzania 
    set_interface_attribs(fenc, B9600, 0);
    //wyłączenie blokowania portu
    set_blocking(fenc, 0);                 
    while(ctr.state)
    {
        int temp = getPosition(fenc);
        if(temp!=0)
            //zapisanie pozycji do obiektu przechowujące informacje o wynikach testu
            ctr.position=(double)temp*3.14*DIAMETER/SPIKES;
    }
}
bool check(int a, int b, bool parsed)
{   
    //sprawdzanie poprawnosci odebranych danych 
    if (a < 0)
        a *= (-1);
    if (parsed == true)
    {
        while (a != 0)
        {
            b -= a % 10;
            a /= 10;
            b -= 100;
        }
    }
    else
    {
        return false;
    }
    if (b == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getPosition(int fenc)
{
    char buf[1000];
    char *p;
    char *r;
    char *s;
    int b;
    position_t res;
    
    res.correctly_parsed = false;
    //oczekiwanie na nazbieranie danych do bufora
    usleep(96000);
    //odczytanie danych z bufora
    int n = read(fenc, buf, sizeof(buf));
    buf[n] = '\0';

    if (n > 50)
    {
        p = buf;
        //pobieranie informacji o pozycji i sumy kontrolnej
        r = strchr(p, 'C'); 
        s = strchr(p, 'P');
        if (r != NULL)
        {
            p = r + 1;
            r = strchr(p, '=');
            p = r + 1;
            r = strchr(p, ' ');
            if (r != NULL)
            {
                *r = '\0';
                b = atof(p);
                res.correctly_parsed = true;
            }
        }
        if (r != NULL && res.correctly_parsed == true)
        {
            p = s + 1;
            s = strchr(p, '=');
            p = s + 1;
            s = strchr(p, ' ');
            if (s != NULL)
            {
                *s = '\0';
                res.position = atof(p);
                res.correctly_parsed = true;
            }
            else
            {
                res.correctly_parsed = false;
            }
        }
    }
    if (check(res.position, b, res.correctly_parsed))
    {
        return res.position;
    }
    else
    {   
        res.correctly_parsed = false;
        return res.position;
    }
}

