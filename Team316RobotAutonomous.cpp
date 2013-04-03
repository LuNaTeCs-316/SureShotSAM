/*******************************************************************************
 * Team316RobotAutonomous.cpp - Autonomous mode functions
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#include "Team316Robot.h"
using std::cout;
using std::endl;

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
			//TESTING ONLY - experimentation with encoders and PIDs
		case 6:
			AutonomousMode6();
			break;
		default:
			// Do nothing
			break;
	}

	// Send data to SmartDashboard for debugging
	//UpdateSmartDashboard();
}

//***********************************************************
//
// AUTONOMOUS MODE 1 - SHOOOT 3 FRISBEES THEN STOP
//
//***********************************************************
void Team316Robot::AutonomousMode1()
{
	switch (step)
	{
		case 1: // Turn the motor on and wait till we're up to speed
			cout << "auto 1:1 -shooter speed = " << (shooterSpeedCounter->GetRPM() )<< ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();
			shooterPistonSolenoid->Set(false);
			
			//during testing this only achieves about 3600 rpm by 2.5 seconds
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 3) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 2: // Fire the first shot
			cout << "auto 1:2 - Fire the first shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 3: // Wait for the motor to come back up to speed
			cout << "auto 1:3 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(false);
			
			//we lose approximately 500rpm in the shot - it takes approx 500ms to recover that
			if (    ( (shooterSpeedCounter->PIDGet() > 3800) && (GetClock() - startTime > 0.4) )
				|| ((GetClock() - startTime) > 2.0) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 4: // Fire the second shot
			cout << "auto 1:4 - Fire the second shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 5: // Wait for the motor to come back up to speed
			cout << "auto 1:5 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(false);
			
			if ( ( (shooterSpeedCounter->PIDGet() > 3800) &&(GetClock() - startTime > 0.4) )
				|| ((GetClock() - startTime) > 2.0) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 6: // Fire the third shot
			cout << "auto 1:6 - Fire the third shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 7: // turn off motor and retract piston
			cout << "auto 1:7 - turn off motor and retract piston.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			break;
		case 8:
			break;
		default:
			cout << "auto 1:default  Error.  You should not be here" << endl;
			break;
	}//END OF SWITCH
}//END OF AUTO 1





//***********************************************************
//
// AUTONOMOUS MODE 2 - SHOOOT 3 FRISBEES THEN BACKUP AND PICK UP 2 FRISBEES OFF LINE THEN SHOOT THEM - use dead reckoning
//
//***********************************************************
void Team316Robot::AutonomousMode2()
{
	switch (step)
	{
	case 1: // Turn the motor on and wait till we're up to speed
		cout << "auto 2:1 -shooter speed = " << (shooterSpeedCounter->GetRPM() )<< ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;

		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();
		
		//during testing this only achieves about 3600 rpm by 2.5 seconds
		if ( (shooterSpeedCounter->PIDGet() > 3800)
			|| ((GetClock() - startTime) > 2.5) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 2: // Fire the first shot
		cout << "auto 2:2 - Fire the first shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;

	case 3: // Wait for the motor to come back up to speed
		//we lose approximately 500rpm in the shot - it takes approx 500ms to recover that
		cout << "auto 2:3 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(false);
		
		if (    ( (shooterSpeedCounter->PIDGet() > 3800) && (GetClock() - startTime > 0.2) )
			|| ((GetClock() - startTime) > 1.5) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 4: // Fire the second shot
		cout << "auto 2:4 - Fire the second shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);			
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;

	case 5:// Wait for the motor to come back up to speed
		cout << "auto 2:5 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(false);
		
		if (    ( (shooterSpeedCounter->PIDGet() > 3800) &&(GetClock() - startTime > 0.2) )
			|| ((GetClock() - startTime) > 1.5) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 6: // Fire the third shot
		cout << "auto 2:6 - Fire the third shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;

		case 7://pause so we do not disrupt the frisbee exiting the shooter
			cout << "auto 2:7 - Pause so we do not disrupt the exiting frisbee.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 8: // it takes exactly 4 second to lower the shooter from
				// shooting position to loading position
			cout << "auto 2:8 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();

			shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
			shooterAngleController->Enable();

			if (GetClock() - startTime > .5) {
				step++;
				startTime = GetClock();
			}
			break;
			
		case 9: // here we are still continuing to lower the shooter
				// but now that it is out of the way we can also lower the pickup arm
			cout << "auto 2:9 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
			shooterAngleController->Enable();

			pickupAngleMotor->Set(-1.0);

//TEST: this was a 3 second wait
			if ( (GetClock() - startTime > 2.5)
				|| ( shooterAnglePot->GetAverageVoltage() <= (SHOOTER_LOWEST_HEIGHT + .05) ) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 10: // Drive backwards to pickup the frisbees - using dead reckoning and timing to know when to stop
			cout << "auto 2:10 - Drive back. shooter angle = "<< (shooterAnglePot->GetAverageVoltage())   <<" time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(-1.0);
			shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
			shooterAngleController->Enable();

			frontLeftDriveMotor->Set(-0.5);
			rearLeftDriveMotor->Set(-0.5);
			frontRightDriveMotor->Set(0.5);
			rearRightDriveMotor->Set(0.5);
			
			if ((GetClock() - startTime) > 2.0) {
				step++;
				startTime = GetClock();
			}
			break;

		case 11: // Stop the drive motors and wait for a moment
			cout << "auto 2:11 - Pause and pickup.  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(0.0); //we have to do this so that code does not lock
			
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			
			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			if ((GetClock() - startTime) > .15) {
				step++;
				startTime = GetClock();
			}
			break;

		case 12: // Drive forwards to the goal
			cout << "auto 2:12 - Drive forward.  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(1.0);
					
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			
			frontLeftDriveMotor->Set(0.37); //it appears that the left drive is a little weaker in testing
			rearLeftDriveMotor->Set(0.37);
			frontRightDriveMotor->Set(-0.30);
			rearRightDriveMotor->Set(-0.30);
			
			if ((GetClock() - startTime) > 2.4) { //this allows the bot to coast into the stops
				step++;
				startTime = GetClock();
			}
			break;
			
		case 13: // Stop the drive motors and wait till we're in position to fire
			cout << "auto 2:13 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;

			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(1.0);

			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();

//TEST: not sure if we should go with 4500 here to save time later on recoup but might be too strong?
			shooterSpeedController->SetSetpoint(3800);
			shooterSpeedController->Enable();
			
			if (shooterAnglePot->GetAverageVoltage() >= (SHOOTER_TOP_HEIGHT - .05)
//TEST: this should actually take about 2.7 seconds or so
				|| (GetClock() - startTime) > 3.2){
				step++;
				startTime = GetClock();
			}
			break;

		case 14: // Fire the 4th shot
			cout << "auto 2:14 - Fire the 4th shot. shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupMotor->Set(0.0);
			pickupAngleMotor->Set(1.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 15: // Wait for the motor to come back up to speed
			cout << "auto 2:15 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;

			pickupAngleMotor->Set(1.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(false);
			
//TEST: we are almost out of time here so just throwing them up - in all likelyhood we only have 1 frisbee
			if ( ( (shooterSpeedCounter->PIDGet() > 3800) && (GetClock() - startTime > 0.1) )
				|| ((GetClock() - startTime) > 1.5) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 16: // Fire the 5th shot
			cout << "auto 2:16 - Fire the 5th shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupAngleMotor->Set(1.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 17:
			// Cleanup
			cout << "auto 2:17 - cleanup" << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupAngleMotor->Set(0.0);
			shooterAngleController->Disable();
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			startTime = GetClock();
			break;

		case 18:
			break;

		default:
			cout << "auto 2:default  Error.  You should not be here" << endl;
			break;
	}
}//END OF AUTO 2







//***********************************************************
//
// AUTONOMOUS MODE 3 -
//
//***********************************************************
void Team316Robot::AutonomousMode3()
{
	switch (step) {
	case 1: // Turn the motor on and wait till we're up to speed
		cout << "auto 3:1 -shooter speed = " << (shooterSpeedCounter->GetRPM() )<< ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;

		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();
		
		if ( (shooterSpeedCounter->PIDGet() > 3800)
			|| ((GetClock() - startTime) > 2.9) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 2: // Fire the first shot
		cout << "auto 3:2 - Fire the first shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;

	case 3: // Wait for the motor to come back up to speed
		//we lose approximately 500rpm in the shot - it takes approx 500ms to recover that
		cout << "auto 3:3 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT + .05);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(false);
		
		if (    ( (shooterSpeedCounter->PIDGet() > 3800) && (GetClock() - startTime > 0.4) )
			|| ((GetClock() - startTime) > 0.8) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 4: // Fire the second shot
		cout << "auto 3:4 - Fire the second shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);			
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;

	case 5: // Wait for the motor to come back up to speed
		cout << "auto 3:5 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(false);
		
		if (    ( (shooterSpeedCounter->PIDGet() > 3800) &&(GetClock() - startTime > 0.4) )
			|| ((GetClock() - startTime) > 0.8) ) {
			step++;
			startTime = GetClock();
		}
		break;

	case 6: // Fire the third shot
		cout << "auto 3:6 - Fire the third shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
		shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
		shooterAngleController->Enable();
		shooterSpeedController->SetSetpoint(4500);
		shooterSpeedController->Enable();

		shooterPistonSolenoid->Set(true);
		
		if ((GetClock() - startTime) > 0.05) {
			step++;
			startTime = GetClock();
		}
		break;
		
		case 7://pause so we do not disrupt the frisbee exiting the shooter
//			cout << "auto 3:7 - Pause so we do not disrupt the exiting frisbee.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 8: // it takes exactly 4 second to lower the shooter from shooting position to loading position
//			cout << "auto 3:8 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
			shooterAngleController->Enable();

			if (GetClock() - startTime > .5) {
				step++;
				startTime = GetClock();
			}
			break;
			
		case 9: // here we are still continuing to lower the shooter but now that it is out of the way we can also lower the pickup arm
			cout << "auto 3:9 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
			shooterAngleController->Enable();

			pickupAngleMotor->Set(-1.0);

			if ( (GetClock() - startTime > 2.5)
				|| ( shooterAnglePot->GetAverageVoltage() <= (SHOOTER_LOWEST_HEIGHT + .05) ) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 10: //here we are making sure the encoders are reset before we use them
//			cout << "auto 3:10 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			leftDriveEncoder->Reset();
			rightDriveEncoder->Reset();

//			cout << "auto 3:10 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			step++;
			startTime = GetClock();
		break;

		case 11: // Drive backwards to pickup the frisbees using encoders
			cout << "auto 3:11-Drive back. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			pickupAngleMotor->Set(-1.0);
			pickupMotor->Set(-0.9);


			//since our distance Per Pulse is .01 then a value of 50 equates to 5000 pulses
			if (leftDriveEncoder->GetDistance() <= 14.0) {
				frontLeftDriveMotor->Set(-0.9);
				rearLeftDriveMotor->Set(-0.9);
				frontRightDriveMotor->Set(0.9);
				rearRightDriveMotor->Set(0.9);
			} else {
				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);
			}//end of left side

/*this commented since right encoder is not working
 * 			
			//since our distance Per Pulse is .01 then a value of 50 equates to 5000 pulses
			if (leftDriveEncoder->GetDistance() <= 14.0) {
				frontLeftDriveMotor->Set(-0.75);
				rearLeftDriveMotor->Set(-0.75);
			} else {
				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
			}//end of left side

			//this encoder per pulse value is not .01 but .035
			if (rightDriveEncoder->GetDistance() <= 14.0) {
				frontRightDriveMotor->Set(0.9);
				rearRightDriveMotor->Set(0.9);
			} else {
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);
			}//end of right side
*/
			if ( ((leftDriveEncoder->GetDistance() >= 13.9) 
					//&& (rightDriveEncoder->GetDistance() >= 13.9)
					)
					|| ((GetClock() - startTime) > 2.0) ){
				step++;
				startTime = GetClock();
			}
			break;

		case 12: // Stop the drive motors and wait
//			cout << "auto 3:12 - Pause.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(0.0); //this is necessary to prevent lockup
			
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			
			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			if ((GetClock() - startTime) > .05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 13: //reset encoders - this is probably unnnecessary
//			cout << "auto 3:13 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			leftDriveEncoder->Reset();
			rightDriveEncoder->Reset();

//			cout << "auto 5:1 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			step++;
			startTime = GetClock();
		break;

		case 14: // Drive forwards to the goal
			cout << "auto 3:14 - Drive forward.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(.8); //raise arm
					
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			

			if (leftDriveEncoder->GetDistance() >= -8.0) {
				frontLeftDriveMotor->Set(0.65);
				rearLeftDriveMotor->Set(0.65);
				frontRightDriveMotor->Set(-0.35);
				rearRightDriveMotor->Set(-0.35);
			} else {
				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);
			}//end of left side


/*			
			//since our distance Per Pulse is .01 then a value of 50 equates to 5000 pulses
			if (leftDriveEncoder->GetDistance() >= -13.0) {
				frontLeftDriveMotor->Set(0.41);
				rearLeftDriveMotor->Set(0.41);
			} else {
				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
			}//end of left side


			if (rightDriveEncoder->GetDistance() >= -13.0) {
				frontRightDriveMotor->Set(-0.5);
				rearRightDriveMotor->Set(-0.5);
			} else {
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);
			}//end of right side
	*/		
			if ( ((leftDriveEncoder->GetDistance() <= -7.9) 
					//&& (rightDriveEncoder->GetDistance() <= -12.9)
					)
					|| ((GetClock() - startTime) > 3.0) ){
				step++;
				startTime = GetClock();
			}
			break;
			
		case 15: // Stop the drive motors and wait till we're in position to fire
			cout << "auto 3:15 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;

			pickupMotor->Set(-0.9);
			pickupAngleMotor->Set(1.0);

			frontLeftDriveMotor->Set(0.0);
			rearLeftDriveMotor->Set(0.0);
			frontRightDriveMotor->Set(0.0);
			rearRightDriveMotor->Set(0.0);
			
			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();

			shooterSpeedController->SetSetpoint(3800);
			shooterSpeedController->Enable();
			
				if (shooterAnglePot->GetAverageVoltage() >= (SHOOTER_TOP_HEIGHT - .05)
					|| (GetClock() - startTime) > 3.2){
				step++;
				startTime = GetClock();
			}
			break;

		case 16: // Fire the 4th shot
//			cout << "auto 3:16 - Fire the 4th shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupMotor->Set(0.0);
			pickupAngleMotor->Set(0.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);

			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 17: // Wait for the motor to come back up to speed
//			cout << "auto 3:17 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupMotor->Set(0.0);
			pickupAngleMotor->Set(0.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(false);
			
			if ( (shooterSpeedCounter->PIDGet() > 3800)
				|| ((GetClock() - startTime) > 0.3) ) {
				step++;
				startTime = GetClock();
			}
			break;

		case 18: // Fire the 5th shot
//			cout << "auto 3:18 - Fire the 5th shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupMotor->Set(0.0);
			pickupAngleMotor->Set(0.0);

			shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
			shooterAngleController->Enable();
			shooterSpeedController->SetSetpoint(4500);
			shooterSpeedController->Enable();

			shooterPistonSolenoid->Set(true);			
			
			if ((GetClock() - startTime) > 0.05) {
				step++;
				startTime = GetClock();
			}
			break;

		case 19:
			// Cleanup
//			cout << "auto 3:19 - cleanup" << "Tot Time: " << (GetClock() - beginTime) << endl;
			pickupMotor->Set(0.0);
			pickupAngleMotor->Set(0.0);
			shooterAngleController->Disable();
			shooterPistonSolenoid->Set(false);
			shooterSpeedController->Disable();
			step++;
			startTime = GetClock();
			break;

		case 20:
			break;

		default:
			cout << "auto 3:default  Error.  You should not be here" << endl;
			break;
	}
}//end of auto 3



//***********************************************************
//
// AUTONOMOUS MODE 4 - TESTING OF RAISING/LOWERING SHOOTER
//
//***********************************************************
	void Team316Robot::AutonomousMode4()
	{

		shooterPistonSolenoid->Set(false);
		shooterSpeedController->Disable();

		switch (step)
		{
			case 1: // this mode proved out that it takes exactly 4 second to lower the shooter
				cout << "auto 4:1 lower shooter: actual = " << (shooterAnglePot->GetAverageVoltage())<< ".  time = "<< (GetClock() - startTime)<< endl;
				shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
				shooterAngleController->Enable();
				if (GetClock() - startTime > 4.0) {
					step++;
					startTime = GetClock();
				}
				break;
	
				//SHOOTER_TEST_LOAD_HEIGHT
			case 2: // this mode proved out that it takes exactly > 5 second to raise the shooter
				cout << "auto 4:2 raise shooter: actual = " << (shooterAnglePot->GetAverageVoltage())<< ".  time = "<< (GetClock() - startTime)<< endl;
				shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
				shooterAngleController->Enable();
				if (GetClock() - startTime > 7.0) {
					step++;
					startTime = GetClock();
				}
				break;

			case 3:
				cout << "auto 4:3 - STOP" << endl;
				shooterAngleController->Disable();
				if (GetClock() - startTime > 2.5)
				{
					step++;
					startTime = GetClock();
				}
				break;

		}//end of switch
	}//end of auto 4




	//***********************************************************
	//
	// AUTONOMOUS MODE 5 - TESTING OF encoder driving
	//
	//***********************************************************
		void Team316Robot::AutonomousMode5()
		{
			switch (step) {
			case 1: //reset encoders
				cout << "auto 5:1 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
				shooterPistonSolenoid->Set(false);
				shooterSpeedController->Disable();
				shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
				shooterAngleController->Enable();
				pickupAngleMotor->Set(0);
				pickupMotor->Set(0.0);

				leftDriveEncoder->Reset();
				rightDriveEncoder->Reset();

				cout << "auto 5:1 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

				step++;
				startTime = GetClock();
			break;

			case 2: // Drive backwards to pickup the frisbees
				cout << "auto 5:2-Drive back. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
				shooterPistonSolenoid->Set(false);
				shooterSpeedController->Disable();
				shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
				shooterAngleController->Enable();

				pickupAngleMotor->Set(-1); //lower pickup
				pickupMotor->Set(-0.9);

				//our distance Per Pulse is set in the team316robot.cpp file under robot init function
				if (leftDriveEncoder->GetDistance() <= 14.0) {
					frontLeftDriveMotor->Set(-0.9);
					rearLeftDriveMotor->Set(-0.9);
				} else {
					frontLeftDriveMotor->Set(0.0);
					rearLeftDriveMotor->Set(0.0);
				}//end of left side

				//our distance Per Pulse is set in the team316robot.cpp file under robot init function
				if (rightDriveEncoder->GetDistance() <= 14.0) {
					frontRightDriveMotor->Set(0.9);
					rearRightDriveMotor->Set(0.9);
				} else {
					frontRightDriveMotor->Set(0.0);
					rearRightDriveMotor->Set(0.0);
				}//end of right side

				if ( ((leftDriveEncoder->GetDistance() >= 13.9) && (rightDriveEncoder->GetDistance() >= 13.9))
						|| ((GetClock() - startTime) > 2.0) ){
					step++;
					startTime = GetClock();
				}
				break;

			case 3: // Stop the drive motors and wait
				cout << "auto 5:3 - Pause.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
				pickupMotor->Set(-0.9);
				pickupAngleMotor->Set(0.0); //this is necessary to prevent lockup

				shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
				shooterAngleController->Enable();

				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);

				if ((GetClock() - startTime) > .05) {
					step++;
					startTime = GetClock();
				}
				break;

			case 4: // Drive forwards to the goal
				cout << "auto 5:4 - Drive forward.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
				pickupMotor->Set(-0.9);
				pickupAngleMotor->Set(1.0); //raise arm

				shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
				shooterAngleController->Enable();

				//our distance Per Pulse is set in the team316robot.cpp file under robot init function
				if (leftDriveEncoder->GetDistance() >= -14.0) {
					frontLeftDriveMotor->Set(0.5);
					rearLeftDriveMotor->Set(0.5);
				} else {
					frontLeftDriveMotor->Set(0.0);
					rearLeftDriveMotor->Set(0.0);
				}//end of left side

				//our distance Per Pulse is set in the team316robot.cpp file under robot init function
				if (rightDriveEncoder->GetDistance() >= -14.0) {
					frontRightDriveMotor->Set(-0.5);
					rearRightDriveMotor->Set(-0.5);
				} else {
					frontRightDriveMotor->Set(0.0);
					rearRightDriveMotor->Set(0.0);
				}//end of right side

				if ( ((leftDriveEncoder->GetDistance() <= -13.9) && (rightDriveEncoder->GetDistance() <= -13.9))
						|| ((GetClock() - startTime) > 2.0) ){
					step++;
					startTime = GetClock();
				}
				break;

			case 5: //stop
				cout << "auto 5:5 - STOP. left = "<< (leftDriveEncoder->GetDistance())<<" right = "<< (rightDriveEncoder->GetDistance())<<" time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
				frontLeftDriveMotor->Set(0.0);
				rearLeftDriveMotor->Set(0.0);
				frontRightDriveMotor->Set(0.0);
				rearRightDriveMotor->Set(0.0);

				shooterPistonSolenoid->Set(false);
				shooterSpeedController->Disable();
				shooterAngleController->Disable();
				pickupAngleMotor->Set(0.0);
				pickupMotor->Set(0.0);

				if (GetClock() - startTime > 1.0)
				{
					step++;
					startTime = GetClock();
				}
				break;

		}//end of switch
	}//end of auto 5



		//********************************************************************************
		//
		// AUTONOMOUS MODE 6 - TESTING OF encoder driving with PID to control wheels
		//
		// note that we are not using the get distance function but the raw encoder
		// values so we must compensate for the encoder clicks per distance
		//	being off locally
		//
		//********************************************************************************
			void Team316Robot::AutonomousMode6()
			{
				switch (step) {
				case 1: //reset encoders
					shooterPistonSolenoid->Set(false);
					shooterSpeedController->Disable();
					shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
					shooterAngleController->Enable();
					pickupAngleMotor->Set(-1); //lower pickup
					pickupMotor->Set(0.0);

//					leftFrontDriveSpeedController->Disable();
//					leftRearDriveSpeedController->Disable();
//					rightFrontDriveSpeedController->Disable();
//					rightRearDriveSpeedController->Disable();

					cout << "auto 6:1 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

					leftDriveEncoder->Reset();
					rightDriveEncoder->Reset();

					cout << "auto 6:1 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

					step++;
					startTime = GetClock();
				break;

				case 2: // Drive backwards to pickup the frisbees
					cout << "auto 6:2-Drive back. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
					shooterPistonSolenoid->Set(false);
					shooterSpeedController->Disable();
					shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
					shooterAngleController->Enable();
					pickupAngleMotor->Set(-1); //lower pickup

					pickupMotor->Set(-0.9);

//					leftFrontDriveSpeedController->SetSetpoint(1400);
//					leftRearDriveSpeedController->SetSetpoint(1400);
//					rightFrontDriveSpeedController->SetSetpoint(400);
//					rightRearDriveSpeedController->SetSetpoint(400);

					if ( ((leftDriveEncoder->GetDistance() >= 14.0) && (rightDriveEncoder->GetDistance() >= 14.0))
							|| ((GetClock() - startTime) > 3.0) ){
						step++;
						startTime = GetClock();
					}
					break;

				case 3: // Stop the drive motors and wait
					cout << "auto 6:3 - Pause.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
					pickupMotor->Set(-0.9);

					pickupAngleMotor->Set(0.0); //this is necessary to prevent lockup
					shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
					shooterAngleController->Enable();

//					leftFrontDriveSpeedController->Disable();
//					leftRearDriveSpeedController->Disable();
//					rightFrontDriveSpeedController->Disable();
//					rightRearDriveSpeedController->Disable();

					frontLeftDriveMotor->Set(0.0);
					rearLeftDriveMotor->Set(0.0);
					frontRightDriveMotor->Set(0.0);
					rearRightDriveMotor->Set(0.0);

					leftDriveEncoder->Reset();
					rightDriveEncoder->Reset();

					if ((GetClock() - startTime) > .15) {
						step++;
						startTime = GetClock();
					}
					break;

				case 4: // Drive forwards to the goal
					cout << "auto 6:4 - Drive forward.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
					pickupMotor->Set(-0.9);
					pickupAngleMotor->Set(1.0); //raise arm

					shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
					shooterAngleController->Enable();

//					leftFrontDriveSpeedController->SetSetpoint(-1400);
//					leftRearDriveSpeedController->SetSetpoint(-1400);
//					rightFrontDriveSpeedController->SetSetpoint(-400);
//					rightRearDriveSpeedController->SetSetpoint(-400);

					if ((GetClock() - startTime) > 3.0) {
						step++;
						startTime = GetClock();
					}
					break;

				case 5: //stop
					cout << "auto 6:5 - STOP. left = "<< (leftDriveEncoder->GetDistance())<<" right = "<< (rightDriveEncoder->GetDistance())<<" time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
//					leftFrontDriveSpeedController->Disable();
//					leftRearDriveSpeedController->Disable();
//					rightFrontDriveSpeedController->Disable();
//					rightRearDriveSpeedController->Disable();

					frontLeftDriveMotor->Set(0.0);
					rearLeftDriveMotor->Set(0.0);
					frontRightDriveMotor->Set(0.0);
					rearRightDriveMotor->Set(0.0);

					shooterPistonSolenoid->Set(false);
					shooterSpeedController->Disable();
					shooterAngleController->Disable();
					pickupAngleMotor->Set(0.0);
					pickupMotor->Set(0.0);

					if (GetClock() - startTime > 1.0)
					{
						step++;
						startTime = GetClock();
					}
					break;

			}//end of switch
		}//end of auto 6




