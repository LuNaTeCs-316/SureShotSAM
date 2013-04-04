/*******************************************************************************
 * Team316RobotTeleop.cpp - Teleop mode functions
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 ******************************************************************************/

#include "Team316Robot.h"
//#include "Vision/RGBImage.h"
#include <math.h>

//
// Custom arcade drive parameters
//
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
// @param v	   - the value to be skimmed
// @param gain - gain to adjust how much is skimmed
// @return the skimmed value
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
	
	// Display parameter values
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
	/**************************************************************************
	 * Drivetrain
	 **************************************************************************/
	
	// Simple Arcade drive with Xbox controller
	/*
	driveMotors->ArcadeDrive(driverController->GetY(),
	 	driverController->GetRawAxis(4));
	*/

	// Simple Arcade drive with standard joystick
	//driveMotors->ArcadeDrive(driverController);
	
	/**************************************************************************
	 *
	 * Advanced Arcade Drive w/ Filtering
	 *
	 * Custom arcade drive code includes a multi-step process described below
	 * to provide a highly tunable and acurate arcade drive system
	 *
	 * 1. Joystick filtering
	 * We start by reading in the raw value of the throttle axis and the
	 * turning axis and applying a deadband to these values, specified in the
	 * `deadband` parameter. Next we run these values through a cubic function,
	 * making the input a curve rather than linear. The shape of the curve is
	 * determined by the `throttleGain` and `turnGain` parameters.
	 *
	 * 2. Turn enhancement
	 * Turning the robot is more difficult when the throttle value is higher.
	 * To compensate, we give the turn value a boost when the throttle value
	 * is over 50%.
	 *
	 * 3. Motor Speed Calculations
	 * Use the filtered throttle and turn values to calculate the speed for
	 * the left and right sides of the drivetrain.
	 *
	 * 4. Skimming
	 * Sometimes the output for one side of the drivetrain exceeds 100%. To
	 * compensate, we skim the excess off of each side and apply it in the
	 * opposite direction
	 *
	 * 5. Setting motor speeds
	 * After running all of the above, the calculated values are applied to the
	 * motors.
	 *
	 **************************************************************************/

	//
	// 1. Joystick filtering
	//

	// Read the raw value of the throttle input
	double throttle = -(driverController->GetY());
	
	// If within the deadband, set the value to 0
	if (fabs(throttle) < deadband)
		throttle = 0;

	//
	// Run the value through a cubic function to change it from linear to
	// a curve.
	//
	// f(x) = (A * x^3) + [(1 - A) * x]
	//
	// x = throttle
	// A = throttleGain
	//
	else
		throttle = (throttleGain * (throttle * throttle * throttle)) + ((1 - throttleGain) * throttle);

	// Repeat the above process for the turn value

	// Read the raw value of the turn input
	double turn = driverController->GetRawAxis(4);
	
	// If within the deadband, set the value to 0
	if (fabs(turn) < deadband)
		turn = 0;

	//
	// Run the value through a cubic function to change it from linear to
	// a curve.
	//
	// f(x) = (k * x^3) + [(1 - k) * x]
	//
	// x = turn
	// k = turnGain
	//
	else
		turn = (turnGain * (turn * turn * turn)) + ((1 - turnGain) * turn);
	
	//
	// 2. Turn Enhancment
	//

	//
	// If we are over the threshold, boost the turn value
	//
	// f(x) = x * (k * |throttle|)
	//
	// x = turn
	// k = turnBoostGain
	//
	if (fabs(throttle) > 0.5)
		turn = turn * (turnBoostGain * fabs(throttle));
	
	//
	// 3. Motor speed calculations
	//

	// Calculate the raw values for the left and right sides
	double t_left = throttle + turn;
	double t_right = throttle - turn;
	
	//
	// 4. Skimming
	//

	// Add the skimmed value from the opposite side to determine the final value
	double left = t_left + skim(t_right, skimGain);
	double right = t_right + skim(t_left, skimGain);
	
	// Send data to SmartDashboard for debugging
	//SmartDashboard::PutNumber("LeftMotor", left);
	//SmartDashboard::PutNumber("RightMotor", right);
	// Print the left and right values to standard output for debugging
	std::cout << "LeftMotor: " << left << ", RightMotor: " << right;

	//
	// 5. Set the speed of the motors
	//
	frontLeftDriveMotor->Set(left);
	rearLeftDriveMotor->Set(left);
	frontRightDriveMotor->Set(-right);
	rearRightDriveMotor->Set(-right);
	
	/**************************************************************************
	 * Pickup
	 **************************************************************************/

	//
	// Pickup angle control
	//
	// Control the angle of the pickup system. Positive = down, negative = up
	//
	if (driverController->GetRawButton(PICKUP_LOWER_BUTTON))
	{
		// Lower the pickup
		pickupAngleMotor->Set(1.0);
	}
	else if (driverController->GetRawButton(PICKUP_RAISE_BUTTON))
	{
		// Raise the pickup
		pickupAngleMotor->Set(-1.0);
	}
	else
	{
		// Stop the pickup angle motor
		pickupAngleMotor->Set(0.0);
	}
	
	// Send data to SmartDashboard for debugging
	//SmartDashboard::PutNumber("PickupAngle", pickupAnglePot->GetAverageVoltage());
	
	//
	// Pickup belt control
	//
	// Control the pickup belts. Can be run in both directions.
	// Configured to allowe usage of either a relay or a motor controller.
	// The speed of the pickup is set via the Z axis (thumb wheel on Logitech
	// controller).
	//
	if (operatorJoystick->GetRawButton(PICKUP_ON_BUTTON))
	{
		// Run the pickup in the forward direction
		pickupBeltRelay->Set(Relay::kForward);
		pickupMotor->Set(fabs(operatorJoystick->GetZ()));
	}
	else if (operatorJoystick->GetRawButton(PICKUP_REVERSE_BUTTON))
	{
		// Run the pickup in the reverse direction
		pickupBeltRelay->Set(Relay::kReverse);
		pickupMotor->Set(operatorJoystick->GetZ());
	}
	else
	{
		pickupBeltRelay->Set(Relay::kOff);
		pickupMotor->Set(0.0);
	}
	
	/**************************************************************************
	 * Shooter
	 **************************************************************************/

	//
	// Angle control of the shooter
	//
	if (operatorJoystick->GetRawButton(SHOOTER_TOP_HEIGHT_BUTTON))
	{
		// Position for 3 point target
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
	}
	else if (operatorJoystick->GetRawButton(SHOOTER_MID_HEIGHT_BUTTON))
	{
		// Position for 2 point target
		shooterAngleController->SetSetpoint(SHOOTER_MID_HEIGHT);
		shooterAngleController->Enable();
	}
	else if(operatorJoystick->GetRawButton(SHOOTER_LOAD_HEIGHT_BUTTON))
	{
		// Pickup position
		shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
		shooterAngleController->Enable();
	}
	else
	{
		// Manual control of the shooter angle	
		shooterAngleController->Disable();

		// Read raw value of the input
		float shooterAngleMotorSpeed = operatorJoystick->GetY();

		// Apply deadband to raw input
		if (fabs(shooterAngleMotorSpeed) < 0.2)
			shooterAngleMotorSpeed = 0;
		
		// Set the shooter angle motor's speed
		shooterAngleMotor->Set(shooterAngleMotorSpeed);
	}

	//
	// Firing Motor Control
	//
	if (operatorJoystick->GetRawButton(SHOOTER_MOTOR_BUTTON))
	{
		// Enable the motor under speed control
		shooterSpeedController->SetSetpoint(3750.0);
		shooterSpeedController->Enable();
	}
	else if (operatorJoystick->GetRawButton(5))
	{
		// Spin the motor backwards at slow speed when shooter is jammed
		shooterMotor->Set(.5);
	}
	else
	{
		// Disable the shooter motor
		shooterSpeedController->Disable();
	}
	
	//
	// Firing Piston Control
	//
	if (operatorJoystick->GetRawButton(SHOOTER_FIRING_BUTTON))
		shooterPistonSolenoid->Set(true);
	else
		shooterPistonSolenoid->Set(false);
	
	/**************************************************************************
	 * Climbing
	 **************************************************************************/

	if (operatorJoystick->GetRawButton(CLIMB_BUTTON))
		climbingSolenoid->Set(true);
	else
		climbingSolenoid->Set(false);
	
	/**************************************************************************
	 * Misc.
	 **************************************************************************/

	/*
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
	*/
	
	// Send data to the dashboard
	//UpdateSmartDashboard();

	// Output newline characters to end debugging line
	std::cout << "\n\n";
}
