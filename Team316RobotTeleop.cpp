//
// Team316RobotTeleop.cpp
//
// Teleop mode functions
//

#include "Team316Robot.h"
#include "Vision/RGBImage.h"
#include <math.h>

// Custom arcade drive parameters
double throttleGain = 1.0;
double turnGain = 1.0;
double deadband = 0.2;
double turnBoostGain = 0.5;
double skimGain = 0.5;

//
// skim(v, gain)
//
// Takes a portion of the excess value from one side of the drivetrain
// to be applied to the other side.
//
double skim(double v, double gain)
{
	if (v > 1.0)
		return ((v - 1.0) * gain);
	else if (v < -1.0)
		return ((v + 1.0) * gain);
	return 0;
}

//
// TeleopInit()
//
// Setup for teleop mode
//
void Team316Robot::TeleopInit()
{
	compressor->Start();
	
	// Retrive ArcadeDrive parameters values
	throttleGain = prefs->GetDouble("throttleGain", 1.0);
	turnGain = prefs->GetDouble("turnGain", 1.0);
	deadband = prefs->GetDouble("deadband", 0.2);
	turnBoostGain = prefs->GetDouble("turnBoostGain", 0.6);
	skimGain = prefs->GetDouble("skimGain", 0.6);
	
	// Check parameter values
	std::cout << "throttleGain: " << throttleGain << ", turnGain: " << turnGain
			<< ", deadband: " << deadband << ", turnBoostGain: " << turnBoostGain
			<< ", skimGain: " << skimGain << std::endl;
}

//
// TeleopPeriodic()
//
// Runs approx. every 20 ms; the main Teleop mode loop
//
void Team316Robot::TeleopPeriodic()
{
	//
	// Drivetrain
	//
	
	// Simple Arcade drive with Xbox controller
	//driveMotors->ArcadeDrive(driverController->GetY(), driverController->GetRawAxis(4));
	// Simple Arcade drive with standard joystick
	//driveMotors->ArcadeDrive(driverController);
	
	// Advanced Arcade Drive w/ Filtering
	
	// Joystick filtering
	// Apply cubic function and deadband to joystick inputs
	double throttle = -(driverController->GetY());
	if (fabs(throttle) < deadband) {
		throttle = 0;
	} else {
		throttle = (throttleGain * (throttle * throttle * throttle)) +
			((1 - throttleGain) * throttle);
	}
	
	double turn = driverController->GetRawAxis(4);
	
	if (fabs(turn) < deadband) {
		turn = 0;
	} else {
		turn = (turnGain * (turn * turn * turn)) + ((1 - turnGain) * turn);
	}
	
	// Enhance the turn value when necessary
	if (fabs(throttle) > 0.5) {
		turn = turn * (turnBoostGain * fabs(throttle));
	}
	
	double t_left = throttle + turn;
	double t_right = throttle - turn;
	
	double left = t_left + skim(t_right, skimGain);
	double right = t_right + skim(t_left, skimGain);
	
	//SmartDashboard::PutNumber("t_left", t_left);
	//SmartDashboard::PutNumber("t_right", t_right);
	SmartDashboard::PutNumber("LeftMotor", left);
	SmartDashboard::PutNumber("RightMotor", right);
	
	frontLeftDriveMotor->Set(left);
	rearLeftDriveMotor->Set(left);
	frontRightDriveMotor->Set(-right);
	rearRightDriveMotor->Set(-right);
	
	//
	// Pickup
	//
	
	/*
	if (operatorJoystick->GetRawButton(8)) {
		pickupAngleController->SetSetpoint(2.486);
		pickupAngleController->Enable();
	} else if (operatorJoystick->GetRawButton(9)) {
		pickupAngleController->SetSetpoint(2.332);
		pickupAngleController->Enable();
	} else if (operatorJoystick->GetRawButton(10)) {
		pickupAngleController->SetSetpoint(2.075);
		pickupAngleController->Enable();
	} else {
		pickupAngleController->Disable();
		pickupAngleMotor->Set(operatorJoystick->GetX());
	}
	*/
	if (driverController->GetRawButton(5)
//			&& (shooterAngleController->GetSetpoint() <= 3.2) 
			) {
		pickupAngleMotor->Set(1.0);
	} else if ( driverController->GetRawButton(6)
//			&& (shooterAngleController->GetSetpoint() <= 3.2) 
			) {
		pickupAngleMotor->Set(-1.0);
	} else {
		pickupAngleMotor->Set(0.0);
	}
	
	SmartDashboard::PutNumber("PickupAngle", pickupAnglePot->GetAverageVoltage());
	
	/*
	if (operatorJoystick->GetRawButton(6)) {
		pickupBeltRelay->Set(Relay::kForward);
	} else if (operatorJoystick->GetRawButton(7)) {
		pickupBeltRelay->Set(Relay::kReverse);
	} else {
		pickupBeltRelay->Set(Relay::kOff);
	}
	*/
	
	if (operatorJoystick->GetRawButton(6)) {
		pickupBeltRelay->Set(Relay::kForward);
		pickupMotor->Set(-operatorJoystick->GetZ());
	} 
	else if (operatorJoystick->GetRawButton(7)) {
		pickupMotor->Set(operatorJoystick->GetZ());
	}
	else {
		pickupBeltRelay->Set(Relay::kOff);
		pickupMotor->Set(0.0);
	}
	
	//
	// Shooter
	//
	
	// Camera aiming
	/*
	static bool prevAimingButtonValue = false;
	bool aimingButtonValue = operatorJoystick->GetRawButton(SHOOTER_AIMING_BUTTON);
	if (aimingButtonValue && !prevAimingButtonValue)
		ProcessCameraImage();
	prevAimingButtonValue = aimingButtonValue;
	*/
	
	// Angle Control
	if (operatorJoystick->GetRawButton(11)) //3 point target
	{
<<<<<<< HEAD
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
=======
		shooterAngleController->SetSetpoint(4.2);
>>>>>>> parent of c8892c9... Add skeleton code for Autonomous Modes 3-5
		shooterAngleController->Enable();
	}
	else if (operatorJoystick->GetRawButton(10)) //2 point target
	{
<<<<<<< HEAD
		shooterAngleController->SetSetpoint(SHOOTER_MID_HEIGHT);
		shooterAngleController->Enable();
	}
	else if(operatorJoystick->GetRawButton(6)) //pickup position
	{
		shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
=======
		shooterAngleController->SetSetpoint(4.1);
>>>>>>> parent of c8892c9... Add skeleton code for Autonomous Modes 3-5
		shooterAngleController->Enable();
	}
	else
	{
		// Manual control of the shooter angle	
		shooterAngleController->Disable();

		// Apply deadband to joystick
		float shooterAngleMotorSpeed = operatorJoystick->GetY();
		if (fabs(shooterAngleMotorSpeed) < 0.2)
			shooterAngleMotorSpeed = 0;
		
		// Manually control the shooter angle motor
		shooterAngleMotor->Set(shooterAngleMotorSpeed);
	}
	
	// Motor Control
	if (operatorJoystick->GetRawButton(SHOOTER_MOTOR_BUTTON))
	{
		shooterSpeedController->SetSetpoint(3750.0);
		shooterSpeedController->Enable();
		//shooterMotor->Set(-1);
	}
	else if (operatorJoystick->GetRawButton(5))
	{
		shooterMotor->Set(.5);
	}
	else
	{
		shooterSpeedController->Disable();
		//shooterMotor->Set(0.0);
	}
	
	// Piston Control
	if (operatorJoystick->GetRawButton(SHOOTER_FIRING_BUTTON))
	{
		shooterPistonSolenoid->Set(true);
	}
	else
	{
		shooterPistonSolenoid->Set(false);
	}
	
	// Climbing
	if (operatorJoystick->GetRawButton(4))
	{
		climbingSolenoid->Set(true);
	}
	else
	{
		climbingSolenoid->Set(false);
	}
	
	// Camera snapshot
	AxisCamera &camera = AxisCamera::GetInstance();
	static bool prevCameraButtonValue = false;
	bool cameraButtonValue = operatorJoystick->GetRawButton(CAMERA_SNAPSHOT_BUTTON);
	if (cameraButtonValue && !prevCameraButtonValue)
	{
		ColorImage* image = new RGBImage();
		camera.GetImage(image);
		if (image)
		{
			image->Write("snapshot.jpg");
			std::cout << "Snapshot saved at " << GetClock() << "ms" << std::endl;
		}
		else 
			printf("Error: could not acquire image\n");
		delete image;
	}
	prevCameraButtonValue = cameraButtonValue;
	
	// Send data to the dashboard
	UpdateSmartDashboard();
}
