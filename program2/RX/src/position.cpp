
#include "../headers/position.hpp"

void position(ControlRX &ctr)
{

    int fenc = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
    if (fenc < 0)
    {
        error_message("error %d opening %s: %s", errno, "/dev/ttyACM0", strerror(errno));
        exit(1);
    }

    set_interface_attribs(fenc, B9600, 0); // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking(fenc, 0);                 // set no blocking
    while(ctr.state)
    {
    int temp = getPosition(fenc);
    if(temp!=0)
    ctr.position=temp;
    //std::cout<<position<<std::endl;
    }
}
bool check(int a, int b, bool parsed)
{
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
        //printf("NOK1\n");
        return false;
    }
    if (b == 0)
    {
        return true;
    }
    else
    {
        //printf("NOK2, ");
        //printf("%i\n", b);
        return false;
    }
}
int getPosition(int fenc)
{
    char buf[1000]; // buffer size not critical unless we make sure that each read operation reads all data from the input buffer
    char *p;
    char *r;
    char *s;
    int b;
    position_t res;

    res.correctly_parsed = false;
    usleep(96000);
    int n = read(fenc, buf, sizeof(buf));
    //printf("%i,\n",n);
    buf[n] = '\0';
    //printf("%s",buf);
    //printf("%s", buf);
    /* JUST FOR DEBUG
    for (int i=0; i<n; i++)
    {
        if (buf[i]=='\r')
            buf[i]=' ';
    }
*/
    // parsing!
    //n = 51;
    //printf("%s\n",buf);
    if (n > 50) // give the chance to read something - if read less, it means that encoder board does not send data as expected
    {
        //system("clear");
        //char buf2[1000] = "P=1234124                      ,C=121            ";
        p = buf;
        r = strchr(p, 'C'); // begin of the "position" word
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
                //res.position /= 1000;   // encoder gives position in milimeters, we want position in meters
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
                //res.position /= 1000;   // encoder gives position in milimeters, we want position in meters
                res.correctly_parsed = true;
                //printf("%i\n", res.position);
            }
            else
            {
                res.correctly_parsed = false;
            }
        }
    }
    //printf("ENC=%d POS=%d\n%s\n", n, res.position, buf);
    if (check(res.position, b, res.correctly_parsed))
    {
        //printf("%i\t,%i\n", res.position, b);
        return res.position;
    }
    else
    {   //printf("%i\t,%i\n", res.position, b);
        res.correctly_parsed = false;
    }
}

