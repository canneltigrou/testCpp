#include "Robot.h"

Robot::Robot(std::string const& name)
	: AbstractLogObject(name),
	  batteryLevel_(MAX_VOLTAGE),
	  positionX_(0),
	  positionY_(0),
	  leftLeg_("LeftLeg"),
	  rightLeg_("RightLeg")
{
	registerValue("BatteryLevel");
	registerValue("PositionX");
	registerValue("PositionY");
}

void Robot::formatHeader(std::string& header)
{
	AbstractLogObject::formatHeader(header);
	leftLeg_.formatHeader(header);
	rightLeg_.formatHeader(header);
}

void Robot::getCurrentValues(std::vector<int>& values)
{
	// call Parent class method to log our private int values.
	AbstractLogObject::getCurrentValues(values);

	// Then call the method for complex objects.
	leftLeg_.getCurrentValues(values);
	rightLeg_.getCurrentValues(values);
}

// Do some computations to have some data to log.
void Robot::compute(int const timeMs)
{
	// Simulate a discharge, unit is mV.
	static int const DISCHARGE = 10; // Ratio in mv/s;

	if (batteryLevel_ > 0)
	{
		batteryLevel_ -= (timeMs * DISCHARGE/1000);
	}
	else
	{
		batteryLevel_ = 0;
	}

	// Set non null data.
	positionX_ = timeMs;
	positionY_ = -timeMs;

	// Call compute for private members (not ideal, see question 2).
	leftLeg_.compute(timeMs);
	rightLeg_.compute(timeMs);

	// Once values are updated, update the log.
	logValue("BatteryLevel", batteryLevel_);
	logValue("PositionX", positionX_);
	logValue("PositionY", positionY_);
}

Robot::~Robot()
{
}

