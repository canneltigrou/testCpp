#include "Leg.h"

// Set the internal objects name also.
Leg::Leg(std::string const& name)
	: AbstractLogObject(name),
	  foot_("Foot"),
	  knee_("Knee")
{
}

void Leg::compute(int const timeMs)
{
	foot_.compute(timeMs);
	knee_.compute(timeMs);
}


void Leg::formatHeader(std::string& header, std::string const& prefix)
{
	std::string prefix2 = prefix + name_ + ".";
	foot_.formatHeader(header, prefix2);
	knee_.formatHeader(header, prefix2);
}

void Leg::getCurrentValues(std::vector<int>& values)
{
	foot_.getCurrentValues(values);
	knee_.getCurrentValues(values);
}

Leg::~Leg()
{
}

