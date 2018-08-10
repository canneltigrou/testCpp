#include "Motor.h"

Motor::Motor(std::string const& name)
	: AbstractLogObject(name),
	  position_(0),
	  speed_(0),
	  torque_(0)
{
	// Register the values we want to log.
	// Allows to call later logValue("Position", position_); for example.
	registerValue("Position", false);
	registerValue("Speed", false);
	registerValue("Torque", true);
}

Motor::~Motor()
{
}




// do the computation on the variable position_ and update the value of the map values_
// I suppose that the computation can be more long and difficult than just to be equal to timeMS
void Motor::computePosition(int const timeMs)
{
	position_ = timeMs;
	logValue("Position", position_);
}

// do the computation on the variable speed_ and update the value of the map values_
// I suppose that the computation can be more long and difficult than just to be equal to timeMS
void Motor::computeSpeed(int const timeMs)
{
	speed_ = timeMs;
	logValue("Speed", speed_);
}

// do the computation on the variable speed_ and update the value of the map values_
// I suppose that the computation can be more long and difficult than just to be equal to timeMS
void Motor::computeTorque(int const timeMs)
{
	torque_ = timeMs;
	logValue("Torque", torque_);
}

// Example of the simulation step, it should change
// the values of internal variables, doing some computation on them.
void Motor::compute(int const timeMs)
{
	// I compute only the non optional attributes
	if(!optional_["Position"])
		computePosition(timeMs);
	if(!optional_["Speed"])
		computeSpeed(timeMs);
	if(!optional_["Torque"])
		computeTorque(timeMs);
}
