#include "Leg.h"

// Set the internal objects name also.
Leg::Leg(std::string const& name)
	: AbstractLogObject(name),
	  foot_("Foot"),
	  knee_("Knee")
{
	complexObjects_.insert(&foot_);
	complexObjects_.insert(&knee_);
}


void Leg::getCurrentValues(std::vector<int>& values)
{
	getCurrentAttributesValues(values);
}

Leg::~Leg()
{
}

