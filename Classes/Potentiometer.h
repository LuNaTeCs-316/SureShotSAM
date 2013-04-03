/*******************************************************************************
 * Potentiometer.h - Potentiometer class
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include "WPILib.h"

// 
// Potentiometer
//
// Wrapper class for the AnalogChannel so we can use Potentiometers with
// the WPILib PIDController class
//
class Potentiometer : public AnalogChannel
{
public:
    //
    // Constructor
    //
    // Calls the parent class' constructor
    //
	Potentiometer(int channel) : AnalogChannel(channel) {}
	
    //
    // PIDGet()
    //
    // PIDGet is called by the PIDController object to get the current value
    // of the input.
    //
    // @return The angle of the potentiometer as determined by it's voltage output
    //
	double PIDGet()
    {
		return GetAverageVoltage();
	}
};

#endif
