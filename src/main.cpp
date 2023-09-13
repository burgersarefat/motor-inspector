#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "started");
	pros::lcd::register_btn1_cb(on_center_button);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Motor motor(1);
	pros::lcd::initialize();

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
		pros::lcd::set_text(2, "AV (RPM): " + actual_velocity_string);
		pros::delay(20);
		pros::lcd::set_text(3, "Temp (C): " + temperaturestring);
		pros::delay(20);
		pros::lcd::set_text(4, "Torque (nM): " + torque_string);
		pros::delay(20);
		pros::lcd::set_text(5, "Overheating?: " + over_temp_string);
    	pros::delay(20);
	}
}
