/*******************************************************************************
 * SpeedCounter.h - SpeedCounter class
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/


#ifndef SPEEDCOUNTER_H_
#define SPEEDCOUNTER_H_

#include "WPILib.h"

//
// SpeedCounter
//
// Wrapper class to add PIDSource functionality to the Counter class
//
class SpeedCounter : public Counter, public PIDSource
{
public:
	//
	// Constructor
	//
	// Calls the superclasses constructor
	//
	SpeedCounter(int channel) : Counter(channel) {}
	
	//
	// GetRPM()
	//
	// Calculates the speed measured by the sensor based on the time period
	// between ticks
	//
	// @return The speed measured by the sensor in RPMs
	//
	double GetRPM()
	{
		// Holds the value from the previous call to filter noise
		static double prevSpeed = 0;

		// Calculate the speed measured by the sensor in RPMs
		double speed = (60.0 / GetPeriod());
		
		// Max output is 5400 RPMs. If we exceed this, use the previous
		// value instead. Helps to filter out noise
		if (speed > 5400)
			speed = prevSpeed;
		
		// Store the current speed as the previous speed for the next time through
		prevSpeed = speed;
		
		// Return the calculated value
		return speed;
	}
	
	//
    // PIDGet()
    //
    // PIDGet is called by the PIDController object to get the current value
    // of the input.
    //
    // @return The speed measured by the counter in RPMs
    //
	double PIDGet()
	{
		return GetRPM();
	}
	
	//
	// UpdateTable()
	//
	// Updates the value of the sensor for LiveWindow/NetworkTables
	//
	void UpdateTable()
	{
		if (GetTable() != NULL)
			GetTable()->PutNumber("Value", GetRPM());
	}
};

#endif
