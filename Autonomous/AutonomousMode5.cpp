/******************************************************************************
 * AutonomousMode5.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * TEST - experimentation with encoders
 *
 ******************************************************************************/

#include "../Team316Robot.h"
#include "Autonomous.h"
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

}
    }
