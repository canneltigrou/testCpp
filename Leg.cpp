#include "Leg.h"

// Set the internal objects name also.
Leg::Leg(std::string const& name)
	: AbstractLogObject(name),
	  foot_("Foot"),
	  knee_("Knee")
{
	complexObects_.insert(&foot_);
	complexObects_.insert(&knee_);
}


void Leg::getCurrentValues(std::vector<int>& values)
{
	getCurrentAttributesValues(values);
}

Leg::~Leg()
{
}

