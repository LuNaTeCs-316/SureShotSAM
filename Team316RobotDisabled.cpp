/*******************************************************************************
 * Team316RobotDisable.cpp - Disabled mode functions
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 ******************************************************************************/

#include "Team316Robot.h"

//
// DisabledInit()
//
// Setup for disabled mode
//
void Team316Robot::DisabledInit() {}

//
// DisabledPeriodic()
//
// Runs ever 20 ms while disabled
//
void Team316Robot::DisabledPeriodic()
{
    // 
    // Stop all outputs
    //
	driveMotors->ArcadeDrive(0.0, 0.0);
	
    pickupBeltRelay->Set(Relay::kOff);
    pickupAngleMotor->Set(0.0);

    shooterMotor->Set(0.0);
    shooterSpeedController->Disable();
    shooterAngleMotor->Set(0.0);
    shooterAngleController->Disable();
    shooterPistonSolenoid->Set(false);

    climbingSolenoid->Set(false);

    // Send data to the dashboard
    //UpdateSmartDashboard();
}
