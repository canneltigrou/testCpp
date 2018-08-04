#include "Motor.h"

Motor::Motor(std::string const& name)
	: AbstractLogObject(name),
	  position_(0),
	  speed_(0),
	  torque_(0)
{

	// Register the values we want to log.
	// Allows to call later logValue("Position", position_); for example.
	registerValue("Position");
	registerValue("Speed");
	registerValue("Torque");
}

Motor::~Motor()
{
}


// Example of the simulation step, it should change
// the values of internal variables, doing some computation on them.
void Motor::compute(int const timeMs)
{
	// Update members with non null data to make sure we see some changes in the log.
	position_ = timeMs;
	speed_ = timeMs;
	torque_ = timeMs;

	// At each step, update the current "image" of the values.
	// It's like taking a photograph at time T of the values,
	// If we don't call this at each simulation step, the logged values won't be udpated.
	logValue("Position", position_);
	logValue("Speed", speed_);
	logValue("Torque", torque_);
}
