//
// Team316Robot.cpp
//
// Initialization and robot-wide code
//

#include "Team316Robot.h"

//
// Team316Robot()
//
// Default constructor; allocate memory for all the dynamic objects
//
Team316Robot::Team316Robot()
{
	// OI
	driverController = new Joystick(1);
	operatorJoystick = new Joystick(2);
	
	// Drivetrain
	leftDriveMotor = new Jaguar(LEFT_DRIVE_MOTOR);
	rightDriveMotor = new Jaguar(RIGHT_DRIVE_MOTOR);
	driveMotors = new RobotDrive(leftDriveMotor, rightDriveMotor);
	leftDriveEncoder = new Encoder(LEFT_DRIVE_ENCODER_A, LEFT_DRIVE_ENCODER_B, false, Encoder::k4X);
	rightDriveEncoder = new Encoder(RIGHT_DRIVE_ENCODER_A, RIGHT_DRIVE_ENCODER_B, false, Encoder::k4X);
	
	// Pickup
	pickupBeltRelay = new Relay(PICKUP_BELT_RELAY);
	pickupAngleMotor = new Jaguar(PICKUP_ANGLE_MOTOR);
	pickupAnglePot = new Potentiometer(PICKUP_ANGLE_POT);
	pickupAngleController = new PIDController(1.0, 0.0, 0.0, pickupAnglePot, pickupAngleMotor);
	
	// Shooter
	shooterMotor = new Victor(SHOOTER_MOTOR);
	shooterSpeedCounter = new SpeedCounter(SHOOTER_SPEED_COUNTER);
	shooterSpeedController = new PIDController(0.004, 0.000, 0.0, shooterSpeedCounter, shooterMotor);
	shooterAngleMotor = new Victor(SHOOTER_ANGLE_MOTOR);
	shooterAnglePot = new Potentiometer(SHOOTER_ANGLE_POT);
	shooterAngleController = new PIDController(20.0, 0.0, 0.0, shooterAnglePot, shooterAngleMotor);
	shooterPistonSolenoid = new Solenoid(SHOOTER_PISTON_SOLENOID);
	
	// Compressor
	compressor = new Compressor(COMPRESSOR_PRESSURE_SWITCH, COMPRESSOR_RELAY);
	
	// LiveWindow
	liveWindow = LiveWindow::GetInstance();

	// Robot Preferences
	prefs = Preferences::GetInstance();
	
	table = NetworkTable::GetTable("SmartDashboard");
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
	// Configure sensors
	//
	leftDriveEncoder->Start();
	rightDriveEncoder->Start();
	
	driveMotors->SetSafetyEnabled(false);
	driveMotors->SetExpiration(0.1);
	driveMotors->SetMaxOutput(1.0);
	driveMotors->SetSensitivity(0.5);
	driveMotors->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	driveMotors->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	
	shooterSpeedCounter->Start();
	
	compressor->Start();
	
	
	//
	// Configure LiveWindow
	//
	liveWindow->AddActuator("Drivetrain", "LeftMotor", (Jaguar*) leftDriveMotor);
	liveWindow->AddActuator("Drivetrain", "RightMotor", (Jaguar*) rightDriveMotor);
	liveWindow->AddSensor("Drivetrain", "LeftEncoder", leftDriveEncoder);
	liveWindow->AddSensor("Drivetrain", "RightEncoder", rightDriveEncoder);
	
	liveWindow->AddActuator("Pickup", "BeltRelay", pickupBeltRelay);
	liveWindow->AddActuator("Pickup", "AngleMotor", (Jaguar*) pickupAngleMotor);
	liveWindow->AddSensor("Pickup", "AnglePot", pickupAnglePot);
	liveWindow->AddActuator("Pickup", "AnglePIDController", pickupAngleController);

	liveWindow->AddActuator("Shooter", "Motor", (Victor*) shooterMotor);
	liveWindow->AddSensor("Shooter", "SpeedCounter", shooterSpeedCounter);
	liveWindow->AddActuator("Shooter", "SpeedPIDController", shooterSpeedController);
	liveWindow->AddActuator("Shooter", "AngleMotor", (Victor*) shooterAngleMotor);
	liveWindow->AddSensor("Shooter", "AnglePot", shooterAnglePot);
	liveWindow->AddActuator("Shooter", "AnglePIDController", shooterAngleController);
	
	std::cout << "RobotInit Done" << std::endl;
}

//
// UpdateSmartDashboard()
//
// Send robot data to the SmartDashboard for debugging purposes. Can be called
// from any periodic loop.
//
void Team316Robot::UpdateSmartDashboard()
{
	/*
	SmartDashboard::PutNumber("LeftDriveMotorSpeed", leftDriveMotor->Get());
	SmartDashboard::PutNumber("RightDriveMotorSpeed", rightDriveMotor->Get());
	SmartDashboard::PutNumber("LeftEncoderRate", leftDriveEncoder->GetRate());
	SmartDashboard::PutNumber("RightEncoderRate", rightDriveEncoder->GetRate());
	SmartDashboard::PutNumber("LeftEncoderDistance", leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("RightEncoderDistance", rightDriveEncoder->GetDistance());
	
	SmartDashboard::PutNumber("PickupAngleMotorSpeed", pickupAngleMotor->Get());
	SmartDashboard::PutNumber("PickupAngle", pickupAnglePot->GetAverageVoltage());
	
	SmartDashboard::PutNumber("ShooterMotorSpeed", shooterMotor->Get());
	SmartDashboard::PutNumber("ShooterSpeedCount", shooterSpeedCounter->Get());
	SmartDashboard::PutNumber("ShooterSpeedRPM", shooterSpeedCounter->GetRPM());
	SmartDashboard::PutNumber("ShooterAngleMotor", shooterAngleMotor->Get());
	SmartDashboard::PutNumber("ShooterAngle", shooterAnglePot->GetAverageVoltage());
	*/
	SmartDashboard::PutNumber("ShooterAngle", shooterAnglePot->PIDGet());
	SmartDashboard::PutNumber("ShooterSpeed", shooterSpeedCounter->PIDGet());
}

//
// START_ROBOT_CLASS()
//
// Macro that hooks into the startup code for the robot
//
START_ROBOT_CLASS(Team316Robot);
