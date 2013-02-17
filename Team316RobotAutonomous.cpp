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
	char* modeString = (char*) autoModeChooser->GetSelected();
	cout << modeString << endl;
	
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
		default:
			// Do nothing
			break;
	}
	UpdateSmartDashboard();
}

void Team316Robot::AutonomousMode1()
{
	static int step = 1;
	double startTime = GetClock();
	switch (step)
	{
		case 1:
			// Turn the motor on and wait till we're up to speed
			cout << "Step1" << endl;
			shooterSpeedController->SetSetpoint(5000);
			shooterSpeedController->Enable();
			
			// Terminating condition check
			if (shooterSpeedController->GetError() < 1000) {
				step++;
				startTime = GetClock();
			}
			break;
		case 2:
			// Fire the first shot
			cout << "Step2" << endl;
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime >= 150) {
				step++;
				startTime = GetClock();
			}
			break;
		case 3:
			// Wait for the motor to come back up to speed
			cout << "Step3" << endl;
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedController->GetError() < 1000) {
				step++;
				startTime = GetClock();
			}
			break;
		case 4:
			// Fire the second shot
			cout << "Step4" << endl;
			shooterPistonSolenoid->Set(true);			
			
			if (GetClock() - startTime >= 150) {
				step++;
				startTime = GetClock();
			}
			break;
		case 5:
			// Wait for the motor to come back up to speed
			cout << "Step5" << endl;
			shooterPistonSolenoid->Set(false);
			
			if (shooterSpeedController->GetError() < 500) {
				step++;
				startTime = GetClock();
			}
			break;
		case 6:
			// Fire the third shot
			cout << "Step6" << endl;
			shooterPistonSolenoid->Set(true);
			
			if (GetClock() - startTime >= 150) {
				step++;
				startTime = GetClock();
			}
			break;
		case 7:
			// Cleanup
			cout << "Step7" << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
		default:
			cout << "Error: default case" << endl;
			break;
	}
}

void Team316Robot::AutonomousMode2()
{
	
}
