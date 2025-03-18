#include "vex.h"
using namespace vex;

brain Brain;
controller con; 
//declares the controller and brain
motor right1 = motor(PORT18, ratio6_1, false);// front
motor right2 = motor(PORT19, ratio6_1, false);//middle
motor right3 = motor(PORT20, ratio6_1, true);//back
//declares ports, cartidges, and directions for right drive motors
motor left1 = motor(PORT17, ratio6_1, false);//front
motor left2 = motor(PORT16,  ratio6_1, true);//middle 
motor left3 = motor(PORT15,  ratio6_1, true);//back
//declares ports, cartidges, and directions for left drive motors
motor lb = motor(PORT14, false);
motor upperIntake = motor(PORT6, true);
//declares port and direction for lift motor
motor lowerIntake = motor(PORT10, false);//
//declares port and direction for intake
motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
//declares the motors in each motor group
inertial Inertial = inertial(PORT7);
//declares the inertial sensors' ports
optical Optical = optical(PORT12);
optical TheOpps = optical(PORT21);
rotation Rotation = rotation(PORT13);
vex::motor_group intake_Group = motor_group(lowerIntake, upperIntake);
vex::motor_group leftDrive_Group = motor_group(left1, left2, left3);
vex::motor_group rightDrive_Group = motor_group(right1, right2, right3);
drivetrainObj Drive (3.25, .75);
//declares the parameters for the Drive object which are the wheel diameter and the gear ratio
pneumatics clamp = pneumatics(Brain.ThreeWirePort.F);
pneumatics bonk = pneumatics(Brain.ThreeWirePort.H);
pneumatics intakeLift = pneumatics(Brain.ThreeWirePort.G);
/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void) {
 // Nothing to initialize
}
