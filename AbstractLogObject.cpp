#include "AbstractLogObject.h"
#include <iostream>
#include <typeinfo>

AbstractLogObject::~AbstractLogObject()
{
}

AbstractLogObject::AbstractLogObject(std::string const& name)
	: name_(name)
{
}


void const AbstractLogObject::formatHeader(std::string &header, std::string const& prefix)
{
	// log our private int values of the AbstractLogObject's attributes
	std::string result("");

	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		std::string tmp = prefix + name_ + "." + *it + "\t";
		header += tmp;
	}

	// Then call the method for complex objects of the descendant class.
	std::string const prefix2 = prefix + name_+ '.';
	for (std::set<AbstractLogObject*>::const_iterator it = complexObects_.begin(); it != complexObects_.end(); it++)
		(*it)->formatHeader(header, prefix2);

}

void AbstractLogObject::registerValue(std::string const& name)
{
	headers_.insert(name);
}

template <typename T>
std::map<std::string, T> AbstractLogObject::AttributeLied(T const value)
{
	if (typeid(value) == typeid(int))
		return valuesInt_;
	if (typeid(value) == typeid(float))
		return valuesFloat_ ;
	if (typeid(value) == typeid(std::string))
		return valuesString_;
	if (typeid(value) == typeid(bool))
		return valuesBool_;
	return valuesDouble_;
}


template <typename T>
void AbstractLogObject::logValue(std::string const& field, T const value)
{
	AttributeLied(value)[field] = value;
	//values_[field] = value;
}

void AbstractLogObject::getCurrentValues(std::vector<int>& values)
{
	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		int val = valuesInt_[*it];
		values.push_back(val);
	}
}

void AbstractLogObject::compute(int const timeMs)
{
	computeAttributes(timeMs);
}

void AbstractLogObject::computeAttributes(int const timeMs)
{
	for (std::set<AbstractLogObject*>::const_iterator it = complexObects_.begin(); it != complexObects_.end(); it++)
				(*it)->compute(timeMs);
}

void AbstractLogObject::getCurrentAttributesValues(std::vector<int>& values)
{
	for (std::set<AbstractLogObject*>::const_iterator it = complexObects_.begin(); it != complexObects_.end(); it++)
		(*it)->getCurrentValues(values);
}
