/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Arjomand Khokhar                                          */
/*    Created:      9/7/2024, 7:27:23 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// make class called apple and make apple.myapple can place properties about all of the apples, like ripeness, color, myapple.ripeness()=5 days, myapple2.ripeness()= 7 days, motor is a class for vex motors with properties such as spin, temperature, so you can make a class drivetrain with inputs of drivegroups left and right and then make a drivestraight function inside the drive class, odom applications: take wheel diameter input so when you had a previous wheel diameter for your robot you can change that parameter when you rebuild and all of your code still works. 
// error is loss function, how far away are we from where we want to be. P value is just some number multiplied by your error and does most of the work to get you where you want to be. if p is to small your motor input will be to low to do anything and you won't reach the point you want to. if p is too high then you will reach the point you want to, but then you will overshoot it because you are going to fast so it will oscillate a lot. so you can try to get the P value very exact but its difficult and take a long time to tune, so what you can do is have it a little higher and then subtract your velocity. speed = error times kp - derivative of error times kd. what that does is calculate velocity and if we are moving faster move slower so we don't over shoot our target. dampening works by allowing us to not have to be super exact with our kp and dampen it's affect as we get closer to the target. when we are close to where we want to be but not eactly there the p value is basically 0 and the d value is basically 0 so you will be very close, but never exactly where you want to be. The I value which stands for integral is just the theoretical area under the graph of position vs time, telling you how long you've been that far away from your target. Derivative is current error and prev error starts at current error but after the first loop it becomes your current error, then current error updates, then you calculate your speed, and then your previous error. the way you track your integral is you take your error sum starting at 0 and every loop you just add your error to it, errorsum += error. so speed = error * kP + errorsum * kI - deriv of error * kD, then tune it until you have each value affecting the program how you want, not just one individual part of it. no analytical way to find kp ki and kd so you have to take educated guesses and test your program until you have a program that functions how you want it to 
#include "vex.h"

class Drive
{
public:
  double wheelRatio;
  double gearRatio;
  double kp;
  double kd;
  double initialAngle;
  double finalAngle;
  double totalError;
  double currentError;
  double finalDistance;
  double currentDistance;
  double turningDistance;
  double turnTimeout;
  double totalTimeout;
  double firstDriveTimeout;
  double secondDriveTimeout;
};
bool conToggle1 = true;
bool conToggle2 = true;
bool conToggle3 = true;
bool conToggle4 = true;
bool intakeToggle = false;
bool rwingtoggle = false;
bool lwingtoggle = false;
bool rbwingtoggle = false;
bool lbwingtoggle = false;
bool Shoottogg = false;
bool punchythingToggle = false;
bool dropdowntoggle = false;
bool hangToggle = false;
bool f1loop = true;
bool f2loop = true;
bool f3loop = true;
bool f4loop = true;
bool f5loop = true;
bool f6loop = true;
bool f7loop = true;
int counter = 0;


int autoSelect = 0;


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int armup(){
  lift.spin(fwd, 100, pct);
  wait(.2, sec);
  lift.spin(fwd,-100,pct);
  wait(.1, sec);
  lift.stop(hold);
  return(0);
}
int armdown(){
  lift.spin(fwd, -100, pct);
  wait(.15, sec);
  lift.spin(fwd,100,pct);
  wait(.1, sec);
  lift.stop(hold);
  return(0);
}
void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void AWPRight(){
  armup();
  clamp.open();
  Drive.swing(-25, 100, -60, 1);
  Drive.moveDistance(-5, 100, .5);
  clamp.close();
  Drive.turn(-90, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(28, 20, 2);
  Drive.moveDistance(-15, 100, .7);
  Drive.turn(-180, 100, .7);
  Drive.moveDistance(16, 70, .9);
  Drive.moveDistance(-15, 100, .8);
  Drive.turn(-155, 100, .5);
  Drive.moveDistance(17, 100, .8);
  Drive.moveDistance(-18, 100, 1);
  Drive.turn(-270, 100, .8);
  Drive.moveDistance(30, 70, 1.2);
  // Drive.moveDistance(-43, 100, 1.2);
  // Drive.turn(-45, 100, .7);
  // Drive.moveDistance(10, 70, .8);

}
void AWPLeft(){
  armup();
  Drive.swing(-14.5, 100, 90, .9);
  intake.spin(fwd,100,pct);
  wait(.8,sec);
  Drive.turn(150, 100,.7);
  Drive.swing(20,100,35,1);
  Drive.swing(40,100,-90, 1.1);
  intake.stop();
  clamp.open();
  Drive.moveDistance(-10, 70, .8);
  clamp.close();
  intake.spin(fwd,100,pct);
  Drive.turn(0,100,.8);
  Drive.moveDistance(25,70, 1.2);


}
void testing(){
  Drive.turn(45,100, 2);
}
void (*autonsList[])() =
{
  // testing,
  AWPRight,
  AWPLeft,
  

};

void autonomous()
{
  autonsList[autoSelect]();
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int conInfo()
{
  while (true)
  {
    con.Screen.clearScreen();
    con.Screen.setCursor(1, 1);
    con.Screen.print("Battery:");
    con.Screen.print(Brain.Battery.capacity(percent));
    con.Screen.setCursor(2, 1);
    con.Screen.print("Left  ");
    con.Screen.print((left1.temperature(fahrenheit) + left2.temperature(fahrenheit) + left3.temperature(fahrenheit)) / 3);
    con.Screen.setCursor(3, 1);
    con.Screen.print("Right  ");
    con.Screen.print((right1.temperature(fahrenheit) + right2.temperature(fahrenheit) + right3.temperature(fahrenheit)) / 3);
    wait(1, sec);
  }
  return (0);
}
void usercontrol()
{
  task printcon = task(conInfo);
  while (true)
  {
    // controls the speed at which the robot moves
    // moving controls
    rightdrive.spin(fwd, con.Axis2.value(), pct);
    leftdrive.spin(fwd, con.Axis3.value(), pct);
    // intake controls
    if (con.ButtonR2.pressing())
    {
      intake.spin(fwd, -100, pct);
    }
    else if (con.ButtonR1.pressing())
    {
      intake.spin(fwd, 100, pct);
    }
    else
    {
      intake.stop(hold);
    }


    //lift controls
    if (con.ButtonL1.pressing())
    {
      lift.spin(fwd,100,pct);
      f1loop = false;
    }
    else if (!f1loop)
    {
      lift.stop(hold);
    }
    if (con.ButtonL2.pressing())
    {
      lift.spin(fwd, -100, pct);
      f1loop = true;
    }
    else if (!con.ButtonL1.pressing()){
      lift.stop(hold);
    }
    //clamp control
    if (con.ButtonY.pressing()){
      if (f2loop){
        clamp.open();
      }
      if (!f2loop){
        clamp.close();
      }
      f3loop = true;
    }
    else if (f3loop){
      f2loop = !f2loop;
      f3loop = false;
    }
  }

  wait (20, msec); //prevent system overload 
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
