#include <iostream>
#include "AbstractLogObject.h"
#include "Robot.h"
#include <fstream>
#include <list>
#include <string>

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
	std::cerr<<"Error ! Usage : simulator [-all | -some | -none | -help] [-save file_name][-load file_name2]\n"
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
			" -save file_name : it will save the results into a file named file_name.\n"
			" -load file_name2 : it will load the values of the filename. \n"
			" CAUTION : please enter 2 different file-names if you use save and load at the same time.";
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
void paramsManagement(int argc, char *argv[], int* optionLog, bool* optionSave , bool* optionLoad, std::string* file , std::string* fileLoad)
{
	if (argc > 6)
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
							if(argv[indice] == std::string("-load"))
							{
								*optionLoad = true;
								if(indice == argc - 1)
								{
									*optionLog = ERROR;
									printError();
									return;
								}
								*fileLoad = std::string(argv[indice+1]);
								indice++;
							}
						{
							*optionLog = ERROR;
							printError();
							return;
						}
		indice++;
	}
}




/*
const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff("");
	std::vector<std::string> v;

	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);

	return v;
}*/



int main(int argc, char *argv[])
{
	int optionPrint_;
	bool optionSave_;
	bool optionLoad_;
	std::string fileName_("");
	std::string fileNameLoad_("");

	paramsManagement(argc, argv, &optionPrint_, &optionSave_, &optionLoad_ , &fileName_, &fileNameLoad_);

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

	if(!optionLoad_)
	{
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
	}
	else
	{
		std::cout << "not finish yet";
		return(-1);
		/*

		// I will use the same time step than the one logged in the file.
		 std::ifstream fileLoad(fileNameLoad_.c_str(), std::ios::in);  // on ouvre le fichier en lecture

		 if(fileLoad)  // if it succeeded

			 // the first line contains the name of the differents values to load.
			 // We will use them to make them optional to the computation
			 std::string buffer;  // déclaration d'une chaîne qui contiendra la ligne lue
			 std::getline(fileLoad, buffer);  // on met dans "contenu" la ligne
			 std::vector vectHeaders_ = explode(buffer, '\t');
			 // the first argument is the time. I don't need it so I delete it.
			 vectHeaders_.pop_front();

			 // an easy idea to find the different variables of the file, we will do the same fonction than formatHeader
			 // and compare it with the name of the file. (Observation: they are in the same order)

			 // créons tout d'abord une hashmap comportant un string pour le titre de la colonne, et les valeurs qu'on remettra à jour à chaque temps
			 std::map<std::string, int> valuesLoad_;

			 // so now, we can use each line of the file.
			 std::vector tmpVect_;
			 int timeStep;
			 while(getline(fileLoad, buffer))  // tant que l'on peut mettre la ligne dans "contenu"
			 {
				 // we know we have the same number of arguments in the same order.
				 tmpVect_ = explode(buffer, '\t');

				 // the first element is the time again.
				 timeStep = stoi("3");

				 stringstream ss(tmpVect_.pop_fornt());
				 int my_res; ss >> my_res;

				 r.findingHeaders(header, "", &valuesLoad_ , &tmpVect_);


				 // then it is the same than without the optionLoad
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



			 r.findingHeaders(header, "", );



		     fichier.close();  // on ferme le fichier
		 }
		 else
		 {
		     std::cerr << "Error I couldn't open the file to load !" << std::endl;
		     return (-1);
		 }
		 */
	}



		if(optionSave_)
			myfile.close();

	return 0;
}
