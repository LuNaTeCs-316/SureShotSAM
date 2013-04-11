/*******************************************************************************
 * Potentiometer.h - Potentiometer class
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#ifndef ENCODER_SUB_H_
#define ENCODER_SUB_H_

#include "WPILib.h"

// 
//
// Wrapper class for the ENCODER so we can use PIDController class
//
class Encoder_sub : public Encoder
{
public:
    //
    // Constructor
    //
    // Calls the parent class' constructor
    //
	Encoder_sub (UINT32 aChannel, UINT32 bChannel, bool reverseDirection=false, EncodingType encodingType = k1X) : Encoder (aChannel, bChannel, reverseDirection, encodingType){}
	
    //
    // PIDGet()
    //
    // PIDGet is called by the PIDController object to get the current value
    // of the input.
    //
	double PIDGet()
    {
		return Get();
//		return GetDistance();
	}
};

#endif
