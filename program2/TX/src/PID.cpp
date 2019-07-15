#include <iostream>
#include <cmath>
#include "../headers/PID.hpp"

using namespace std;

PID::PID(double dt, double max, double min, double Kp, double Kd, double Ki)
{
    _dt = dt;
    _max = max;
    _min = min;
    _Kp = Kp;
    _Kd = Kd;
    _Ki = Ki;
    previous_error = 0;
    integral = 0;
}

double PID::calculate(double setpoint, double measured_value)
{

    double error = setpoint - measured_value;

    //wyznaczenie wzmocnienia częsci proporcjonalnej
    double Pout = _Kp * error;

    //wyznaczenie wzmocnienia częsci całkującej 
    integral += error * _dt;
    double Iout = _Ki * integral;

    //wyznaczenie wzmocnienia cześci różniczkującej
    double derivative = (error - previous_error) / _dt;
    double Dout = _Kd * derivative;

    //obliczenie wyjściowego wzmocnienia
    double output = Pout + Iout + Dout;

    //sprawdzenie i dostosowanie wzmocnienia do granicznych wartości podanych przez użytkownika
    if( output > _max )
        output = _max;
    else if( output < _min )
        output = _min;

    //zapisanie aktualnego błędu w celu użycia go w obliczeniach podczas kolejnej iteracji
    previous_error = error;

return output;
}
