//
// Potentiometer.h
//
// Wrapper class for the AnalogChannel for use with Potentiometers
//

#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

class Potentiometer : public AnalogChannel
{
public:
	Potentiometer(int channel)
		: AnalogChannel(channel) {}
	
	double PIDGet() {
		return GetAverageVoltage();
	}
};

#endif
