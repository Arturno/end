#ifndef PID_H
#define PID_H
/**
 * @brief 
 * 
 */
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
	/**
	 * @brief Construct a new PID object
	 * 
	 * @param dt 
	 * @param max 
	 * @param min 
	 * @param Kp 
	 * @param Kd 
	 * @param Ki 
	 */
	PID(double dt, double max, double min, double Kp, double Kd, double Ki);
	/**
	 * @brief 
	 * 
	 * @param setpoint 
	 * @param measured_value 
	 * @return double 
	 */
	double calculate(double setpoint, double measured_value);
};

#endif
