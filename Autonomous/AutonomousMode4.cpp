/******************************************************************************
 * AutonomousMode4.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * TEST - timing of raising and lowering shooter
 *
 ******************************************************************************/

#include "Team316Robot.h"
#include "Autonomous.h"

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

    }
}
