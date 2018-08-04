#include <iostream>
#include "AbstractLogObject.h"
#include "Robot.h"

void printVector(std::vector<int> const& v)
{
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		std::cout << *it << "\t";
	}

	std::cout << std::endl;
}


int main(void)
{
	Robot r("JohnyFive");

	std::string header("Time\t");
	r.formatHeader(header);
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
