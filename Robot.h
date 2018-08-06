#ifndef ROBOT_H_
#define ROBOT_H_

#include "AbstractLogObject.h"
#include "Leg.h"

class Robot : public AbstractLogObject
{
public:
	Robot(std::string const& name);

	// Reimplement virtual methods.
	virtual void compute(int const timeMs);
	virtual void getCurrentValues(std::vector<int>& values);
	virtual void formatHeader(std::string& header, std::string const& prefix);

	virtual ~Robot();
private:
	static int const MAX_VOLTAGE = 12000;

	// Some internal variables to so that we have something to log.
	int batteryLevel_;
	int positionX_;
	int positionY_;

	// Complex objects that are also derived from AbstractLogObject.
	Leg leftLeg_;
	Leg rightLeg_;
};

#endif /* ROBOT_H_ */
