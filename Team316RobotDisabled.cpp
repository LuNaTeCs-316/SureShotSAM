//
// Team316RobotDisabled.cpp
//
// Disabled mode functions
//

#include "Team316Robot.h"

//
// DisabledInit()
//
// Setup for disabled mode
//
void Team316Robot::DisabledInit()
{
	// Nothing to do
}

//
// DisabledPeriodic()
//
// Runs ever 20 ms while disabled
//
void Team316Robot::DisabledPeriodic()
{
	// Send data to the dashboard
	UpdateSmartDashboard();
}
