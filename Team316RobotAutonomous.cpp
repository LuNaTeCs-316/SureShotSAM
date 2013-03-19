//
// Team316RobotAutonomous.cpp
//
// Autonomous mode functions
//

#include "Team316Robot.h"

using namespace std;

//
// AutonomousInit()
//
// Called once at the start of Autonomous Mode to setup
//
void Team316Robot::AutonomousInit()
{
	cout << "Autonomous Init" << endl;
	
	autoMode = (int) ds->GetAnalogIn(1);	// automode is predetermined by the analog sliders on the dashboard
	cout << "Autonomous Mode " << autoMode << " Selected" << endl;

	step = 1;

	/*
	modeString = (char*) autoModeChooser->GetSelected();
	if (strcmp(modeString, "Mode 1") == 0) {
		cout << "Mode 1" << endl;
		autoMode = 1;
	}
	else if (strcmp(modeString, "Mode 2") == 0) {
		cout << "Mode 2" << endl;
		autoMode = 2;
	}
	else {
		cout << "Default" << endl;
		autoMode = 1;
	}
	*/
}

//
// AutonomousPeriodic()
//
// 
//
void Team316Robot::AutonomousPeriodic()
{
	switch (autoMode)
	{
		case 1:
			AutonomousMode1();
			break;
		case 2:
			AutonomousMode2();
			break;
		case 3:
			AutonomousMode3();
			break;
		default:
			// Do nothing
			break;
	}
	UpdateSmartDashboard();
}

void Team316Robot::AutonomousMode1()
{
	static double startTime = GetClock();
	switch (step)
	{
		case 1:
			// Turn the motor on and wait till we're up to speed
			cout << "Step1" << endl;

			shooterAngleController->SetSetpoint(3.6);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();
			
			// Terminating condition check
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 2:
			// Fire the first shot
			cout << "Step2, Time: " << (GetClock() - startTime) << endl;
			shooterAngleController->Disable();
			shooterPistonSolenoid->Set(true);

			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 3:
			// Wait for the motor to come back up to speed
			cout << "Step3" << endl;
			shooterPistonSolenoid->Set(false);
			
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 4:
			// Fire the second shot
			cout << "Step4" << endl;
			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 5:
			// Wait for the motor to come back up to speed
			cout << "Step5" << endl;
			shooterPistonSolenoid->Set(false);
			
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 6:
			// Fire the third shot
			cout << "Step6" << endl;
			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 7:
			// Cleanup
			cout << "Step7" << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			break;
		case 8:
			cout << "Step 8: Done!" << endl;
			break;
		default:
			cout << "Error: default case" << endl;
			break;
	}
}

void Team316Robot::AutonomousMode2()
{
	static double startTime = GetClock();
	switch (step)
	{
		case 1:
			// Turn the motor on and wait till we're up to speed
			cout << "Step1" << endl;

			shooterAngleController->SetSetpoint(3.60);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();
			
			// Terminating condition check
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 2:
			// Fire the first shot
			cout << "Step2" << endl;
			shooterAngleController->Disable();
			shooterPistonSolenoid->Set(true);

			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 3:
			// Wait for the motor to come back up to speed
			cout << "Step3" << endl;
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 4:
			// Fire the second shot
			cout << "Step4" << endl;
			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 5:
			// Wait for the motor to come back up to speed
			cout << "Step5" << endl;
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 6:
			// Fire the third shot
			cout << "Step6" << endl;
			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 7:
			// Cleanup
			cout << "Step7" << endl;
			shooterAngleController->SetSetpoint(3.1);
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			shooterAngleController->SetSetpoint(2.25);
			shooterAngleController->Enable();
			step++;
			startTime = GetClock();
			break;
		case 8:
			// Lower the pickup
			cout << "Step8" << endl;
			
			pickupAngleMotor->Set(-1);
			pickupMotor->Set(-0.9);
			
			if ((GetClock() - startTime) > 2.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 9:
			// Drive backwards to pickup the frisbees
			cout << "Step9" << endl;

			pickupAngleMotor->Set(0.0);
			
			frontLeftDriveMotor->Set(-0.75);
			rearLeftDriveMotor->Set(-0.75);
			frontRightDriveMotor->Set(0.75);
			rearRightDriveMotor->Set(0.75);
			
			if ((GetClock() - startTime) > 1.0) {
				step++;
				startTime = GetClock();
			}
			break;
		case 10:
			// Stop the drive motors and wait
			
			pickupAngleMotor->Set(0);
			
			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			if ((GetClock() - startTime) > 1.0) {
				step++;
				startTime = GetClock();
			}
			break;
		case 11:
			// Drive forwards to the goal
			shooterAngleController->SetSetpoint(3.60);
			shooterAngleController->Enable();
			
			frontLeftDriveMotor->Set(0.4);
			rearLeftDriveMotor->Set(0.4);
			frontRightDriveMotor->Set(-0.4);
			rearRightDriveMotor->Set(-0.4);
			
			pickupAngleMotor->Set(1.0);
			pickupMotor->Set(0.0);
			
			if ((GetClock() - startTime) > 1.0) {
				step++;
				startTime = GetClock();
			}
			break;
		case 12:
			// Stop the drive motors and wait till we're in position to fire
			
			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			shooterSpeedController->SetSetpoint(4200);
			shooterSpeedController->Enable();
			
			pickupAngleMotor->Set(0.0);
			if ((shooterSpeedCounter->PIDGet() > 3900)
					&& shooterAngleController->GetError() < 0.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 13:
			// Fire the first shot
			shooterAngleController->Disable();
			
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 14:
			// Wait for the motor to get back up to speed
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 15:
			// Fire the second shot
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 16:
			// Cleanup
			cout << "Step16" << endl;
			shooterAngleController->SetSetpoint(3.1);
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			startTime = GetClock();
			break;
		case 17:
			cout << "Step 17: Done!" << endl;
			break;
		default:
			cout << "Error: default case" << endl;
			break;
	}
}

void Team316Robot::AutonomousMode3()
{
	static float startTime = GetClock();

	switch (step)
	{
		case 1:
			// Turn the motor on and wait till we're up to speed
			cout << "Step1" << endl;
			shooterAngleController->SetSetpoint(3.65);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();
			
			// Terminating condition check
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 2:
			// Fire the first shot
			cout << "Step2, Time: " << (GetClock() - startTime) << endl;
			shooterAngleController->Disable();
			shooterPistonSolenoid->Set(true);
	
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 3:
			// Wait for the motor to come back up to speed
			cout << "Step3" << endl;
			shooterPistonSolenoid->Set(false);
			
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 4:
			// Fire the second shot
			cout << "Step4" << endl;
			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 5:
			// Wait for the motor to come back up to speed
			cout << "Step5" << endl;
			shooterPistonSolenoid->Set(false);
			
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;
		case 6:
			// Fire the third shot
			cout << "Step6" << endl;
			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.15) {
				step++;
				startTime = GetClock();
			}
			break;
		case 7:
			// Cleanup
			cout << "Step7" << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			break;
		case 8:
			// Lower the pickup partway
			cout << "Step8" << endl;
			
			shooterAngleController->SetSetpoint(2.0);
			shooterAngleController->Enable();
			pickupAngleMotor->Set(-0.75);
			if ((GetClock() - startTime) > 1.25) {
				step++;
				startTime = GetClock();
			}
			break;
		case 9:
			// Drive forwards in front of the two frisbees
			cout << "Step9" << endl;
			
			pickupAngleMotor->Set(0);
			
			frontLeftDriveMotor->Set(0.5);
			rearLeftDriveMotor->Set(0.5);
			frontRightDriveMotor->Set(-0.5);
			rearRightDriveMotor->Set(-0.5);
			
			if ((GetClock() - startTime) > 2.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 10:
			// Lower the pickup partway
			cout << "Step10" << endl;
			
			pickupAngleMotor->Set(-0.75);
			if ((GetClock() - startTime) > 0.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 11:
			// Back into the frisbees and pick them up
			cout << "Step11" << endl;
			
			pickupAngleMotor->Set(0.0);
			pickupMotor->Set(operatorJoystick->GetZ());
			
			frontLeftDriveMotor->Set(-0.5);
			rearLeftDriveMotor->Set(-0.5);
			frontRightDriveMotor->Set(0.5);
			rearRightDriveMotor->Set(0.5);
			
			if ((GetClock() - startTime) > 3.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 12:
			// Stop the robot and pause for a second
			frontLeftDriveMotor->Set(0);
			rearLeftDriveMotor->Set(0);
			frontRightDriveMotor->Set(0);
			rearRightDriveMotor->Set(0);
			
			if ((GetClock() - startTime) > 1.0) {
				step++;
				startTime = GetClock();
			}
			break;
		case 13:
			// Drive forwards to the goal
			shooterAngleController->SetSetpoint(3.65);
			shooterAngleController->Enable();
			
			frontLeftDriveMotor->Set(0.5);
			rearLeftDriveMotor->Set(0.5);
			frontRightDriveMotor->Set(-0.5);
			rearRightDriveMotor->Set(-0.5);
			
			pickupAngleMotor->Set(1.0);
			pickupMotor->Set(0.0);
			
			if ((GetClock() - startTime) > 1.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 14:
			// Stop the drive motors and wait till we're in position to fire
			
			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			shooterSpeedController->SetSetpoint(4200);
			shooterSpeedController->Enable();
			
			pickupAngleMotor->Set(0.0);
			if ((shooterSpeedCounter->PIDGet() > 3900)
					&& shooterAngleController->GetError() < 0.5) {
				step++;
				startTime = GetClock();
			}
			break;
		case 15:
			// Fire the first shot
			shooterAngleController->Disable();
			
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 16:
			// Wait for the motor to get back up to speed
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 17:
			// Fire the second shot
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 18:
			// Wait for the motor to get back up to speed
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 19:
			// Fire the second shot
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 20:
			// Wait for the motor to get back up to speed
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedCounter->PIDGet() > 3900) {
				step++;
				startTime = GetClock();
			}
			break;
		case 21:
			// Fire the second shot
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime > 0.1);
			{
				step++;
				startTime = GetClock();
			}
			break;
		case 22:
			// Cleanup
			cout << "Step16" << endl;
			shooterAngleController->SetSetpoint(3.1);
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			startTime = GetClock();
			break;	
		default:
			cout << "Error: default case" << endl;
			break;
		
	}
}
