//
// SpeedCounter.h
//
// Wrapper class to add PIDSource functionality to the Counter class
//

#ifndef SPEEDCOUNTER_H_
#define SPEEDCOUNTER_H_

#include "WPILib.h"

class SpeedCounter : public Counter, public PIDSource
{
public:
	SpeedCounter(int channel) : Counter(channel) {}
	
	double GetRPM() {
		static double prevSpeed = 0;
		double speed = (60.0 / GetPeriod());
		if (speed > 5400)
			speed = prevSpeed;
		prevSpeed = speed;
		return speed;
	}
	
	double PIDGet() {
		// Return the RPM speed of the counter
		return GetRPM();
	}
	
	void UpdateTable() {
		if (GetTable() != NULL)
			GetTable()->PutNumber("Value", GetRPM());
	}
};

#endif
