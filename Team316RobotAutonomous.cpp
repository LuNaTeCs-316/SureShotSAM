/*******************************************************************************
 * Team316RobotAutonomous.cpp - Autonomous mode functions
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 * Each Autonomous mode is in its own file in the Autonomous directory
 *
 ******************************************************************************/

#include "Team316Robot.h"

//
// AutonomousInit()
//
// Called once at the start of Autonomous Mode to setup
//
void Team316Robot::AutonomousInit()
{
	// Set autoMode to the value of analog slider 1 on the DS
	autoMode = (int) ds->GetAnalogIn(1);
	cout << "[AutonomousInit] autoMode = " << autoMode << endl;

	// these must be here and NOT be static so that we can restart autonomous without rebooting the robot
	step = 1;
	startTime = GetClock();
	beginTime = GetClock();
}

//
// AutonomousPeriodic()
//
// Called aprox. every 20ms, reads the value of `autoMode`, then jumps to the
// appropriate sub-routine
//
void Team316Robot::AutonomousPeriodic()
{
	switch (autoMode)
	{
		case 1: 
			AutonomousMode1(); // Fire 3 shots then stop
			break;
		case 2:
			AutonomousMode2();	// Shoot 3, pickup & fire frisbees from center line - Dead reckoning
			break;
		case 3:
			AutonomousMode3();	// Shoot 3, pickup & fire frisbees from center line - Encoders
			break;
		case 4:
			AutonomousMode4();	// TEST - timing of raising and lowering shooter
			break;
		case 5:
			AutonomousMode5();	// TEST - experimentation with encoders
			break;
		case 6:
			AutonomousMode6();	// TEST - experimentation with encoders and PIDs
			break;
		default:
			// Do nothing
			break;
	}

	// Send data to SmartDashboard for debugging
	//UpdateSmartDashboard();
}
