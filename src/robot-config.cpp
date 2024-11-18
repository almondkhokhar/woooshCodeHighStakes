#include "vex.h"
using namespace vex;

brain Brain;
controller con;
//declares the controller and brain
motor right1 = motor(PORT1, ratio6_1, false);
motor right2 = motor(PORT3, ratio6_1, false);
motor right3 = motor(PORT9, ratio6_1, false);
//declares ports, cartidges, and directions for right drive motors
motor left1 = motor(PORT12, ratio6_1, true);
motor left2 = motor(PORT13,  ratio6_1, true);
motor left3 = motor(PORT17,  ratio6_1, true);
//declares ports, cartidges, and directions for left drive motors
motor lift = motor(PORT5, false);
motor lift2 = motor(PORT14, true);
//declares port and direction for lift motor
motor intake = motor(PORT2, false);
//declares port and direction for intake
motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
//declares the motors in each motor group
inertial Inertial = inertial(PORT11);
//declares the inertial sensors' ports
optical Optical = optical(PORT21);
rotation Rotation = rotation(PORT4);
vex::motor_group leftDrive_Group = motor_group(left1, left2, left3);
vex::motor_group rightDrive_Group = motor_group(right1, right2, right3);
drivetrainObj Drive (3.25, .75);
//declares the parameters for the Drive object which are the wheel diameter and the gear ratio
pneumatics clamp = pneumatics(Brain.ThreeWirePort.A);
pneumatics bonk = pneumatics(Brain.ThreeWirePort.E);
pneumatics intakeLift = pneumatics(Brain.ThreeWirePort.G);
limit lSwitch = limit(Brain.ThreeWirePort.H);
/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void) {
 // Nothing to initialize
}