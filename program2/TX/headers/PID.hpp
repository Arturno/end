/**
 * @file PID.hpp
 * @brief Plik przechowujący klasę realizującą regulację PID
 * 
 */
#ifndef PID_H
#define PID_H
/**
 * @brief Klasa PID realizująca regulację PID
 * @details Obiekt tej klasy reguluje opóźnienie pomiędzy wysłanymi grupami pakietów dzięki czemu pośrednio wpływa na przepływność nadawanych danych
 * 			Służy do utrzymania stałej przepływności i uniezależnieniu przepływności od innych czynników.
 */
class PID
{
	private:
	double _Kp;				/**< Współczynnik proporcjonalny*/
	double _Kd;				/**< Współczynnik różniczkujący*/
	double _Ki;				/**< Współczynnik całkujący*/
	double _min;			/**< Maksymalna wartość, o którą regulator może zmniejszyć zmienną wyjściową*/
	double _max;			/**< Maksymalna wartość, o którą regulator może zwiększyć zmienną wyjściową*/
	double _dt;				/**< Czas pomiędzy kolejnymi uruchomieniami regulacji*/
	
	double previous_error;	/**< Zmiana zastosowana przez regulator w poprzedniej iteracji */
	double integral;		/**< Zmienna przechowująca całkę z dotychczas uzyskanych przepływności*/
	public:
	/**
	 * @brief Konstruktor obiektu klasy PID
	 * 
	 * @param dt Współczynnik proporcjonalny
	 * @param max Maksymalna wartość, o którą regulator może zmniejszyć zmienną wyjściową
	 * @param min Maksymalna wartość, o którą regulator może zwiększyć zmienną wyjściową
	 * @param Kp Współczynnik proporcjonalny
	 * @param Kd Współczynnik różniczkujący
	 * @param Ki Współczynnik całkujący
	 */
	PID(double dt, double max, double min, double Kp, double Kd, double Ki);
	/**
	 * @brief 
	 * 
	 * @param setpoint Zadana przez użytkownika przepływność
	 * @param measured_value Przepływność uzyskana od ostatniej iteracji algorytmu
	 * @return double Wartość o jaką powinna zostać skorygowane opóźnienie aby uzyskać zadaną przepływność
	 */
	double calculate(double setpoint, double measured_value);
};

#endif
