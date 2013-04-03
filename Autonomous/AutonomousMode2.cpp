/******************************************************************************
 * AutonomousMode2.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * Shoot 3, pickup & fire frisbees from center line - Dead reckoning
 *
 ******************************************************************************/

#include "Team316Robot.h"
#include "Autonomous.h"

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
}