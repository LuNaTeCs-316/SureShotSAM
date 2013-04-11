/******************************************************************************
 * AutonomousMode2.cpp - Autonomous sub-routine
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent
 *
 * Shoot 3, pickup & fire frisbees from center line using encoders and PID loops
 *
 ******************************************************************************/

#include "../Team316Robot.h"
#include "Autonomous.h"



void Team316Robot::AutonomousMode2()
{
    if (step< 20) cout << "[Mode:2][Step:" << step <<"][Step Time:" << STEP_TIME
            << "ms][ElapsedTime:" << GetClock() - beginTime << "ms] ";
    switch (step)
    {
    	case 1: // Turn the motor on and wait till we're up to speed
            cout << "shooter speed = " << (shooterSpeedCounter->GetRPM() )<<endl;

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
            cout << "Fire the first shot"<< endl;
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
            cout << "shooter speed = " << (shooterSpeedCounter->GetRPM() )<< endl;
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
            cout << "Fire the second shot"<< endl;
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
            cout << "shooter speed = " << (shooterSpeedCounter->GetRPM() )<< endl;
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
            cout << "Fire the third shot"<< endl;
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
            shooterPistonSolenoid->Set(false);
            shooterSpeedController->Disable();
            if ((GetClock() - startTime) > 0.05) {
                step++;
                startTime = GetClock();
            }
            break;

/*******************************************************************************************************************
 * firing of 3 shots is complete
 ********************************************************************************************************************/            
            
        case 8: 
        	// it takes exactly 4 second to lower the shooter from shooting position to loading position with old screw
        	// it takes exactly 1.2 second to lower the shooter from shooting position to loading position with new screw
        	cout << "shooter angle = " << (shooterAnglePot->GetAverageVoltage()) <<endl;
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
            cout << "shooter angle = " << (shooterAnglePot->GetAverageVoltage())<<endl;
            shooterPistonSolenoid->Set(false);
            shooterSpeedController->Disable();
            shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
            shooterAngleController->Enable();

            pickupAngleMotor->Set(-1.0);
//TODO
            if ( (GetClock() - startTime > 1.0)  //this time constant is critical and depends on shooter height
                || ( shooterAnglePot->GetAverageVoltage() <= (SHOOTER_LOWEST_HEIGHT + .05) ) ) {
                step++;
                startTime = GetClock();
            }
            break;

        case 10: //here we are making sure the encoders are reset before we use them
            leftDriveEncoder->Reset();
            rightDriveEncoder->Reset();
            step++;
            startTime = GetClock();
        break;

        case 11: // Drive backwards to pickup the frisbees using encoders
            cout << "Drive back. left= "<< (leftDriveEncoder->Get())<<" right= "<< (rightDriveEncoder->Get())<<endl;

            pickupAngleMotor->Set(-1.0);
            pickupMotor->Set(-0.9);

 //NEW
        	leftFDriveController->SetSetpoint(600); //this is in encoder ticks
        	leftRDriveController->SetSetpoint(600);
        	rightFDriveController->SetSetpoint(800);
        	rightRDriveController->SetSetpoint(800);

        	leftFDriveController->Enable(); //this is in encoder ticks
        	leftRDriveController->Enable();
        	rightFDriveController->Enable();
        	rightRDriveController->Enable();
        	
            if ( (GetClock() - startTime) > 2.0 ){
                step++;
                startTime = GetClock();
            }
            break;

        case 12: // Stop the drive motors and wait
            pickupMotor->Set(-0.9);
            pickupAngleMotor->Set(0.0); //this is necessary to prevent lockup
            
        	leftFDriveController->Disable(); //this is in encoder ticks
        	leftRDriveController->Disable();
        	rightFDriveController->Disable();
        	rightRDriveController->Disable();
            
            if ((GetClock() - startTime) > .05) {
                step++;
                startTime = GetClock();
            }
            break;

        case 13: //reset encoders - this is probably unnnecessary
            step++;
            startTime = GetClock();
        break;

        case 14: // Drive forwards to the goal
          	// it takes exactly 1.2 second to raise the shooter from shooting position to loading position with new screw
            cout << "Drive forward.  left= "<< (leftDriveEncoder->GetDistance())<<" right= "<< (rightDriveEncoder->GetDistance())<<endl;

            pickupMotor->Set(-0.9);
            pickupAngleMotor->Set(.8); //raise arm
                    
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            
            shooterSpeedController->SetSetpoint(3800);
            shooterSpeedController->Enable();

	//NEW
			leftFDriveController->SetSetpoint(20); //this is in encoder ticks
			leftRDriveController->SetSetpoint(20);
			rightFDriveController->SetSetpoint(20);
			rightRDriveController->SetSetpoint(20);

			leftFDriveController->Enable(); //this is in encoder ticks
			leftRDriveController->Enable();
			rightFDriveController->Enable();
			rightRDriveController->Enable();
			
            
            
            if ( (GetClock() - startTime) > 2.0 ){
                step++;
                startTime = GetClock();
            }
            break;
            
        case 15: // Stop the drive motors and wait till we're in position to fire
            cout << "shooter angle = " << shooterAnglePot->GetAverageVoltage() <<endl;

            pickupMotor->Set(-0.9);
            pickupAngleMotor->Set(1.0);

        	leftFDriveController->Disable(); //this is in encoder ticks
        	leftRDriveController->Disable();
        	rightFDriveController->Disable();
        	rightRDriveController->Disable();
            
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();

            shooterSpeedController->SetSetpoint(3800);
            shooterSpeedController->Enable();
            
                if (shooterAnglePot->GetAverageVoltage() >= (SHOOTER_TOP_HEIGHT - .05)
                    || (GetClock() - startTime) > 1.2){
                step++;
                startTime = GetClock();
            }
            
            break;

        case 16: // Fire the 4th shot
//        	cout << "Fire the 4th shot"<< endl;
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
//          cout << "shooter speed = " << (shooterSpeedCounter->GetRPM() )<< endl;

            pickupMotor->Set(0.0);
            pickupAngleMotor->Set(0.0);

            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            shooterPistonSolenoid->Set(false);
            
            if ( (shooterSpeedCounter->PIDGet() > 3800)
                || ((GetClock() - startTime) > 0.5) ) {
                step++;
                startTime = GetClock();
            }
            break;

        case 18: // Fire the 5th shot
//          cout << "Fire the 5th shot" << endl;
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
//          cout << "cleanup" << endl;
            pickupMotor->Set(0.0);
            pickupAngleMotor->Set(0.0);
            shooterAngleController->Disable();
            shooterPistonSolenoid->Set(false);
            shooterSpeedController->Disable();
            step++;
            startTime = GetClock();
            break;

        case 20: //this is here to prevent netconsole stack from overflowing
            break;

        default:
//            cout << "auto 3:default  Error.  You should not be here" << endl;
            break;
    }
}//end of function







/******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
 * old dead reckoning code - not used any more
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
******************************************************************************
 ******************************************************************************/
/*
void Team316Robot::AutonomousMode2()
{
    cout << "[Mode:2][Step:" << step <<"][SysTime:" << GetClock()
            << "ms][ElapsedTime:" << STEP_TIME << "ms] ";
    switch (step)
    {
        case 1: // Turn the motor on and wait till we're up to speed
            cout << "Setup - shooterSpeed: " << (shooterSpeedCounter->GetRPM()) << endl;

            // Enable the shooter motor and angle controllers
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();
            
            // during testing this only achieves about 3600 rpm by 2.5 seconds
            if ((shooterSpeedCounter->PIDGet() > 3800) || ((GetClock() - startTime) > 2.5))
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 2: // Fire the first shot
            cout << "Fire the first shot" << endl;
            
            // Update the shooter outputs
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 3: // Wait for the motor to come back up to speed
            cout << "Preparing for second shot - shooterSpeed: " << endl;

            // Update the shooter outputs
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Retract the firing piston
            shooterPistonSolenoid->Set(false);

            // We lose approximately 500rpm in the shot - it takes approx 500ms to recover that
            if ((shooterSpeedCounter->PIDGet() > 3800) || ((GetClock() - startTime) > 1.5) )
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 4: // Fire the second shot
            cout << "Fire the second shot" << endl;
            
             // Update the shooter outputs
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);           
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 5: // Wait for the motor to come back up to speed
            cout << "Preparing for third shot - shooterSpeed: " << endl;
            
            // Update the shooter outputs
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Retract the firing piston
            shooterPistonSolenoid->Set(false);
            
            if ((shooterSpeedCounter->PIDGet() > 3800) || ((GetClock() - startTime) > 1.5) )
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 6: // Fire the third shot
            cout << "Fire the third shot" << endl;
            
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 7: // pause so we do not disrupt the frisbee exiting the shooter
            cout << "Brief pause to avoid disrupting the shot" << endl;
            
            // Retract the firing piston
            shooterPistonSolenoid->Set(false);

            // Turn off the shooter motor
            shooterSpeedController->Disable();
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 8: // it takes exactly 4 second to lower the shooter from
                // shooting position to loading position
            cout << "shooterAngle: " << (shooterAnglePot->GetAverageVoltage()) << endl;
            
            // Set the shooter to the pickup position
            shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
            shooterAngleController->Enable();

            if (GetClock() - startTime > .5)
            {
                step++;
                startTime = GetClock();
            }
            break;
            
        case 9: // here we are still continuing to lower the shooter
                // but now that it is out of the way we can also lower the pickup arm
            cout << "shooterAngle = " << (shooterAnglePot->GetAverageVoltage()) << endl;

            // Start lowering the pickup
            pickupAngleMotor->Set(-1.0);

            if ((GetClock() - startTime > 2.5) ||
                (shooterAnglePot->GetAverageVoltage() <= (SHOOTER_LOWEST_HEIGHT + .05)))
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 10: // Drive backwards to pickup the frisbees - using dead reckoning and timing to know when to stop
            cout << "Drive back - shooterAngle: " << (shooterAnglePot->GetAverageVoltage()) << endl;
            
            // Activate the pickup belts
            pickupMotor->Set(-0.9);

            // Continue lowering the pickup
            pickupAngleMotor->Set(-1.0);

            // Continue to lower the shooter
            shooterAngleController->SetSetpoint(SHOOTER_LOWEST_HEIGHT);
            shooterAngleController->Enable();

            // Start to drive backwards at 50% power
            frontLeftDriveMotor->Set(-0.5);
            rearLeftDriveMotor->Set(-0.5);
            frontRightDriveMotor->Set(0.5);
            rearRightDriveMotor->Set(0.5);
            
            if ((GetClock() - startTime) > 2.0)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 11: // Stop the drive motors and wait for a moment
            cout << "Pause and pickup" << endl;
            
            // Continue running the pickup belts
            pickupMotor->Set(-0.9);

            // Stop lowering the pickup
            pickupAngleMotor->Set(0.0); // we have to do this so that code does not lock (?)
            
            // Start moving the shooter back to the firing position
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            
            // Stop the drive motors
            frontLeftDriveMotor->Set(0.0);
            rearLeftDriveMotor->Set(0.0);
            frontRightDriveMotor->Set(0.0);
            rearRightDriveMotor->Set(0.0);
            
            if ((GetClock() - startTime) > .15)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 12: // Drive forwards to the goal
            cout << "Drive forward" << endl;
        
            // Continue running the pickup belts
            pickupMotor->Set(-0.9);

            // Start to raise the pickup system
            pickupAngleMotor->Set(1.0);
            
            // Continue moving the shooter to the firing position
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            
            // Start to drive forwards towards the goal
            frontLeftDriveMotor->Set(0.37); // it appears that the left drive is a little weaker in testing
            rearLeftDriveMotor->Set(0.37);
            frontRightDriveMotor->Set(-0.30);
            rearRightDriveMotor->Set(-0.30);
            
            if ((GetClock() - startTime) > 2.4) // this allows the bot to coast into the stops
            { 
                step++;
                startTime = GetClock();
            }
            break;
            
        case 13: // Stop the drive motors and wait till we're in position to fire
            cout << "shooterAngle: " << (shooterAnglePot->GetAverageVoltage()) << endl;

            // Continue running the pickup belts
            pickupMotor->Set(-0.9);

            // Continue to raise the pickup
            pickupAngleMotor->Set(1.0);

            // Stop the drive motors
            frontLeftDriveMotor->Set(0.0);
            rearLeftDriveMotor->Set(0.0);
            frontRightDriveMotor->Set(0.0);
            rearRightDriveMotor->Set(0.0);
            
            // Continue moving the shooter to the firing position
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();

            // TEST: not sure if we should go with 4500 here to save time later
            // on recoup but might be too strong?
            shooterSpeedController->SetSetpoint(3800);
            shooterSpeedController->Enable();
            
            // TEST: this should actually take about 2.7 seconds or so
            if (shooterAnglePot->GetAverageVoltage() >= (SHOOTER_TOP_HEIGHT - .05) || (GetClock() - startTime) > 3.2)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 14: // Fire the 4th shot
            cout << "Fire the 4th shot - shooterSpeed: " << (shooterSpeedCounter->GetRPM()) << endl;
            
            // Disable the pickup belts
            pickupMotor->Set(0.0);

            // Continue to raise the pickup
            pickupAngleMotor->Set(1.0);

            // Continue to raise the shooter to the target position
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();

            // Run the shooter motor
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the frisbee
            shooterPistonSolenoid->Set(true);
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 15: // Wait for the motor to come back up to speed
            cout << "shooterSpeed: " << (shooterSpeedCounter->GetRPM()) << endl;

            // Why is this here? Driving the pickup up until it hits the limit/breaks itself!?
            pickupAngleMotor->Set(1.0);

            // Redundant code is redundant; set values for angle and speed of the shooter yet again
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            shooterPistonSolenoid->Set(false);
            
            // TEST: we are almost out of time here so just throwing them up
            // - in all likelyhood we only have 1 frisbee
            if ((shooterSpeedCounter->PIDGet() > 3800) || ((GetClock() - startTime) > 1.5))
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 16: // Fire the 5th shot
            cout << "Fire the 5th shot" << endl;
            pickupAngleMotor->Set(1.0);

            // Redundant code is still redundant; set values for angle and
            // speed of shooters one last time... just to be sure :/
            shooterAngleController->SetSetpoint(SHOOTER_TOP_HEIGHT);
            shooterAngleController->Enable();
            shooterSpeedController->SetSetpoint(4500);
            shooterSpeedController->Enable();

            // Fire the last shot
            shooterPistonSolenoid->Set(true);           
            
            if ((GetClock() - startTime) > 0.05)
            {
                step++;
                startTime = GetClock();
            }
            break;

        case 17: // Cleanup
            cout << "Cleanup\n";
            
            pickupAngleMotor->Set(0.0);
            
            shooterAngleController->Disable();
            shooterSpeedController->Disable();
            shooterPistonSolenoid->Set(false);

            step++;
            startTime = GetClock();
            break;

        case 18:
            cout << "Done\n";
            break;

        default: // Should never be reached
            cout << "Error: default case" << endl;
            break;
    }
}
*/
