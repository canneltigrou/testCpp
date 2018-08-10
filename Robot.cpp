#include "Robot.h"

#define NONE 0
#define SOME 1
#define ALL 2

Robot::Robot(std::string const& name)
	: AbstractLogObject(name),
	  batteryLevel_(MAX_VOLTAGE),
	  positionX_(0),
	  positionY_(0),
	  leftLeg_("LeftLeg"),
	  rightLeg_("RightLeg")
{
	// I suppose all these attributes are optional.
	registerValue("BatteryLevel", true);
	registerValue("PositionX", false);
	registerValue("PositionY", false);
	complexObects_.insert(&leftLeg_);
	complexObects_.insert(&rightLeg_);

}


void Robot::getCurrentValues(std::vector<int>& values)
{
	// call Parent class method to log our private int values.
	AbstractLogObject::getCurrentValues(values);

	// Then call the method for complex objects.
	getCurrentAttributesValues(values);
}


void Robot::computeBatteryLevel(int const timeMs)
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
	logValue("BatteryLevel", batteryLevel_);
}

void Robot::computePositionX(int const timeMs)
{
	positionX_ = timeMs;
	logValue("PositionX", positionX_);
}

void Robot::computePositionY(int const timeMs)
{
	positionY_ = -timeMs;
	logValue("PositionY", positionY_);
}


// Do some computations to have some data to log.
void Robot::compute(int const timeMs)
{
	if(!optional_["BatteryLevel"])
		computeBatteryLevel(timeMs);
	if(!optional_["PositionX"])
		computePositionX(timeMs);
	if(!optional_["PositionY"])
		computePositionY(timeMs);

	// Call compute for private members (not ideal, see question 2).
	computeAttributes(timeMs);
}

Robot::~Robot()
{
}

