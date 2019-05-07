#ifndef PID_H
#define PID_H

class PID
{
	private:
	double _Kp;
	double _Kd;
	double _Ki;
	double _min;
	double _max;
	double _dt;
	
	double previous_error;
	double integral;
	public:
	PID(double dt, double max, double min, double Kp, double Kd, double Ki);
	double calculate(double setpoint, double measured_value);
};

#endif
