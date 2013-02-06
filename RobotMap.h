//
// RobotMap.h
//
// Maps robot sensors/actuators to ports
//

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

//
// PWM Outputs
//
#define LEFT_DRIVE_MOTOR	1
#define RIGHT_DRIVE_MOTOR	2
#define PICKUP_ANGLE_MOTOR	3
#define SHOOTER_MOTOR		4
#define SHOOTER_ANGLE_MOTOR	5

//
// Relay Outputs
//
#define COMPRESSOR_RELAY	1
#define PICKUP_BELT_RELAY	2

//
// Solenoid Outputs
//
#define SHOOTER_PISTON_SOLENOID	1

//
// Analog Inputs
//
#define PICKUP_ANGLE_POT	1
#define SHOOTER_ANGLE_POT	2

//
// Digital inputs
//
#define LEFT_DRIVE_ENCODER_A		1
#define LEFT_DRIVE_ENCODER_B		2
#define RIGHT_DRIVE_ENCODER_A		3
#define RIGHT_DRIVE_ENCODER_B		4
#define SHOOTER_SPEED_COUNTER		5
#define COMPRESSOR_PRESSURE_SWITCH	14

#endif
