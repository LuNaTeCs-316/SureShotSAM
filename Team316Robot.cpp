/*******************************************************************************
 * Team316Robot.cpp - Initialization and robot-wide code.
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#include "Team316Robot.h"

//
// Team316Robot()
//
// Default constructor; allocate memory for all the dynamic objects
//
Team316Robot::Team316Robot()
{
	// OI
	ds = DriverStation::GetInstance();
	driverController = new Joystick(1);
	operatorJoystick = new Joystick(2);
	
	// Drivetrain
	frontLeftDriveMotor = new Victor(FRONT_LEFT_DRIVE_MOTOR);
	frontRightDriveMotor = new Victor(FRONT_RIGHT_DRIVE_MOTOR);
	rearLeftDriveMotor = new Victor(REAR_LEFT_DRIVE_MOTOR);
	rearRightDriveMotor = new Victor(REAR_RIGHT_DRIVE_MOTOR);
	
	driveMotors = new RobotDrive(frontLeftDriveMotor, frontRightDriveMotor, rearLeftDriveMotor, rearRightDriveMotor);
	leftDriveEncoder = new Encoder_sub (LEFT_DRIVE_ENCODER_A, LEFT_DRIVE_ENCODER_B, false, Encoder::k1X);
	rightDriveEncoder = new Encoder_sub (RIGHT_DRIVE_ENCODER_A, RIGHT_DRIVE_ENCODER_B, false, Encoder::k1X);
	
//NEW
	//encoder yeild 360 ticks per full rotation
	//our wheels are 6 inches or 6*pi = 18.84 inches
	//then 360 ticks = 18.84 inches or 237 ticks per foot
	
	//256/18.84= 13.58 or 163 per foot
	leftFDriveController = new PIDController(5.0, 0.0, 0.0, leftDriveEncoder, frontLeftDriveMotor);
	leftRDriveController = new PIDController(5.0, 0.0, 0.0, leftDriveEncoder, frontRightDriveMotor);
	rightFDriveController = new PIDController(5.0, 0.0, 0.0, rightDriveEncoder, rearLeftDriveMotor);
	rightRDriveController = new PIDController(5.0, 0.0, 0.0, rightDriveEncoder, rearRightDriveMotor);

	
	// Pickup
	pickupBeltRelay = new Relay(PICKUP_BELT_RELAY);
	pickupAngleMotor = new Jaguar(PICKUP_ANGLE_MOTOR);
	pickupAnglePot = new Potentiometer(PICKUP_ANGLE_POT);
	pickupAngleController = new PIDController(-5.0, -0.1, 0.0, pickupAnglePot, pickupAngleMotor);
	pickupMotor = new Victor(8);
	
	// Shooter
	shooterMotor = new Victor(SHOOTER_MOTOR);
	shooterSpeedCounter = new SpeedCounter(SHOOTER_SPEED_COUNTER);
	shooterSpeedController = new PIDController(-0.005, 0.000, 0.0, shooterSpeedCounter, shooterMotor);
	shooterAngleMotor = new Jaguar(SHOOTER_ANGLE_MOTOR);
	shooterAnglePot = new Potentiometer(SHOOTER_ANGLE_POT);
	shooterAngleController = new PIDController(22.5, 0.0, 0.0, shooterAnglePot, shooterAngleMotor);
	shooterPistonSolenoid = new Solenoid(SHOOTER_PISTON_SOLENOID);
	shooterIndicatorSolenoid = new Solenoid(8);

	// Climbing
	climbingSolenoid = new Solenoid(CLIMBING_SOLENOID);
	
	// Compressor
	compressor = new Compressor(COMPRESSOR_PRESSURE_SWITCH, COMPRESSOR_RELAY);
	
	// LiveWindow
	liveWindow = LiveWindow::GetInstance();

	// Robot Preferences
	prefs = Preferences::GetInstance();
	
	// Autonomous mode
	autoModeChooser = new SendableChooser();
	
}

//
// RobotInit()
//
// Robot-wide initialization. Configure the sensors/actuators and
// program variables
//
void Team316Robot::RobotInit()
{
	//
	// Configure Percepion Enhancers
	//
	leftDriveEncoder->Start();
	rightDriveEncoder->Start();

	leftDriveEncoder->Reset();
	rightDriveEncoder->Reset();
	
	// our encoders are set to 4 pulse so this constant below will equate the encode value into meaningful units so
	// we can use the get distance function
	//
	// through experimentation we found out the values below
	leftDriveEncoder->SetDistancePerPulse(0.01);
	rightDriveEncoder->SetDistancePerPulse(0.01);

	//
	// Configure the drive motors
	//
	driveMotors->SetSafetyEnabled(false);
	driveMotors->SetExpiration(0.1);
	driveMotors->SetMaxOutput(1.0);
	driveMotors->SetSensitivity(0.5);
	
	//
	// Start the speed counter and the compressor
	//
	shooterSpeedCounter->Start();
	compressor->Start();
		
	//
	// Configure LiveWindow
	//
	liveWindow->AddActuator("Drivetrain", "FrontLeftMotor", (Victor*) frontLeftDriveMotor);
	liveWindow->AddActuator("Drivetrain", "FrontRightMotor", (Victor*) frontRightDriveMotor);
	liveWindow->AddActuator("Drivetrain", "RearLeftMotor", (Victor*) rearLeftDriveMotor);
	liveWindow->AddActuator("Drivetrain", "RearRightMotor", (Victor*) rearRightDriveMotor);
	liveWindow->AddSensor("Drivetrain", "LeftEncoder", leftDriveEncoder);
	liveWindow->AddSensor("Drivetrain", "RightEncoder", rightDriveEncoder);
	
	liveWindow->AddActuator("Pickup", "BeltRelay", pickupBeltRelay);
	liveWindow->AddActuator("Pickup", "AngleMotor", (Jaguar*) pickupAngleMotor);
	liveWindow->AddSensor("Pickup", "AnglePot", pickupAnglePot);
	liveWindow->AddActuator("Pickup", "AnglePIDController", pickupAngleController);
	liveWindow->AddActuator("Pickup", "Motor", pickupMotor);

	liveWindow->AddActuator("Shooter", "Motor", (Victor*) shooterMotor);
	liveWindow->AddSensor("Shooter", "SpeedCounter", shooterSpeedCounter);
	liveWindow->AddActuator("Shooter", "SpeedPIDController", shooterSpeedController);
	liveWindow->AddActuator("Shooter", "AngleMotor", (Jaguar*) shooterAngleMotor);
	liveWindow->AddSensor("Shooter", "AnglePot", shooterAnglePot);
	liveWindow->AddActuator("Shooter", "AnglePIDController", shooterAngleController);
	
	liveWindow->AddActuator("Climbing", "Solenoid", climbingSolenoid);
	
	// Message indicating setup is done
	std::cout << "RobotInit Done" << std::endl;
}

//
// UpdateSmartDashboard()
//
// Send robot data to the SmartDashboard for debugging purposes. Be carefull
// not to call this too often, as it can cause network lag and potentially
// crash the robot code.
//
void Team316Robot::UpdateSmartDashboard()
{
	/*
	SmartDashboard::PutNumber("LeftDriveMotorSpeed", frontLeftDriveMotor->Get());
	SmartDashboard::PutNumber("RightDriveMotorSpeed", frontRightDriveMotor->Get());
	
	SmartDashboard::PutNumber("PickupAngleMotorSpeed", pickupAngleMotor->Get());
	SmartDashboard::PutNumber("PickupAngle", pickupAnglePot->GetAverageVoltage());
	
	SmartDashboard::PutNumber("ShooterSpeedRPM", shooterSpeedCounter->GetRPM());
	*/
	SmartDashboard::PutNumber("LeftEncoderRate", leftDriveEncoder->GetRate());
	SmartDashboard::PutNumber("RightEncoderRate", rightDriveEncoder->GetRate());

	SmartDashboard::PutNumber("LeftEncoderDistance", leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("RightEncoderDistance", rightDriveEncoder->GetDistance());

	SmartDashboard::PutNumber("ShooterAngle", shooterAnglePot->PIDGet());
	SmartDashboard::PutNumber("ShooterSpeed", shooterSpeedCounter->PIDGet());
	SmartDashboard::PutNumber("ShooterOutput", shooterMotor->Get());
}

//
// START_ROBOT_CLASS()
//
// Macro that hooks into the startup code for the robot
//
START_ROBOT_CLASS(Team316Robot);
