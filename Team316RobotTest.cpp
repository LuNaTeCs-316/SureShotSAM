/*******************************************************************************
 * Team316RobotTest.cpp - Test mode functions
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#include "Team316Robot.h"

//
// TestInit()
//
// Called once upon entering test mode. All setup code for test mode
// should be placed here.
//
void Team316Robot::TestInit() {}    // Nothing to do at the moment

//
// TestPeriodic()
//
// Called aprox. every 20 ms in Test mode. Run the LiveWindow
//
void Team316Robot::TestPeriodic()
{
	liveWindow->Run();
}
