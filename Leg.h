#ifndef LEG_H_
#define LEG_H_

#include "AbstractLogObject.h"
#include "Motor.h"


class Leg : public AbstractLogObject
{
public:
	Leg(std::string const& name);
	virtual ~Leg();

	// Reimplement the virtual methods.
	virtual void formatHeader(std::string& header);
	virtual void getCurrentValues(std::vector<int>& values);
	virtual void compute(int const timeMs);

private:
	// A leg is only an aggregation of motors.
	Motor foot_;
	Motor knee_;
};

#endif /* LEG_H_ */
