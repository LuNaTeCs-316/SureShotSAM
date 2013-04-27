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

#include "../Team316Robot.h"
#include "Autonomous.h"

void Team316Robot::AutonomousMode4()
{

    shooterPistonSolenoid->Set(false);
    shooterSpeedController->Disable();

    cout << "[Mode:4][Step:" << step <<"][SysTime:" << GetClock()
            << "ms][ElapsedTime:" << STEP_TIME << "ms] ";

    switch (step)
    {
        case 1: // this mode proved out that it takes exactly 4 second to lower the shooter
        		//with theold screw
        		//with new screw it was 1.2 seconds
            cout << "lower shooter: actual = " << (shooterAnglePot->GetAverageVoltage()) << endl;
            
            shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
            shooterAngleController->Enable();
            
            if (GetClock() - startTime > 4.0)
            {
                step++;
                startTime = GetClock();
            }
            break;

            //SHOOTER_LOAD_HEIGHT
        case 2: // this mode proved that it takes exactly > 5 second to raise the shooter
            cout << "raise shooter: actual = " << (shooterAnglePot->GetAverageVoltage()) << endl;
            
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            
            if (GetClock() - startTime > 7.0)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 3:
            cout << "STOP" << endl;
            
            shooterAngleController->Disable();
            
            if (GetClock() - startTime > 2.5)
            {
                step++;
                startTime = GetClock();
            }
            break;
    }
}
