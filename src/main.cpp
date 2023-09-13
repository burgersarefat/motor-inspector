#include "main.h"

/**
 * init
 */
void initialize() {
	pros::lcd::initialize();
}

/**
 * telemetry
 */
void opcontrol() {
	pros::Motor motor(1); // motor on port 1

	while (true) {
		// Converting numeric values to strings
		double actual_velocity = motor.get_actual_velocity();
		std::string actual_velocity_string = std::to_string(actual_velocity);

		double temperature = motor.get_temperature();
		std::string temperaturestring = std::to_string(temperature);

		double torque = motor.get_torque();
		std::string torque_string = std::to_string(torque);

		bool is_over_temp = motor.is_over_temp();
    	std::string over_temp_string = is_over_temp ? "Yes" : "No";


		// Motor velocity (percent)
		motor.move(100);
		pros::delay(1000);

		// Print values to LCD screen
		pros::lcd::set_text(1, "AV (RPM): " + actual_velocity_string);
		pros::delay(20);
		pros::lcd::set_text(2, "Temp (C): " + temperaturestring);
		pros::delay(20);
		pros::lcd::set_text(3, "Torque (nM): " + torque_string);
		pros::delay(20);
		pros::lcd::set_text(4, "Overheating?: " + over_temp_string);
    	pros::delay(20);
	}
}
