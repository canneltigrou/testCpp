#include "AbstractLogObject.h"
#include <iostream>
#include <algorithm>
#include <string.h>

#define NONE 0
#define SOME 1
#define ALL 2

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
		if(isToLog_[*it])
		{
			std::string tmp = prefix + name_ + "." + *it + "\t";
			header += tmp;
		}
	}

	// Then call the method for complex objects of the descendant class.
	std::string const prefix2 = prefix + name_+ '.';
	for (std::set<AbstractLogObject*>::const_iterator it = complexObjects_.begin(); it != complexObjects_.end(); it++)
		(*it)->formatHeader(header, prefix2);
}

void AbstractLogObject::registerValue(std::string const& name, bool isOptional)
{
	headers_.insert(name);
	optional_[name] = isOptional;
}

void AbstractLogObject::logValue(std::string const& field, int const value)
{
	values_[field] = value;
}

void AbstractLogObject::getCurrentValues(std::vector<int>& values)
{
	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		if(isToLog_[*it])
		{
			int val = values_[*it];
			values.push_back(val);
		}
	}
}

void AbstractLogObject::compute(int const timeMs)
{
	computeAttributes(timeMs);
}

void AbstractLogObject::computeAttributes(int const timeMs)
{
	for (std::set<AbstractLogObject*>::const_iterator it = complexObjects_.begin(); it != complexObjects_.end(); it++)
				(*it)->compute(timeMs);
}

void AbstractLogObject::getCurrentAttributesValues(std::vector<int>& values)
{
	for (std::set<AbstractLogObject*>::const_iterator it = complexObjects_.begin(); it != complexObjects_.end(); it++)
		(*it)->getCurrentValues(values);
}

void AbstractLogObject::initialiseIsToLog(int const option)
{
	if(option != SOME)
	{
		bool chooseAll = true;
		if(option == NONE)
			chooseAll = false;

		for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
		{
			isToLog_[*it] = (!optional_[*it]) | chooseAll;
			if(chooseAll)
				optional_[*it] = false; // an attribute printed can't be optional anymore.
		}
	}
	else // we will ask the user which attributes he want to log
	{
		std::string str;
		std::cout<<"\nWe actually are in " + name_+" : please tell 'y' if you want to log these variables or 'n' if not.";
		for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
		{
			bool isOK = false;
			while(!isOK)
			{
				std::cout<< "\n" + name_ + "." + *it + " : ";
				std::getline(std::cin, str);
				if(str == std::string("y") )
				{
					isOK = true;
					isToLog_[*it] = true;
					optional_[*it] = false; // an attribute printed can't be optional anymore.
				}
				else
					if(str == std::string("n"))
					{
						isOK = true;
						isToLog_[*it] = false;
					}
					else
						std::cout<<"Error : I couldn't understand. Retry. (y for yes, n for no)";
			}
		}
	}
	for (std::set<AbstractLogObject*>::const_iterator it = complexObjects_.begin(); it != complexObjects_.end(); it++)
			(*it)->initialiseIsToLog(option);
}


void AbstractLogObject::findingHeaders(std::string const& prefix, std::vector<std::string> &valuesLoad_ , std::vector<int> &tmpVect_)
{

	// log our private int values of the AbstractLogObject's attributes
	std::string result("");
	for (std::set<std::string>::const_iterator it = headers_.begin(); it != headers_.end(); it++)
	{
		std::string tmp = prefix + name_ + "." + *it;

		bool found = false;
		for (unsigned int i = 0; !found && i < valuesLoad_.size(); i++)
		{
			if (valuesLoad_[i] == tmp)
			{
				optional_[*it] = true;
				values_[*it] = tmpVect_[i];
			}
		}
	}

	// Then call the method for complex objects of the descendant class.
	std::string const prefix2 = prefix + name_+ '.';
	for (std::set<AbstractLogObject*>::const_iterator it = complexObjects_.begin(); it != complexObjects_.end(); it++)
		(*it)->findingHeaders(prefix2, valuesLoad_ , tmpVect_);



}



