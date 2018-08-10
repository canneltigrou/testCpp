#ifndef MOTOR_H_
#define MOTOR_H_

#include "AbstractLogObject.h"

class Motor : public AbstractLogObject
{
public:
	Motor(std::string const& name);
	virtual ~Motor();

	// Redefine the pure virtual method.
	virtual void compute(int const timeMs);
private:

	// example of private attributes we want to log.
	int position_;
	int speed_;
	int torque_;

	// the computation of this private attributes
	void computeTorque(int const timeMS);
	void computeSpeed(int const timeMS);
	void computePosition(int const timeMS);

};

#endif /* MOTOR_H_ */
