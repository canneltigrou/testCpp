#include <iostream>
#include "AbstractLogObject.h"
#include "Robot.h"
#include<string.h>

#define NONE 0
#define SOME 1
#define ALL 2
#define ERROR -1

void printVector(std::vector<int> const& v)
{
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << "\t";
	}

	std::cout << std::endl;
}


void printError()
{
	std::cerr<<"Error ! Usage : simulator [-all | -some | -nothing | -help]\n"
			"use {simulator -help} for more informations";
}


void printHelp()
{
	std::cout <<
			"Usage : simulator [-all | -some | -nothing | -help]\n"
			"no tag : it will do the same than with the tag -nothing \n"
			" -all : all the variables will be computed and printed \n"
			" -some : only some variables will be printed. The program will ask you which ones.\n"
			" -none : only the non optional variables will be computed and printed." ;
}



///////////////////////////////////////////////////////////////////////////////////////
/// \brief   Manage the different parameters given on the args.
///
/// \details
///
/// \param[in] argc: number of parameters given.
///	\param[in] argv: the differents parameters given.
///////////////////////////////////////////////////////////////////////////////////////
int paramsManagement(int argc, char *argv[])
{
	if (argc > 2)
	{
		printError();
		return ERROR;
	}

	if (argc == 1 || argv[1] == std::string("-none"))
		return NONE;
	if (argv[1] == std::string("-some"))
		return SOME;
	if (argv[1] == std::string("-all"))
		return ALL;
	if (argv[1] == std::string("-help"))
	{
		printHelp();
		return ERROR;
	}
	printError();
	return ERROR;

}




int main(int argc, char *argv[])
{
	int option;
	option = paramsManagement(argc, argv);

	if(option == ERROR)
		return 0;

	Robot r("JohnyFive");

	r.initialiseIsToLog(option);

	std::string header("Time\t");
	r.formatHeader(header, "");
	std::cout << header << std::endl;

	for (int timeStep = 0; timeStep < 1000; timeStep++)
	{
		r.compute(timeStep);
		std::vector<int> values;
		// First column is always the Time.
		values.push_back(timeStep);

		// Get the values to log from each class
		r.getCurrentValues(values);
		printVector(values);
	}

	return 0;
}
