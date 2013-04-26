/******************************************************************************
 * AutonomousMode1.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * In this mode, we shoot our 3 starting frisbees then stop.
 *
 ******************************************************************************/

#include "../Team316Robot.h"
#include "Autonomous.h"

void Team316Robot::AutonomousMode1()
{
	cout << "[Mode:1][Step:" << step <<"][Time:"<< (GetClock() - startTime)<< "][TotTime:" << (GetClock() - beginTime) << "] - ";
    switch (step)
    {
        case 1: // Turn the motor on and wait till we're up to speed
            cout << "Setup - shooterSpeed: " << (shooterSpeedCounter->GetRPM()) << endl;

            // Enable the shooter motor
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();

            // Set the shooter to the proper angle
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Make sure the firing piston is retracted
            shooterPistonSolenoid->Set(false);
            
            // during testing this only achieves about 3600 rpm by 2.5 seconds
            if ( (shooterSpeedCounter->PIDGet() > 3800) || ((STEP_TIME) > 3) )
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 2:
            // Fire the first shot
            cout << "Fire the first shot" << endl;

            // Update the values for the shooter motor and angle
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);
            
            if ((STEP_TIME) > 0.2)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 3: // Wait for the motor to come back up to speed
            cout << "Preparing for second shot - shooterSpeed: " << (shooterSpeedCounter->GetRPM()) << endl;

            // Update the values for the shooter motor and angle
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // retract the firing piston
            shooterPistonSolenoid->Set(false);
            
            // we lose approximately 500rpm in the shot - it takes approx 500ms to recover that
            if ((shooterSpeedCounter->PIDGet() > 3800 && STEP_TIME > 1.0) || STEP_TIME > 2.0)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 4: // Fire the second shot
            cout << "Fire the second shot" << endl;

            // Update the values for the shooter motor and angle
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // fire the next shot
            shooterPistonSolenoid->Set(true);           
            
            if ((STEP_TIME) > 0.2)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 5: // Wait for the motor to come back up to speed
            cout << "Prepparing for third shot - shooterSpeed: " << endl;

            // Update the values for the shooter motor and angle
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Retract the firing piston
            shooterPistonSolenoid->Set(false);
            
            if ((shooterSpeedCounter->PIDGet() > 3800 && STEP_TIME > 1.0) || STEP_TIME > 2.0)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 6: // Fire the third shot
            cout << "Fire the third shot" << endl;

            // Update the values for the shooter motor and angle
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);
            
            if (STEP_TIME > 0.2)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 7: // Turn off motor and retract piston
            cout << "Turn off motor and retract piston" << endl;

            // Halt robot output
            shooterPistonSolenoid->Set(false);
            shooterSpeedController->Disable();
            shooterAngleController->Disable();

            // Advance to the next step
            step++;
            break;

        case 8: // Done
            cout << "Autonomous Mode Finished" << endl;
            break;

        default:    // Should never be reached. Halt all robot output for safety
            cout << "Error: Default case" << endl;
            break;
    }
}
