#include "AbstractLogObject.h"
#include <iostream>

AbstractLogObject::~AbstractLogObject()
{
}

AbstractLogObject::AbstractLogObject(std::string const& name)
	: name_(name)
{
}

void AbstractLogObject::formatHeader(std::string &header)
{
	std::string result("");

	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		std::string tmp = name_ + "." + *it + "\t";
		header += tmp;
	}
}

void AbstractLogObject::registerValue(std::string const& name)
{
	headers_.insert(name);
}

void AbstractLogObject::logValue(std::string const& field, int const value)
{
	values_[field] = value;
}

void AbstractLogObject::getCurrentValues(std::vector<int>& values)
{
	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		int val = values_[*it];
		values.push_back(val);
	}
}
