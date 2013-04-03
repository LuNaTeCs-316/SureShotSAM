/*******************************************************************************
 * Team316Robot.h - Header file for the Robot program
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All Rights Reserved.
 * No robots were harmed in the writing of this code.
 * 
 * Copy under pain of torture and/or death.
 *
 * Code for our 2013 robot, Sure Shot SAM.
 * for the FRC game Ultimate Ascent
 *
 * The implementation for each robot mode is split into seperate files:
 * - Team316Robot.cpp:					Robot-wide and initializtion code
 * - Team316RobotAutonomous.cpp:		Autonomous mode
 * - Team316RobotTeleop.cpp:			Teleop mode
 * - Team316RobotTest.cpp:				Test mode
 * - Team316RobotDisabled.cpp:			Disabled mode
 * - Team316RobotVision.cpp:			Vision code
 *
 ******************************************************************************/

#ifndef TEAM316_ROBOT_H_
#define TEAM316_ROBOT_H_

#include "WPILib.h"
using std::cout;
using std::endl;

#include "Classes/SpeedCounter.h"
#include "Classes/Potentiometer.h"
#include "RobotMap.h"
#include "ControllerMap.h"

class Team316Robot : public IterativeRobot
{
private:
	//
	// Constants
	//
	
	// Shooter setpoints

	// Value for highest target
	const static float SHOOTER_TOP_HEIGHT = 3.7;		// for in competition
	//const static float SHOOTER_TOP_HEIGHT = 3.75;		// for practice; no lip at pyramid

	// Value for lower target
	const static float SHOOTER_MID_HEIGHT = 3.49;
	
	// Absolute bottom value
	const static float SHOOTER_LOWEST_HEIGHT = 2.25;
	
	// Value for loading
	const static float SHOOTER_TEST_LOAD_HEIGHT = 2.5;

	//
	// Declare member variables for the operator interface components
	//
	DriverStation* 	ds;
	Joystick* 		driverController;
	Joystick* 		operatorJoystick;
	
	//
	// Declare member variables for the robot components
	//
	
	// Drivetrain
	SpeedController* 	frontLeftDriveMotor;
	SpeedController* 	frontRightDriveMotor;
	SpeedController*	rearLeftDriveMotor;
	SpeedController*	rearRightDriveMotor;
	RobotDrive* 		driveMotors;
	Encoder* 			leftDriveEncoder;
	Encoder* 			rightDriveEncoder;
	
	// Pickup
	Relay* 				pickupBeltRelay;
	SpeedController* 	pickupAngleMotor;
	Potentiometer* 		pickupAnglePot;
	PIDController*		pickupAngleController;
	Victor*				pickupMotor;
	
	// Shooter
	SpeedController* 	shooterMotor;
	SpeedCounter* 		shooterSpeedCounter;
	PIDController*		shooterSpeedController;
	SpeedController* 	shooterAngleMotor;
	Potentiometer* 		shooterAnglePot;
	PIDController* 		shooterAngleController;
	Solenoid*			shooterPistonSolenoid;

	// Vertical Ascent Initiator
	Solenoid* climbingSolenoid;
	
	// Compressor
	DigitalInput* pressureSwitch;
	Compressor* compressor;
	
	//
	// Declare LiveWindow
	//
	LiveWindow* liveWindow;
	
	//
	// Robot Preferences
	//
	Preferences* prefs;
	
	//
	// Autonomous Data
	//
	SendableChooser* autoModeChooser;	// Can probably be removed
	int autoMode;
	int step;
	double startTime;
	double beginTime;

	//
	// Autonomous Sub-Routines
	//
	void AutonomousMode1();
	void AutonomousMode2();
	void AutonomousMode3();
	void AutonomousMode4();
	void AutonomousMode5();
	void AutonomousMode6();
	
	//
	// Private member functions
	//
	
	//void ProcessCameraImage();
	void UpdateSmartDashboard();

	
public:
	//
	// Robot Constructor
	//
	Team316Robot();

	//
	// RobotInit
	//
	// Called at the start of the program to intialize the robot
	//
	void RobotInit();
	
	//
	// Autonomous Mode Functions
	//
	// These functions control the robot during the Autonomous period, when
	// the robot is controlled by itself
	//
	// AutonomousInit() 	- Called once at the start of Autonomous mode
	// AutonomousPeriodic() - Called at a regular interval (aprox. 20ms) during
	//						  Autonomous Mode
	//
	void AutonomousInit();
	void AutonomousPeriodic();
	
	//
	// Teleop Mode Functions
	//
	// These functions control the robot during Teleop mode, when the robot is
	// controlled by human input
	//
	// TeleopInit()		- Called once at the start of Teleop mode
	// TeleopPeriodic()	- Called at a regular interval (20ms) during Teleop
	//
	void TeleopInit();
	void TeleopPeriodic();
	
	//
	// Test Mode Functions
	//
	// These functions control the robot during Test mode. Use LiveWindow
	// to test the robot subsystems and tune PID controllers
	//
	// TestInit()		- Called once at the start of Test mode
	// TestPeriodic()	- Called at a regular interval during Test mode;
	//					  update LiveWindow
	//
	void TestInit();
	void TestPeriodic();
	
	//
	// Disabled Mode Functions
	//
	// These functions control the robot when it is disabled. Useful for
	// calibrating/resetting sensors and other tasks that don't reaquire robot
	// output.
	//
	// DisabledInit()		- Called once at the start of Disabled mode
	// DisabledPeriodic()	- Called at a regular interval while the robot is
	//						  disabled
	//
	void DisabledInit();
	void DisabledPeriodic();
};

#endif	// TEAM316ROBOT_H_
