#include <iostream>
#include "AbstractLogObject.h"
#include "Robot.h"
#include <fstream>

#define NONE 0
#define SOME 1
#define ALL 2
#define ERROR -1

void printVector(std::vector<int> const& v, std::ofstream& fluxSortie_)
{
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		fluxSortie_ << *it << "\t";
	}

	fluxSortie_ << std::endl;
}

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
	std::cerr<<"Error ! Usage : simulator [-all | -some | -none | -help] [-save file_name]\n"
			"use {simulator -help} for more informations";
}


void printHelp()
{
	std::cout <<
			"Usage : simulator [-all | -some | -none | -help][-save file_name]\n"
			"no tag : it will do the same than with the tag -nothing \n"
			" -all : all the variables will be computed and printed \n"
			" -some : only some variables will be printed. The program will ask you which ones.\n"
			" -none : only the non optional variables will be computed and printed.\n"
			" -save file_name : it will save the results into a file named file_name";
}




///////////////////////////////////////////////////////////////////////////////////////
/// \brief   Manage the different parameters given on the args.
///
/// \details
///
/// \param[in] argc: number of parameters given.
///	\param[in] argv: the differents parameters given.
///	\param[out] optionLog : the option chosen about the prints
///	\param[out] optionSave : tell if we have to save into a file or not.
///	\param[out] file : the name of the file in which we have to save.
///////////////////////////////////////////////////////////////////////////////////////
void paramsManagement(int argc, char *argv[], int* optionLog, bool* optionSave , std::string* file )
{
	if (argc > 4)
	{
		printError();
		*optionLog = ERROR;
		return;
	}
	*optionLog = NONE;
	*optionSave = false;

	int indice = 1;
	while(indice < argc)
	{
		if(argv[indice] == std::string("-none"))
		      *optionLog = NONE;
		else
			if(argv[indice] == std::string("-some"))
				*optionLog = SOME;
			else
				if(argv[indice] == std::string("-all"))
					*optionLog = ALL;
				else
					if(argv[indice] == std::string("-help"))
					{
						*optionLog = ERROR;
						printHelp();
					}
					else
						if(argv[indice] == std::string("-save"))
						{
							*optionSave = true;
							if(indice == argc - 1)
							{
								*optionLog = ERROR;
								printError();
								return;
							}
							*file = std::string(argv[indice+1]);
							indice++;
						}
						else
						{
							*optionLog = ERROR;
							printError();
							return;
						}
		indice++;
	}
}



int main(int argc, char *argv[])
{
	int optionPrint_;
	bool optionSave_;
	std::string fileName_("");

	paramsManagement(argc, argv, &optionPrint_, &optionSave_, &fileName_);

	if(optionPrint_ == ERROR)
		return 0;

	std::ofstream myfile;
	if(optionSave_)
	{
		myfile.open(fileName_.c_str(), std::fstream::out | std::fstream::trunc);
		if(!myfile)
		{
			myfile.close();
			std::cerr<<"Error : The program couldn't open a file named " + fileName_<< std::endl;
			return -1;

		}
	}


	Robot r("JohnyFive");

	r.initialiseIsToLog(optionPrint_);

	std::string header("Time\t");
	r.formatHeader(header, "");
	std::cout << header << std::endl;

	if(optionSave_)
	{
		myfile<<header<<std::endl;
	}

	for (int timeStep = 0; timeStep < 1000; timeStep++)
	{
		r.compute(timeStep);
		std::vector<int> values;
		// First column is always the Time.
		values.push_back(timeStep);

		// Get the values to log from each class
		r.getCurrentValues(values);
		printVector(values);
		if(optionSave_)
			printVector(values, myfile);
	}
		if(optionSave_)
			myfile.close();

	return 0;
}
