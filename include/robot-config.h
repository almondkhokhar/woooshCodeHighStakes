#ifndef ROBOTCONFIG_H
#define ROBOTCONFIG_H
#include "vex.h"
using namespace vex;

void vexcodeInit(void);

extern vex::pneumatics clamp;
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
extern vex::motor intake;
// declares intake motor
extern vex::motor lift;
//declares lift motor
extern vex::motor_group leftdrive;
extern vex::motor_group rightdrive;
//declares drivetrain motor groups
extern vex::inertial Inertial;
extern vex::inertial Inert2;
//declares inertial sensors, we have 2 so if one disconnects or has an error we can override it's input and use the second inertial sensor instead
extern drivetrainObj Drive;
//declares the drivetrain as an object
#endif