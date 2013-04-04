/******************************************************************************
 * AutonomousMode3.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * Shoot 3, pickup & fire frisbees from center line - Encoders
 *
 ******************************************************************************/

#include "../Team316Robot.h"
#include "Autonomous.h"

void Team316Robot::AutonomousMode3()
{
    switch (step)
    {
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
//          cout << "auto 3:7 - Pause so we do not disrupt the exiting frisbee.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
            shooterPistonSolenoid->Set(false);
            shooterSpeedController->Disable();
            if ((GetClock() - startTime) > 0.05) {
                step++;
                startTime = GetClock();
            }
            break;

        case 8: // it takes exactly 4 second to lower the shooter from shooting position to loading position
//          cout << "auto 3:8 - shooter angle = " << (shooterAnglePot->GetAverageVoltage()) << ".  time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
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
//          cout << "auto 3:10 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

            leftDriveEncoder->Reset();
            rightDriveEncoder->Reset();

//          cout << "auto 3:10 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

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
//          cout << "auto 3:12 - Pause.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;
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
//          cout << "auto 3:13 before reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

            leftDriveEncoder->Reset();
            rightDriveEncoder->Reset();

//          cout << "auto 5:1 after reset. left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<" time= "<< (GetClock() - startTime)<< "Tot Time= " << (GetClock() - beginTime) <<endl;

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
//          cout << "auto 3:16 - Fire the 4th shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
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
//          cout << "auto 3:17 - shooter speed = " << (shooterSpeedCounter->GetRPM() )<<" Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
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
//          cout << "auto 3:18 - Fire the 5th shot.  Time: " << (GetClock() - startTime) << "Tot Time: " << (GetClock() - beginTime) << endl;
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
//          cout << "auto 3:19 - cleanup" << "Tot Time: " << (GetClock() - beginTime) << endl;
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
}
