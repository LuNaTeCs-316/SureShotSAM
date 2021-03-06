/*******************************************************************************
 * RobotMap.cpp - Maps robot sensors/actuators to ports
 *
 * Copyright (c) 2013 FIRST Team 316, LuNaTeCs. All rights reserved.
 *
 * Code for our 2013 Robot, Sure Shot SAM
 * for the FRC game Ultimate Ascent 
 *
 ******************************************************************************/

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

//
// PWM Outputs
//
#define FRONT_LEFT_DRIVE_MOTOR	1
#define FRONT_RIGHT_DRIVE_MOTOR	3
#define REAR_LEFT_DRIVE_MOTOR	2
#define REAR_RIGHT_DRIVE_MOTOR	4

#define PICKUP_ANGLE_MOTOR		5
#define SHOOTER_MOTOR			6
#define SHOOTER_ANGLE_MOTOR		7

//
// Relay Outputs
//
#define COMPRESSOR_RELAY	1
#define PICKUP_BELT_RELAY	2

//
// Solenoid Outputs
//
#define SHOOTER_PISTON_SOLENOID		1
#define CLIMBING_SOLENOID			2
#define SHOOTER_POSITION_SOL_SHOOT	3
#define SHOOTER_POSITION_SOL_LOAD	4

//
// Analog Inputs
//
#define PICKUP_ANGLE_POT	1
#define SHOOTER_ANGLE_POT	2

//
// Digital inputs
//
#define RIGHT_DRIVE_ENCODER_A		1
#define RIGHT_DRIVE_ENCODER_B		2
#define LEFT_DRIVE_ENCODER_A		3
#define LEFT_DRIVE_ENCODER_B		4
#define SHOOTER_SPEED_COUNTER		5
#define COMPRESSOR_PRESSURE_SWITCH	14

#endif
