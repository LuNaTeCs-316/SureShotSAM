/******************************************************************************
 * AutonomousMode6.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * TEST - experimentation with encoders and PIDs
 *
 ******************************************************************************/

#include "../Team316Robot.h"
#include "Autonomous.h"

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

            //leftFrontDriveSpeedController->Disable();
            //leftRearDriveSpeedController->Disable();
            //rightFrontDriveSpeedController->Disable();
            //rightRearDriveSpeedController->Disable();

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

            //leftFrontDriveSpeedController->SetSetpoint(1400);
            //leftRearDriveSpeedController->SetSetpoint(1400);
            //rightFrontDriveSpeedController->SetSetpoint(400);
            //rightRearDriveSpeedController->SetSetpoint(400);

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

            //leftFrontDriveSpeedController->Disable();
            //leftRearDriveSpeedController->Disable();
            //rightFrontDriveSpeedController->Disable();
            //rightRearDriveSpeedController->Disable();

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

            //leftFrontDriveSpeedController->SetSetpoint(-1400);
            //leftRearDriveSpeedController->SetSetpoint(-1400);
            //rightFrontDriveSpeedController->SetSetpoint(-400);
            //rightRearDriveSpeedController->SetSetpoint(-400);

            if ((GetClock() - startTime) > 3.0) {
                step++;
                startTime = GetClock();
            }
            break;

        case 5: //stop
            cout << "auto 6:5 - STOP. left = "<< (leftDriveEncoder->GetDistance())<<" right = "<< (rightDriveEncoder->GetDistance())<<" time = "<< (GetClock() - startTime)<< "Tot Time: " << (GetClock() - beginTime) <<endl;
            //leftFrontDriveSpeedController->Disable();
            //leftRearDriveSpeedController->Disable();
            //rightFrontDriveSpeedController->Disable();
            //rightRearDriveSpeedController->Disable();

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
