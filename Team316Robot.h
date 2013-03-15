//
// Team316Robot.h
//
// Header file for the Robot program
//
// The implementation for each robot mode is split into seperate files:
// - Team316Robot.cpp:				Robot-wide and initializtion code
// - Team316RobotAutonomous.cpp:	Autonomous mode
// - Team316RobotTeleop.cpp:		Teleop mode
// - Team316RobotTest.cpp:			Test mode
// - Team316RobotDisabled.cpp:		Disabled mode
// - Team316RobotVision.cpp:		Vision code
//

#ifndef TEAM316_ROBOT_H_
#define TEAM316_ROBOT_H_

#include "WPILib.h"

#include "Classes/SpeedCounter.h"
#include "Classes/Potentiometer.h"
#include "RobotMap.h"
#include "ControllerMap.h"

class Team316Robot : public IterativeRobot
{
private:
	//
	// Declare member variables for the operator interface
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
	
	// Intake
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

	// Climbing
	Solenoid* climbingSolenoid;
	
	// Compressor
	DigitalInput* pressureSwitch;
	Compressor* compressor;
	
	//
	// Declare LiveWindow
	//
	LiveWindow* liveWindow;
	
	//
	// Declare NetworkTable for Camera data
	//
	//NetworkTable* table;
	
	//
	// Robot Preferences
	//
	Preferences* prefs;
	
	//
	// Autonomous Data
	//
	SendableChooser* autoModeChooser;
	int autoMode;
	int step;
	void AutonomousMode1();
	void AutonomousMode2();
	void AutonomousMode3();
	void AutonomousMode4();
	void AutonomousMode5();
	
	//
	// Private member functions
	//
	
	void ProcessCameraImage();
	void UpdateSmartDashboard();
	
public:
	//
	// Constructor and destructor
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

#endif
