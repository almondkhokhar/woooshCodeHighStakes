#ifndef ROBOTCONFIG_H
#define ROBOTCONFIG_H
#include "vex.h"
using namespace vex;

void vexcodeInit(void);

extern vex::pneumatics clamp;
extern vex::pneumatics bonk;
extern vex::pneumatics intakeLift;
extern vex::brain Brain;
extern vex::controller con;
extern vex::motor left1;
extern vex::motor left2;
extern vex::motor left3;
//declares left drive motors
extern vex::motor right1;
extern vex::motor right2;
extern vex::motor right3;
//declares right drive motors
// declares intake motor
extern vex::motor lb;
extern vex::motor lowerIntake;
extern vex::motor upperIntake;
//declares lift motor
extern vex::motor_group leftdrive;
extern vex::motor_group rightdrive;
extern vex::motor_group intake;
//declares drivetrain motor groups
extern vex::inertial Inertial;
extern vex::limit lSwitch;
//declares inertial sensors, we have 2 so if one disconnects or has an error we can override it's input and use the second inertial sensor instead
extern vex::optical Optical;
extern vex::optical TheOpps;
extern vex::rotation Rotation;
extern vex::motor_group intake_Group;
extern vex::motor_group leftDrive_Group;
extern vex::motor_group rightDrive_Group;
extern drivetrainObj Drive;
//declares the drivetrain as an object
#endif