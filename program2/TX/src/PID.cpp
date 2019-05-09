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
};

double PID::calculate(double setpoint, double measured_value)
{
    double error = setpoint - measured_value;
    integral += error * _dt;
    double derivative = (error - previous_error) / _dt;
    double output = _Kp * error + _Ki * integral + _Kd * derivative;
    previous_error = error;

    if (output > _max)
        output = _max;
    else if (output < _min)
        output = _min;
    return output;
}
