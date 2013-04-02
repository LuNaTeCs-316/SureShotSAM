//***************************************
// LuNaTeCs - team 316
// code for the 2013 robot
// for the FRC game - ultimate assent
//
// Team316RobotTest.cpp
//
// Test mode functions
//***************************************


#include "Team316Robot.h"

//
// TestInit()
//
// Setup for test mode
//
void Team316Robot::TestInit()
{
	// Nothing to do
}

//
// TestPeriodic()
//
// Called aprox. every 20 ms in Test mode. Run the LiveWindow
//
void Team316Robot::TestPeriodic()
{
	liveWindow->Run();
}
