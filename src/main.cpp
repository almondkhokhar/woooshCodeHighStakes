/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Arjomand Khokhar                                          */
/*    Created:      9/7/2024, 7:27:23 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
// variable initiation
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
bool f2loop = false;
bool f3loop = true;
bool f4loop = true;
bool f5loop = false;
bool f6loop = true;
bool f7loop = false;
bool f8loop = true;
bool f9loop = true;
bool f10loop = true;
bool f11loop = false;
bool f12loop = true;
bool f13loop = true;
bool isRed = false;
bool reject = false;
bool shouldReject = true;
bool rejectStart = false;
int counter = 0;
int lbState = 0;

int autoSelect = 0;
double hue = Optical.hue();
color detectColor = Optical.color();


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
int colorReject(){
  double counter = 0;
  while (shouldReject){
    //416
    //855
    //1258
    //5343
    //5520
    if (Optical.isNearObject() && f13loop && vex::timer::system() - counter > 1000){
      rejectStart = true;
      counter = vex::timer::system();
      f13loop = false;

    }
    if (240 > Optical.hue() && Optical.hue() > 220 && isRed && rejectStart){
      reject = true;
      double currPos = intake.position(deg);
      intake.spinToPosition(currPos+54, deg, 100 ,rpm, true);
      wait(.05, sec);
      intake.spinToPosition(currPos+57, deg, 60 ,rpm, true);
      wait(.2, sec);
      rejectStart = false;
      f4loop = true;
      f13loop = true;
      f11loop = true;
    }
    else if (f11loop){
      if (!Optical.isNearObject()){
        intake.stop();
        // wait(.05, sec);
        // intake.spin(fwd, -10, pct);
        wait(.5, sec);
        reject = false;
        f11loop = false;
      }
    }
    if (Optical.hue() < 10 && !isRed && Optical.isNearObject()){
      reject = true;
      double currPos = intake.position(deg);
      intake.spinToPosition(currPos+54, deg, 100 ,rpm, true);
      wait(.05, sec);
      intake.spinToPosition(currPos+57, deg, 60 ,rpm, true);
      wait(.2, sec);
      rejectStart = false;
      f4loop = true;
      f13loop = true;
      f11loop = true;
    }
    else if (f11loop){
      if (!Optical.isNearObject()){
        intake.stop();
        // wait(.05, sec);
        // intake.spin(fwd, -10, pct);
        wait(.5, sec);
        reject = false;
        f11loop = false;
      }
    }
  }
  return(0);
}


 int ladyBrownMechZero(){
  while(Rotation.position(deg)- 3 > 20){
    if (Rotation.position(deg)  > 350){
      lift.spin(fwd, 100,pct);
      lift2.spin(fwd, 100,pct);
    }
    else if (Rotation.position(deg) - 3 > 20){
      lift.spin(fwd, -100,pct);
      lift2.spin(fwd, -100,pct);
    }
    else {
      lift.stop();
      lift2.stop();
    }
  }
  lift.stop();
  lift2.stop();
  return(0);
}

int ladyBrownMechScoring(){
  double lbkP = 1.2;
  double lbkD = .3;
  double lbSpeed;

  if (lbState == 0){
    while(Rotation.position(deg)- .2 > 17){
      lbSpeed = lbkP * (17-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg)  > 350){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 17){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else {
        lift.stop();
        lift2.stop();
      }
    }
    lift.stop();
    lift2.stop();
    return(0);
  }
  if (lbState == 1){
    while(Rotation.position(deg)- .2 > 41.3 or Rotation.position(deg) + .2 < 41.3 ){
      lbSpeed = lbkP * (41.3-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 41.3){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 41.3){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else {
        lift.stop(hold);
        lift2.stop(hold);
      }
    }
    lift.stop(hold);
    lift2.stop(hold);
    return(0);
  }
  // if (lbState == 2){
  //   while(Rotation.position(deg) - 3 > 157.5 or Rotation.position(deg) + 3 < 157.5){
  //     if (Rotation.position(deg) + 3 < 157.5){
  //       lift.spin(fwd, 100,pct);
  //       lift2.spin(fwd, 100,pct);
  //     }
  //     else if (Rotation.position(deg) - 3 > 157.5){
  //       lift.spin(fwd, -100,pct);
  //       lift2.spin(fwd, -100,pct);
  //     }
  //     else {
  //       lift.stop(hold);
  //       lift2.stop(hold);
  //     }
  //   }
  //   lift.stop(hold);
  //   lift2.stop(hold);
  //   return(0);
  // }
    if (lbState == 2){
    while(Rotation.position(deg) - .2 > 149.5 or Rotation.position(deg) + .2 < 149.5){
      lbSpeed = lbkP * (149.5-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 149.5){
        lift.spin(fwd, lbSpeed ,pct);
        lift2.spin(fwd,  lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 149.5){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else {
        lift.stop(hold);
        lift2.stop(hold);
      }
    }
    lift.stop(hold);
    lift2.stop(hold);
    return(0);
  }
  if (lbState == 3){
    while(Rotation.position(deg) - .2 > 70 or Rotation.position(deg) + .2 < 70){
      lbSpeed = lbkP * (70-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 70){
        lift.spin(fwd,  lbSpeed,pct);
        lift2.spin(fwd,  lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 70 ){
        lift.spin(fwd,  lbSpeed,pct);
        lift2.spin(fwd,  lbSpeed,pct);
      }
      else {
        lift.stop(hold);
        lift2.stop(hold);
      }
    }
    lift.stop(hold);
    lift2.stop(hold);
    return(0);
  }
  if (lbState == 4){
    while(Rotation.position(deg) - .2 > 166 or Rotation.position(deg) + .2 < 166){
      lbSpeed = lbkP * (166-Rotation.position(deg)) - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 166){
        lift.spin(fwd, lbSpeed ,pct);
        lift2.spin(fwd,  lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 166){
        lift.spin(fwd,  lbSpeed,pct);
        lift2.spin(fwd,  lbSpeed,pct);
      }
      else {
        lift.stop(hold);
        lift2.stop(hold);
      }
    }
    lift.stop(hold);
    lift2.stop(hold);
    return(0);
  }
  return (0);
}


void pre_auton(void) {
  //calibrate inertial sensor
  Inertial.calibrate();
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("1=Testing, 2=Skills");
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("3=RedPos, 4=RedNeg");
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("5=BluePos, 6=BlueNeg");
  Brain.Screen.setCursor(5,1);
  Brain.Screen.print("7=RedSOLOAWP, 8=BlueSOLOAWP");
  Brain.Screen.setCursor(6,1);
  Brain.Screen.print("9=RedMax, 10=BlueMax");
  while (true){
    if (lSwitch.pressing() && f10loop){
      f10loop = false;
      if (autoSelect == 9){
        autoSelect = -1;
      }
      autoSelect += 1;
      Brain.Screen.setCursor(1,1);
      Brain.Screen.clearLine();
      Brain.Screen.print("Auto", autoSelect);
    }
    else {
      f10loop = true;
    }
  }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int fasterClamping(){
  wait(.65, sec);
  clamp.open();
  return(0);
}
int fasterClamping2(){
  wait(.55 , sec);
  clamp.open();
  return(0);
}

int fasterClamping3(){
  wait(.9, sec);
  clamp.open();
  return(0);
}

int fasterClamping4(){
  wait(.75 , sec);
  clamp.open();
  return(0);
}
int clamping(){
  wait(.7, sec);
  clamp.open();
  return(0);
}
int lastClamp(){
  wait(.8, sec);
  clamp.open();
  return(0);
}
int waitState(){
  wait(.3, sec);
  ladyBrownMechScoring();
  wait(.6, sec);
  intake.spin(fwd, -40, pct);
  wait(.2, sec);
  intake.stop();
  return(0);
}
int clampP7(){
  wait(.55, sec);
  clamp.open();
  return(0);
}
int waitState2(){
  ladyBrownMechScoring();
  wait(.4, sec);
  intake.spin(fwd, -100, pct);
  wait(.1, sec);
  intake.stop();
  return(0);
}

int hookRemove(){
  wait(.55, sec);
  intake.spin(fwd, -100, pct);
  wait(.15, sec);
  intake.stop();
  lbState=3;
  task ringMid1 = task(ladyBrownMechScoring);
  wait(.75, sec);
  return(0);
}

int hookRemoved2(){
  wait(.35, sec);
  intake.spin(fwd, -100, pct);
  wait(.2, sec);
  intake.stop();
  lbState=2;
  task ringMid2 = task(ladyBrownMechScoring);
  wait(.9, sec);
  return(0);
}
int slowUp(){
  wait(1, sec);
  lbState = 1;
  task ringOne1 = task(ladyBrownMechScoring);
  return(0);
}
int intakeOnOff(){
  wait(.35, sec);
  intake.spin(fwd, -100, pct);
  wait(.2, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int unclamp(){
  wait(.4, sec);
  clamp.close();
  return(0);
}
int hookSaver(){
  intake.stop();
  wait(.3, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int stake2 (){
  wait(.4, sec);
  lbState = 3;
  task ladyUp = task(ladyBrownMechScoring);
  wait(1, sec);
  return(0);
}


int clampClose(){
  wait(.4, sec);
  clamp.close();
  return(0);
}
int clampRelease(){
  wait(.5, sec);
  intake.stop();
  clamp.close();
  return(0);
}

int intakeWait(){
  wait(.55, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakeWaitTimeOpt(){
  wait(.75, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakeWait70(){
  wait(.75, sec);
  intake.spin(fwd, 70, pct);
  return(0);
}
int intakeShortWait(){
  wait(.25, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakeSlowerStop(){
  wait(2.15, sec);
  intake.stop();
  return(0);
}
int intakePause(){
  wait(1, sec);
  intake.stop();
  return(0);
}
int intakeSlowStop(){
  wait(.5, sec);
  intake.stop();
  return(0);
}
int hookRemoved(){
  wait(.55, sec);
  intake.spin(fwd, -100, pct);
  wait(.2, sec);
  intake.stop();
  lbState=2;
  task ringMid2 = task(ladyBrownMechScoring);
  wait(.9, sec);
  return(0);
}
int intakeWait50RedMinus(){
  wait(.55, sec);
  intake.spin(fwd, 65, pct);
  return(0);
}
int clampOne(){
  wait(1.05, sec);
  clamp.open();
  return(0);
}
void blueMOGORush(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed = false;
  task onlyBlues = task(colorReject);
  Drive.moveDistance(-33.5, 100, 1.1);
  Drive.turn(36, 100, .55);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-10.5, 40, .8);
  intake.spin(fwd,100,pct);
  Drive.turn(-20, 100, .5);
  task clampReleaser = task(clampRelease);
  Drive.moveDistance(38, 70, 1.3);
  Drive.turn(35, 100, .6);
  task fastClamp2 = task(fasterClamping2);
  Drive.moveDistance(-26, 40, 1.4);
  Drive.moveDistance(5, 100, .4);
  intake.spin(fwd, 100, pct);
  Drive.turn(-55, 100, .7);
  intakeLift.open();
  Drive.moveDistance(40, 60, 1.2);
  intake.spin(fwd, 60, pct);
  intakeLift.close();
  wait(.23, sec);
  intake.stop();
  Drive.moveDistance(-14, 100, .6);
  clamp.close();
  Drive.turn(0, 100, .55);
  Drive.moveDistance(12, 100, .6);
  Drive.turn(90, 100, .7);
  Drive.moveDistance(-3.1, 40, .5);
  Drive.turn(180, 100, .6);
  Drive.moveDistance(-4.1, 100, .5);
  intake.spin(fwd, 100, pct);
  wait(.7, sec);
  lbState = 2;
  task redMinusLB = task(ladyBrownMechScoring);
  Drive.moveDistance(25, 100, .9);
  Drive.turn(150, 100, .3);

}

void redMOGORush(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed = true;
  task onlyReds = task(colorReject);
  Drive.moveDistance(-33.5, 100, 1.1);
  Drive.turn(-36, 100, .55);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-10.5, 40, .8);
  intake.spin(fwd,100,pct);
  Drive.turn(20, 100, .5);
  task clampReleaser = task(clampRelease);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(39, 70, 1.3);
  Drive.turn(-35, 100, .6);
  task fastClamp2 = task(fasterClamping2);
  Drive.moveDistance(-27, 40, 1.4);
  Drive.moveDistance(5, 100, .4);
  intake.spin(fwd, 100, pct);
  Drive.turn(55, 100, .7);
  intakeLift.open();
  Drive.moveDistance(40, 60, 1.2);
  intake.spin(fwd, 60, pct);
  intakeLift.close();
  wait(.23, sec);
  intake.stop();
  Drive.moveDistance(-14, 100, .6);
  clamp.close();
  Drive.turn(0, 100, .55);
  Drive.moveDistance(12, 100, .6);
  Drive.turn(-90, 100, .7);
  Drive.moveDistance(-4.7  , 60, .6);
  Drive.turn(-180, 100, .6);
  Drive.moveDistance(-5.5, 100, .5);
  intake.spin(fwd, 100, pct);
  wait(.7, sec);
  lbState = 2;
  task redMinusLB = task(ladyBrownMechScoring);
  Drive.moveDistance(25, 100, .9);
  Drive.turn(-150, 100, .3);

}

void redMinus(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed= true;
  task rejectinator = task(colorReject);
  task sleepy = task(intakeWait50RedMinus);
  Drive.moveDistance(33, 40, 1.4);
  intake.stop();
  Drive.moveDistance(-3, 100, .5);
  Drive.turn(-90, 60, .9);
  task sleepyClamp = task(fasterClamping2);
  Drive.moveDistance(-22, 40, 1.2);
  Drive.turn(-10, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.swing(21, 20, -90, 3);
  intake.spin(fwd, 100, pct);
  Drive.swing(20, 30, -130, 1.6);
  Drive.turn(100, 100, 1.2);
  Drive.moveDistance(42, 70, 1);
  lbState = 1;
  task redMinusLB = task(ladyBrownMechScoring);

}
void blueMinus(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed= false;
  task rejectinator = task(colorReject);
  task sleepy = task(intakeWait50RedMinus);
  Drive.moveDistance(33, 40, 1.4);
  intake.stop();
  Drive.moveDistance(-3, 100, .5);
  Drive.turn(90, 60, .9);
  task sleepyClamp = task(fasterClamping2);
  Drive.moveDistance(-22, 40, 1.2);
  Drive.turn(10, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.swing(21, 20, 90, 3);
  intake.spin(fwd, 100, pct);
  Drive.swing(20, 30, 130, 1.6);
  Drive.turn(-100, 100, 1.2);
  Drive.moveDistance(42, 70, 1);
  lbState = 1;
  task redMinusLB = task(ladyBrownMechScoring);
}


void redSoloAWP(){
  // Optical.setLightPower(10, pct);
  // shouldReject = true;
  // isRed = true;
  // task cReject = task(colorReject);
  Drive.swing(-12, 40, -90, 1.1);
  Drive.moveDistance(-1.1, 30, .3);
  intake.spin(fwd, 100, pct);
  wait(.8, sec);
  Drive.swing(12, 80, -160, 1);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(38, 70, 1.1);
  intake.stop();
  Drive.moveDistance(-4, 100, .4);
  wait(.1,sec);
  Drive.turn(-233, 100, .8);
  task clamp1 = task(clampP7);
  Drive.moveDistance(-25, 55, 1);
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-175, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(20, 70, 1);
  Drive.moveDistance(-3, 100, .3);
  Drive.turn(-90, 100, .7);
  Drive.moveDistance(11, 100, .6);
  Drive.moveDistance(-11, 100, .6);
  Drive.turn(-120, 100, .3);
  Drive.moveDistance(13, 100, .7);
  lbState = 1;
  task LB = task(ladyBrownMechScoring);
  Drive.moveDistance(-10, 100, 1);
  Drive.turn(-140, 100, .6);
  intake.stop();
  Drive.moveDistance(20, 100, .8);
  lbState = 2;
  task AWPLB = task(ladyBrownMechScoring);
  wait(.5, sec);
  Drive.moveDistance(-40, 100, 1.5);
  // wait(.3, sec);
  // Drive.moveDistance(-74, 100, 1.5);
  // Drive.turn(-40, 100, .9);
  // clamp.close();
  // intake.spin(fwd, 60, pct);
  // Drive.moveDistance(43, 80, 1.5);
  // intake.stop();
  // Drive.turn(0, 100, .5);
  // task clamp2 = task(fasterClamping3);
  // Drive.moveDistance(-29, 70, 1.1);
  // intake.spin(fwd, 100, pct);
  // Drive.turn(-135, 100, .8);
  // lbState = 1;
  // task AWPLB = task(ladyBrownMechScoring);
  // Drive.moveDistance(10, 100, .7);
  // wait(.3, sec);
  // Drive.turn(0, 100, .7);
  // task slow = task(intakeSlowStop);
  // lbState = 2;
  // task AWPLB = task(ladyBrownMechScoring);
  // Drive.moveDistance(40, 80, 1);
}
void blueSoloAWP(){
  // Optical.setLightPower(10, pct);
  // shouldReject = true;
  // isRed = false;
  // task cReject = task(colorReject);
  Drive.swing(-12, 40, -90, 1.1);
  Drive.moveDistance(-1.15, 30, .3);
  intake.spin(fwd, 100, pct);
  wait(.7, sec);
  Drive.swing(12, 80, -160, 1);
  Drive.moveDistance(35, 100, 1.05);
  intake.stop();
  wait(.1, sec);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(-239, 100, .8);
  task clamp1 = task(fasterClamping2);
  Drive.moveDistance(-17, 50, 1);
  Drive.turn(-160, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(23, 70, 1);
  wait(.3, sec);
  Drive.moveDistance(-74, 100, 1.7);
  Drive.turn(-40, 100, .9);
  clamp.close();
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(43, 80, 1.4);
  Drive.moveDistance(-7.5, 100, .5);
  intake.stop();
  Drive.turn(0, 100, .5);
  task clamp2 = task(fasterClamping2);
  Drive.moveDistance(-29, 70, 1.1);
  intake.spin(fwd, 100, pct);
  Drive.turn(-135, 100, .8);
  lbState = 1;
  task AWPLB = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .7);
}
void newBlue(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed = false;
  task cReject = task(colorReject);
  Drive.swing(-12, 40, 90, 1.1);
  Drive.moveDistance(-1.1, 30, .3);
  intake.spin(fwd, 100, pct);
  wait(.7, sec);
  intake.stop();
  Drive.moveDistance(19, 100, .8);
  Drive.turn(0, 100, .9);
  Drive.moveDistance(35, 100, 1);
  wait(.1, sec);
  Drive.turn(-57, 100, .8);
  task clamp1 = task(fasterClamping2);
  Drive.moveDistance(-18.5, 40, 1.2);
  Drive.turn(12, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(23, 70, 1);
  // wait(.3, sec);
  // Drive.moveDistance(-74, 100, 1.5);
  // Drive.turn(-40, 100, .9);
  // clamp.close();
  // intake.spin(fwd, 60, pct);
  // Drive.moveDistance(43, 80, 1.5);
  // intake.stop();
  // Drive.turn(0, 100, .5);
  // task clamp2 = task(fasterClamping3);
  // Drive.moveDistance(-29, 70, 1.1);
  // intake.spin(fwd, 100, pct);
  // Drive.turn(-135, 100, .8);
  // lbState = 1;
  // task AWPLB = task(ladyBrownMechScoring);
  // Drive.moveDistance(10, 100, .7);
  wait(.3, sec);
  intake.stop();
  Drive.turn(180, 100, .9);
  intake.spin(fwd, 100, pct);
  lbState = 2;
  task AWPLB = task(ladyBrownMechScoring);
  Drive.moveDistance(36, 100, 1);
}

// void simpleAWPposBlue(){
//   Optical.setLightPower(10, pct);
//   shouldReject = true;
//   clamp.open();
//   Drive.swing(-25, 100, 60, 1);
//   Drive.moveDistance(-5, 100, .5);
//   clamp.close();
//   Drive.turn(90, 100, .7);
//   intake.spin(fwd, 100, pct);
//   Drive.moveDistance(26, 20, 2);
//   intake.stop();
//   Drive.turn(0, 100, .7);
//   Drive.moveDistance(-9, 100, .6);
//   Drive.turn(30, 100, .5);
//   Drive.moveDistance(-9.2, 30, 1);
//   clamp.close();
//   Drive.turn(-90, 100, .8);
//   Drive.moveDistance(18, 100, .8);
// }

// void skills(){
//   lift.stop(hold);
//   lift2.stop(hold);
//   intake.spin(fwd, 100, pct);
//   wait(.65, sec);
//   Drive.turn(35.5, 100, .4);
//   intake.spin(fwd, 70, pct);
//   Drive.moveDistance(43, 100, 1.1);
//   task slowintake = task(intakeSlowStop);
//   Drive.turn(-45, 100, .7);
//   task waitintake = task(intakeWait);
//   Drive.moveDistance(27, 100, .8);
//   task slowintake2 = task(intakeSlowerStop);
//   Drive.turn(40, 100, .6);
//   Drive.swing(27 , 100, 0, .8);
//   Drive.swing(31, 100, 90, 1);
//   Drive.moveDistance(-13, 80, .7);
//   clamp.open();
//   wait(.15, sec);
//   intake.spin(fwd, 100, pct);
//   Drive.moveDistance(26, 100, .8);
//   Drive.moveDistance(35, 20, 1.2);
// }

void simHitSkills(){
  Optical.setLightPower(10, pct);
  shouldReject = true;
  isRed = true;
  intake.spin(fwd,100,pct);
  // task onlyReds = task(colorReject);
  wait(.45, sec);
  Drive.moveDistance(14, 100, .7);
  lbState=0;
  task state0 = task(ladyBrownMechZero);
  Drive.turn(-90,100, .6);
  task slowClamp = task(clamping);
  Drive.moveDistance(-23.5, 40, 1.1);
  Drive.turn(0, 100, .8);
  Drive.moveDistance(20, 100, .7);
  Drive.turn(27, 100, .75);
  task slowUp1 = task(slowUp);
  Drive.moveDistance(50, 80, 1.6);
  intake.spin(fwd,60,pct);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(180, 70, .8);
  task removeHook = task(hookRemove);
  wait(.2, sec);
  task waitIntake = task(intakeWait);
  Drive.moveDistance(8.5, 100, .7);
  Drive.turn(90, 100, .7);
  Drive.moveDistance(11, 70, .7);
  lbState = 2;
  task ringScore1 = task(ladyBrownMechScoring);
  intake.stop();
  Drive.turn(90, 30, .3);
  Drive.moveDistance(1000, 100, .5);
  Drive.turn(90, 100, .4);
  task saveTheLady = task(ladyBrownMechZero);
  Drive.moveDistance(-15, 100, .8);
  intake.spin(fwd, 100, pct);
  Drive.turn(180, 100, .8);
  Drive.moveDistance(33, 70, 1.1);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(36, 20, 1.9);
  Inertial.setRotation(180, deg);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(60, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(16, 70, .9);
  Drive.turn(-17, 70, .6);
  Drive.moveDistance(-20, 100, .6);
  wait(.5, sec);
  clamp.close();
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-51, 100, .6);
  task superMarioBrosSlow = task(intakeSlowerStop);
  Drive.moveDistance(40, 100, 1);
  Drive.turn(-51, 100, .2);
  task saveTheCaptain = task(hookSaver);
  Drive.moveDistance(38, 100, .95);
  Drive.turn(-135, 100, .7);
  task slowStartViolation = task(intakeShortWait);
  task slowEndViolation = task(intakePause);
  Drive.moveDistance(48, 90, 1.5);
  Drive.turn(-37, 100, .7);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-19, 45, .8);
  task onOff = task(intakeOnOff);
  Drive.turn(-49, 100, .4);
  wait(.7, sec);
  Drive.moveDistance(35 , 50 , 1.3);
  Drive.moveDistance(-3, 100, .3);
  Drive.turn(-180, 100, .9);
  Drive.moveDistance(23, 30, 1.5);
  Drive.moveDistance(18, 30, 1.1);
  Inertial.setRotation(-180, deg);
  Drive.moveDistance(-3, 100, .3);
  Drive.turn(-55, 100, .7);
  Drive.moveDistance(16, 70, .7);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(-10, 100, .6);
  clamp.close();
  Drive.turn(3, 100, .5);
  // //28.4 seconds on 11/16/24 // 34.75 on 11/17/24
  lbState = 1;
  task ladyLift = task(ladyBrownMechScoring);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(59, 70, 1.7);
  Drive.moveDistance(-6, 100, .45);
  // Drive.turn(30, 100, .4);
  // wait(.4, sec);
  // task removeIntakeHook = task(hookRemoved);
  // task pauseIntake = task(intakeWait70);
  // wait(.3, sec);
  // Drive.moveDistance(26, 50, 1.3);
  // Drive.turn(0, 100, .5);
  // task removeIntakeHooked = task(hookRemoved);
  // Drive.moveDistance(-25.3, 70, 1);
  // Drive.turn(-90, 100, .6);
  // task dosSteaksPorFavor = task(stake2);
  // Drive.moveDistance(20, 70, .7);
  // wait(.4, sec);
  // Drive.moveDistance(-20, 100, 1);
  // intake.spin(fwd, 100, pct);
  Drive.turn(-90, 100, .9);
  intake.stop();
  lbState = 2; 
  task ladyStake2 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .6);
  wait(.4, sec);
  Drive.moveDistance(-20, 100, 1);
  Drive.turn(40, 100, .7);
  task ladyReset = task(ladyBrownMechZero);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(35, 70, 1.3);
  intake.stop();
  Drive.turn(222, 100, 1.1);
  task lastClamp1 = task(lastClamp);
  Drive.moveDistance(-29, 50, 1.2);
  Drive.turn(138, 100, .8);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(30, 100, 1);
  Drive.turn(43, 100, .6);
  Drive.moveDistance(30, 100, 1);
  Drive.turn(238, 100, .9);
  wait(.3,sec);
  task Yay = task(unclamp);
  wait(.1, sec);
  intake.stop();
  Drive.moveDistance(-30, 100, .8);
  Drive.turn(228, 100, .5);
  Drive.moveDistance(18, 100, .6);
  intake.spin(fwd, 60, pct);
  Drive.turn(270, 100, .6);
  Drive.moveDistance(40, 100, 1.3);
  Drive.turn(300, 100, .6);
  Drive.moveDistance(20, 100, .7);
  Drive.turn(270, 100, .4);
  Drive.moveDistance(38, 100, 1.1);
  Drive.moveDistance(-10, 100, .4);
  lbState = 2; 
  task hang = task(ladyBrownMechScoring);
  Drive.turn(327, 100, 1);
  intake.stop();
  Drive.moveDistance(-45, 100, 1.4);
  Drive.turn(315, 100, .4);
  Drive.moveDistance(1000, 50, 3);




  // Drive.turn(90, 100, .8);
  // intake.spin(fwd, 60, pct);
  // Drive.moveDistance(50, 100, 1.6);
  // Drive.moveDistance(-5, 100, .4);
  // Drive.turn(228, 100, .8);
  // wait(.2, sec);
  // clamp.close();
  // Drive.moveDistance(-30, 100, .8);
  // Drive.turn(228, 100, .5);
  // Drive.moveDistance(15, 100, .6);
  // Drive.turn(270, 100, .6);
  // Drive.moveDistance(40, 100, 1.4);
  // Drive.turn(300, 100, .6);
  // Drive.moveDistance(20, 100, .7);
  // Drive.turn(270, 100, .4);
  // Drive.moveDistance(38, 100, 1.1);
  // Drive.moveDistance(-7, 100, .4);
  // Drive.moveDistance(10, 100, 1.1);
  // Drive.moveDistance(-10, 100, .4);
  // lbState = 2; 
  // task hang = task(ladyBrownMechScoring);
  // Drive.turn(330, 100, 1);
  // intake.stop();
  // Drive.moveDistance(-53, 50, 3);





  //this is where i started

  // intake.spin(fwd, 100, pct);
  // Drive.moveDistance(-75, 100, 3);
  // clamp.close();
  // Drive.swing(60, 100, -60, 2.4);
  // Drive.swing(60, 100, -90, 2);
  // Drive.turn(-45, 100, 1); 
  // lbState = 3;
  // task audiQuattro = task(ladyBrownMechScoring);
  // Drive.moveDistance(-75,60, 1.2);
  // intake.spin(fwd, 100, pct);
  // Drive.turn(-90, 100, .8);
  // Drive.moveDistance(-80, 100, 1.4);
  // Drive.turn(-170, 100, .7);
  // Drive.moveDistance(-100, 100, .7);
  // clamp.close();
  // Drive.moveDistance(5, 100, .4);
  // Drive.turn(-90, 100, 1);
  // Drive.swing(130, 100, -40, 2.4); 



  // Drive.moveDistance(100, 100, 2);
  // Drive.moveDistance(70, 100, 1.8);
  // Inertial.setRotation(0, deg);
  // Drive.moveDistance(-2, 100, .4);
  // Drive.turn(-90, 100, .65);
  // Drive.moveDistance(-6, 100, .4);
  // intake.spin(fwd, 40, pct);
  // Drive.moveDistance(23, 100, .9);
  // intake.stop();
  // Drive.turn(-225, 100, 1);
  // Drive.turn(40, 100, .6);
  // lbState = 1;
  // task lady1 = task(ladyBrownMechScoring);
  // Drive.moveDistance(36, 70, 1.1);
  // Drive.turn(-50, 100, .7);
  // task wallStake2 = task(hookRemoved);
  // wait(.3, sec);
  // task pauseIntakeBlue = task(intakeWait70);
  // Drive.moveDistance(35, 60, 1.1);
  // Drive.turn(-180, 100, .9);
  // Drive.moveDistance(43, 100, 1.1);
  // task removeIntakeHookedQuattro = task(hookRemove);
  // Drive.turn(-90, 100, .6);
  // Drive.moveDistance(30, 100, .8);
  // lbState = 3;
  // task audiQuattro = task(ladyBrownMechScoring);
  // wait(.7, sec);
  // Drive.moveDistance(-17, 100, 1);
  // Drive.turn(7, 100, .7);
  // lbState = 1;
  // task ladyLiftYes = task(ladyBrownMechScoring);
  // Drive.moveDistance(47, 100, 1.3);
  // Drive.turn(0, 100, .3);
  // Drive.moveDistance(17, 100, .7);
  // Inertial.setRotation(0, deg);
  // Drive.moveDistance(-3, 100, .3);
  // Drive.turn(-90, 100, .8);
  // Drive.moveDistance(-8, 40, .6);
  // clamp.open();
  // Drive.swing(40, 100, -225, 1.4);
  // Drive.moveDistance(-6, 100, .5);
  // clamp.close();
  // Drive.turn(180, 100, .55);
  // Drive.moveDistance(7, 100, .4);

  //52.85 11/17/24



  
}
void testing(){
  Drive.moveDistance(10, 100, .9);
}

void blueelims(){
  intake.spin(fwd,100,pct);
  lbState = 1; 
  task pickUp = task(ladyBrownMechScoring);
  Drive.swing(45, 100, -50, 1.2);
  Drive.moveDistance(-8, 100, .6);
  Drive.turn(40, 100, .7);
  lbState = 2; 
  task score = task(ladyBrownMechScoring);
  Drive.moveDistance(7, 50, .9);
}

void simAWP(){
  task intControl = task(intakeWait50RedMinus);
  Drive.moveDistance( 21.647887323669252+4.901408450642095 , 100 , .9 );	
  intake.stop();
  Drive.turn( 90 , 100 , .65 );	

  task c1 = task(clampP7);
  Drive.moveDistance( -16.746478873027158 , 70 , .9 );	
  Drive.turn( 232.14743605677376 , 100 , .9 );	
  intake.spin(fwd, 100, pct);
  wait(.3, sec);
  intakeLift.open();
  Drive.moveDistance( 33.492957746054316 , 100 , 1.2 );	
  wait(.3, sec);
  intake.stop();
  clamp.close();
  intakeLift.close();
  Drive.turn( 360-68.90081325936256 , 100 , .5 );		
  Drive.moveDistance( 18.42253521100873 , 100 , 1.1 );	
  Drive.turn( 153 , 100 , .65 );	

  task c2 = task(clampP7);
  Drive.moveDistance( -10.169014084403491 , 70 , 1.1 );	
  intake.spin(fwd, 100, pct);
  Drive.turn( -77.85886760649004 , 100 , 1.00000009 );	
  Drive.moveDistance( 23.69014084477012 , 100 , .9 );
  lbState = 1; 
  task set = task(ladyBrownMechScoring);
  Drive.turn(-42, 100, .4);
  Drive.moveDistance(22.2, 100, 1);
  intake.stop();
  lbState = 2; 
  task score = task(ladyBrownMechScoring);
  Drive.moveDistance(-10, 100, .6);
  Drive.turn(90, 100, .7);
}
void bluePlusElims(){
  task c1 = task(clampOne);
  Drive.swing(-45.2, 100, 35, 1.15);
  Drive.moveDistance(7, 100, .5);
  Drive.turn(132, 100, .7);
  Drive.moveDistance(9.5, 40, .6);
  lbState = 4; 
  task scoreDown = task(ladyBrownMechScoring);
  wait(.6, sec);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(-40, 100, 1.2);
  intake.spin(fwd, 100,pct);
  Drive.moveDistance(12, 100, 1);
  Drive.moveDistance(24, 100, .9);
  wait(.3, sec);
  intake.stop();
  clamp.close();
  Drive.turn(-90, 100, .7);
  intakeLift.open();
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(28, 100, 1);
  //intakeLift.close();
  wait(.2, sec);
  intake.stop();
  Drive.moveDistance(-10 , 100, .8);
  Drive.turn(-36, 100, .7);
  task lastClamp1 = task(fasterClamping4);
  Drive.moveDistance(-29, 60, .9);
  intake.spin(fwd, 100, pct);
  Drive.turn(-135, 100, .8);
  intakeLift.close();
  lbState = 0; 
  task down = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 40, .8);




}

void redPlus(){
  Drive.swing(-45, 100, -36, 1);
  clamp.open();
  wait(.15, sec);
  Drive.moveDistance(7, 100, .5);
  lbState = 2; 
  task score = task(ladyBrownMechScoring);
  Drive.turn(-132, 100, .8);
  Drive.moveDistance(8.5, 40, .9);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(40, 100, .9);
  intake.spin(fwd, 100,pct);
  Drive.moveDistance(12, 100, 1);
  Drive.moveDistance(28, 100, .9);
  wait(.5, sec);
  intake.stop();
  clamp.close();
  Drive.turn(90, 100, .7);
  intakeLift.open();
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(25, 100, 1);
  intakeLift.close();
  wait(.3, sec);
  intake.stop();
  Drive.moveDistance(-10, 100, .6);
  Drive.turn(36, 100, .6);
  task lastClamp1 = task(fasterClamping4);
  Drive.moveDistance(-29, 60, .9);
  intake.spin(fwd, 100, pct);



}
int clampwaiters(){
  wait(.4, sec);
  clamp.close();
  return(0);
}
int clampP6(){
  wait(.5, sec);
  clamp.open();
  return(0);
}

int clampOneFour(){
  wait(1.3, sec);
  clamp.open();
  return(0);
}
int deClamper(){
  wait(.7, sec);
  clamp.close();
  return(0);
}

void simTesting(){
  intake.spin(fwd,100,pct);
  wait(.5, sec);
  // Drive.moveDistance( 14.295774647706109 , 100 , .8 );	
  // Drive.turn( -90 , 100 , .8 );	

  
  // task c1 = task(clampP7);
  // Drive.moveDistance( -16.746478873027158 , 100 , .8 );	// first clamp
  // Drive.turn( 195.98031865128928 -180 , 100 , .8 );	
  // Drive.moveDistance( 19.60563380256838 , 100 , .9 );	//first ring
  // Drive.turn( 259.276538207964-180 , 100 , .65 );	
  // Drive.moveDistance( 20.42253521100873 , 100 , .9 );	//second ring
  // Drive.turn( 213.68061848329688-180 , 100 , .5 );	
  // Drive.moveDistance( 24.507042253210475 , 100 , .9 );	//third ring
  // Drive.turn( -6.214720571122712-180 , 100 , 1.00000009 );	
  // Drive.moveDistance( 38.39436619669641 , 100 , 1.2 );	//fourth ring
  // Drive.turn( 66.64328756160637-180 , 100 , .65 );	
  // Drive.moveDistance( 7.352112675963142 , 100 , .7 );	//fifth ring
  // Drive.turn( 18.346417160430008-180 , 100 , .5 );	
  // Drive.moveDistance( 9.394366197064015 , 100 , .7 );	//ring 6
  // Drive.turn( 122.85112524919296-180 , 100 , .8 );	
  // Drive.moveDistance( -5.309859154862269 , 100 , .8 );	// drop goal
  // clamp.close();
  // Drive.turn( 122.85112524919296-180 , 100 , .4 );	
  // Drive.moveDistance( 18.78873239412803 , 100 , .9 );	
  // Drive.turn( -90-180 , 100 , 1.00000009 );	

  // task c2 = task(clampOneFour);
  // Drive.moveDistance( -53.915492957063044 , 100 , 1.6 );	// second goal
  // Drive.turn( 163.54075037173976-180 , 100 , 1.00000009 );	
  // Drive.moveDistance( 19.60563380256838 , 100 , .9 );	// ring 1 goal 2
  // Drive.turn( 99.87523830972361-180 , 100 , .65 );	
  // Drive.moveDistance( 20.42253521100873 , 100 , .9 );	// ring 2 goal 2
  // Drive.turn( 145.6142071030391-180 , 100 , .5 );	
  // Drive.moveDistance( 24.507042253210475 , 100 , .9 );	// ring 3 goal 2
  // Drive.turn( 3.66572688886572-180 , 100 , .9 );	
  // Drive.moveDistance( 38.39436619669641 , 100 , 1.2 );	// ring 4 goal 2
  // Drive.turn( -67.27523284702278-180 , 100 , .65 );	
  // Drive.moveDistance( 7.760563380183316 , 100 , .7 );	//ring 5 goal 2
  // Drive.turn( -16.968164296991972-180 , 100 , .5 );	
  // Drive.moveDistance( 9.394366197064015 , 100 , .7 );	// ring 6 goal 2
  // Drive.turn( 237.77226563448414-180 , 100 , 1.00000009 );	
  // Drive.moveDistance( -5.309859154862269 , 100 , .8 );	// unclamp
  // clamp.close();
  // Drive.turn( 185.223900382058-180 , 100 , .5 );	


  // lbState = 2; 
  // task ladyStake = task(ladyBrownMechScoring);
  // intake.spin(fwd, 60, pct);
  // Drive.moveDistance( 76.38028168917265 , 100 , 2.5 );	// 1 for W2
  // Drive.turn( 258.5116137663494-180 , 100 , .65 );	
  // Drive.moveDistance( 19.60563380256838 , 100 , .9 );	//1 for goal 4
  // Drive.turn( 62.00640192322385-180 , 100 , 1.00000009 );	
  // Drive.moveDistance( 37.57746478825606 , 100 , 1.3 );	// w2
  // lbState = 3; 
  // task ladyStake = task(ladyBrownMechScoring);
  // Drive.turn( 198.85424714647314-180 , 100 , .9 );	
  // Drive.moveDistance( 40.028169013577106 , 100 , 1.2 );	// ring 2 for goal 4
  // Drive.moveDistance( 17.15492957724733 , 100 , .9 );	
  // Drive.turn( 90-180 , 100 , .8 );	


  // task c3 = task(clampP7);
  // Drive.moveDistance( -12.661971830825411 , 60 , .8 );	// goal 3
  // Drive.turn( -80.95231681727165-180 , 100 , 1 );	
  // Drive.moveDistance( -20.830985915228904 , 100 , 1 );	// unclamp
  // clamp.close();
  // Drive.turn( -65.95231681727165-180 , 100 , .4 );	
  // Drive.moveDistance( 37.98591549247624 , 100 , 1.3 );	
  // Drive.turn( 90-180 , 100 , 1 );	


  // task c4 = task(clampP6);
  // Drive.moveDistance( -9.394366197064015 , 60 , .7 );	// goal 4
  // Drive.turn( -52.147436056773756-180 , 100 , .9 );	
  // Drive.moveDistance( 33.492957746054316 , 100 , 1.2 );	// ring 3 goal 4
  // Drive.turn( -83.7833674406728-180 , 100 , .5 );	

  // lbState = 2; 
  // task ladyStake = task(ladyBrownMechScoring);

  // Drive.moveDistance( 22.873239436329776 , 100 , .9 );	//ring 1 for w1
  // Drive.turn( -49.05436663237298-180 , 100 , .5 );	
  // Drive.moveDistance( 26.957746478531522 , 100 , 1.1 );	//w1

  // lbState = 3; 
  // task ladyStake2 = task(ladyBrownMechScoring);

  // Drive.turn( 174.52706460076436-180 , 100 , 1.00000009 );	
  // Drive.moveDistance( 35.94366197137536 , 100 , 1.2 );	// ring 4 goal 4
  // Drive.turn( 110.44016880086983-180 , 100 , .65 );	
  // Drive.moveDistance( 8.169014084403491 , 100 , .7 );	// ring 5 goal 4
  // Drive.turn( 161.26025593022746-180 , 100 , .5 );	
  // Drive.moveDistance( 9.394366197064015 , 100 , .7 );	// ring 6 goal 4
  // Drive.turn( 56.973772634879076-180 , 100 , .8 );	
  // Drive.moveDistance( -5.309859154862269 , 100 , .8 ); // drop goal 4
  // clamp.close();




  Drive.moveDistance( 14.295774647706109 , 100 , .8 );	
  Drive.turn( 90-180 , 100 , .8 );	

  task c1 = task(clampP7);
  Drive.moveDistance( -16.746478873027158 , 60 , 1 );	// goal 1
  Drive.turn( 195.98031865128928-180 , 100 , .9 );	
  Drive.moveDistance( 19.60563380256838 , 100 , .9 );	//1,1
  Drive.turn( 259.276538207964-180 , 100 , .65 );	
  Drive.moveDistance( 20.42253521100873 , 100 , .9 );	//2,1
  Drive.turn( 213.68061848329688-180 , 100 , .6 );	
  Drive.moveDistance( 24.507042253210475 , 100 , .95 );	//3,1
  Drive.moveDistance( -5 , 100, .4 );
  Drive.turn( -7.445906193644646 , 100 , 1.00000009 );  Drive.moveDistance( 38.39436619669641 , 100 , 1.1 );	//4,1
  Drive.turn( 66.64328756160637+180 , 100 , .75 );	
  Drive.moveDistance( 7.352112675963142 , 100 , .5 );	//5,1
  Drive.turn( 18.346417160430008+180 , 100 , .6 );	
  Drive.moveDistance( 9.394366197064015 , 100 , .6 );	//6,1
  Drive.turn( 122.85112524919296+180 , 100 , .9 );	
  Drive.moveDistance( -8.98591549284384 , 100 , .5 );	//drop
  clamp.close();

  Drive.moveDistance( 22.056338027889428 , 100 , 1 );	
  Drive.turn( -90+180 , 100 , 1.2 );	

  task c2 = task(clampOneFour);
  Drive.moveDistance( -49, 100, 1.1);
  
  Drive.moveDistance(-4.915492957063044 , 38 , .5 );	// 2nd goal
  Drive.turn( 163.54075037173976-180 , 100 , .9 );	
  Drive.moveDistance( 19.60563380256838 , 100 , .9 );	//1,2
  Drive.turn( 99.87523830972361-180 , 100 , .65 );	
  Drive.moveDistance( 20.42253521100873 , 100 , .8 );	//2,2
  Drive.turn( 145.6142071030391-180 , 100 , .5 );	
  Drive.moveDistance( 24.507042253210475 , 100 , .9 );	//3,2
  Drive.turn( 3.66572688886572-180 , 100 , .9 );	
  Drive.moveDistance( 38.39436619669641 , 100 , 1.2 );	//4,2
  Drive.turn( -67.27523284702278-180 , 100 , .65 );	
  Drive.moveDistance( 7.760563380183316 , 100 , .7 );	//5,2
  Drive.turn( -16.968164296991972-180 , 100 , .5 );	
  Drive.moveDistance( 9.394366197064015 , 100 , .7 ); //6,2
  Drive.turn( 237.77226563448414-540 , 100 , .9 );	
  Drive.moveDistance( -8.98591549284384 , 100 , .8 );	//drop
  clamp.close();

  intake.spin(fwd, 60, pct);
  lbState = 1; 
  task ladyStake = task(ladyBrownMechScoring);
  Drive.turn( 186.45587322039893-540 , 100 , .5 );	
  Drive.moveDistance( 78.42253521027352 , 100 , 2.7 );	//1,w2
  Drive.turn( 258.5371950325996-540 , 100 , .65 );	
  Drive.moveDistance( 19.60563380256838 , 100 , .9 );	//1,4
  Drive.turn( 62.005280255096295-180 , 100 , .9 );	
  intake.stop();

  Drive.moveDistance( 37.57746478825606 , 100 , 1 );	//w2
  lbState = 2; 
  task ladyStakeScore = task(ladyBrownMechScoring);
  wait(.5, sec);

  Drive.moveDistance( -6.126760563302619 , 100 , .5 );	
  lbState = 0; 
  task ladyStakeDown = task(ladyBrownMechScoring);
  Drive.turn( 193.93598530302165-180 , 100 , .9 );	
  task waitAMinute = task(intakeWait70);
  Drive.moveDistance( 35.94366197137536 , 100 , 1 );//2,4
  intake.stop();
  Drive.moveDistance( 17.15492957724733 , 100 , .8 );	
  Drive.turn( 90-540 , 100 , .8 );	

  task c3 = task(clampP7);
  Drive.moveDistance( -13.887323943485935 , 100 , .7 );	//3rd goal
  Drive.turn( -80.95231681727165-180 , 100 , 1 );	
  Drive.moveDistance( -24.507042253210475 , 100 , .9 );	//drop
  clamp.close();

  Drive.turn( -65.95231681727165-180 , 100 , .4 );	
  Drive.moveDistance( 39.21126760513676 , 100 , 1.1 ); 	
  Drive.turn( 90-540 , 100 , 1 );	

  task c4 = task(clampP6);
  Drive.moveDistance( -11.436619718164888 , 100 , .6 );	//4th goal
  intake.spin(fwd, 100, pct);
  Drive.turn( -52.147436056773756-180 , 100 , .9 );	
  lbState = 1; 
  task ladyStakeW1 = task(ladyBrownMechScoring);
  Drive.moveDistance( 33.492957746054316 , 100 , 1 );	//1,w1
  Drive.turn( -83.7833674406728-180 , 100 , .5 );	
  Drive.moveDistance( 22.873239436329776 , 100 , .9 );	//3,4
  Drive.turn( -49.05436663237298-180 , 100 , .5 );	
  intake.stop();
  Drive.moveDistance( 26.957746478531522 , 100 , .9 );	//w1
  lbState = 2; 
  task ladyStakeScoreW1 = task(ladyBrownMechScoring);
  wait(.5, sec);

  intake.spin(fwd,100, pct);
  Drive.moveDistance( -6.126760563302619 , 100 , .5 );	
  Drive.turn( 183.77818215569772-540 , 100 , .9 );	
  Drive.moveDistance( 31.859154929173613 , 100 , 1 );	//4,4
  Drive.turn( 110.77205763304977-540 , 100 , .65 );	
  Drive.moveDistance( 7.760563380183316 , 100 , .6 );	//5,4
  Drive.turn( 161.30254003094748-540 , 100 , .5 );	
  Drive.moveDistance( 9.394366197064015 , 100 , .65 );	//6,4
  Drive.turn( 56.99253786160597-540 , 100 , .8 );	
  Drive.moveDistance( -8.98591549284384 , 100 , .6 );// drop
  clamp.close();

  Drive.turn( 43.60207279418859-900 , 100 , .7 );	
  Drive.moveDistance( -76.38028168917265 , 50 , 4 );
  }

void testig(){ 
  Drive.moveDistance(10, 100, .8);
}
void pasteRedPos(){
  task c1 = task(clampOne);
  Drive.swing(-45.7, 100, -35, 1.15);
  Drive.moveDistance(7, 100, .5);
  Drive.turn(-132, 100, .7);
  Drive.moveDistance(8.5, 40, .6);
  lbState = 4; 
  task scoreDown = task(ladyBrownMechScoring);
  wait(.6, sec);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(40, 100, 1.2);
  intake.spin(fwd, 100,pct);
  Drive.moveDistance(12, 100, 1);
  task stoppers = task(intakeSlowStop);
  Drive.moveDistance(24, 100, .9);
  wait(.3, sec);
  intake.stop();
  Drive.turn(90, 100, .7);
  intakeLift.open();
  task scoreDownclamp = task(clampwaiters);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(28, 100, 1);
  intake.stop();
  intakeLift.close();
  wait(.4, sec);
  Drive.moveDistance(-10 , 100, .8);
  Drive.turn(36, 100, .7);
  task lastClamp1 = task(fasterClamping4);
  Drive.moveDistance(-30, 60, .9);
  intake.spin(fwd, 100, pct);
  Drive.turn(-37, 100, .8);
  intakeLift.close();
  lbState = 0; 
  task down = task(ladyBrownMechScoring);
  bonk.open();
  task stoppers2 = task(intakeSlowStop);
  Drive.moveDistance(43, 100, 1);
  
  Drive.turn(60, 100, .8);
  bonk.close();
}

void pasteBluePos(){
  task c1 = task(clampOne);
  Drive.swing(-45.7, 100, 35, 1.05);
  Drive.moveDistance(7, 100, .5);
  Drive.turn(132, 100, .7);
  Drive.moveDistance(8.3, 40, .6);
  lbState = 2; 
  task scoreDown = task(ladyBrownMechScoring);
  wait(.6, sec);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(-40, 100, 1.2);
  intake.spin(fwd, 100,pct);
  Drive.moveDistance(12, 100, 1);
  Drive.moveDistance(24, 100, .9);
  intake.stop();
  wait(.3, sec);
  intake.stop();
  Drive.turn(-90, 100, .7);
  intakeLift.open();
  task scoreDownclamp = task(clampwaiters);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(28, 100, 1);
  intake.stop();
  intakeLift.close();
  wait(.4, sec);
  Drive.moveDistance(-10 , 100, .8);
  Drive.turn(-36, 100, .7);
  task lastClamp1 = task(fasterClamping4);
  Drive.moveDistance(-30, 60, .9);
  intake.spin(fwd, 100, pct);
  Drive.turn(37, 100, .8);
  intakeLift.close();
  lbState = 0; 
  task down = task(ladyBrownMechScoring);
  bonk.open();

  Drive.moveDistance(42, 100, 1);
  intake.stop();
  Drive.turn(60, 100, .8);
  bonk.close();
}
int bonky(){
  wait(.8, sec);
  bonk.open();
  return(0);
}
void dataCollection(){
  task bonkers = task(bonky);
  Drive.swing(38, 100, -6, .89);
  Drive.moveDistance(-10, 100, .7);

}
void (*autonsList[])() =
{
  dataCollection,
  pasteBluePos,
  pasteRedPos,
  redSoloAWP, 
  simHitSkills,
  bluePlusElims,
  redPlus,
  simAWP,
  simTesting,
  blueelims,
  blueSoloAWP,
  redMOGORush,
  redMinus,
  blueMinus,
  blueMOGORush,
  newBlue,
  testing,
  
  
  

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
    con.Screen.print("Bat:");
    con.Screen.print(Brain.Battery.capacity(percent));
    con.Screen.print("   Int:");
    con.Screen.print(intake.temperature(fahrenheit));
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
  //isRed = true;
  //task cReject = task(colorReject);
  //task printcon = task(conInfo);
  while (true)
  {

    Optical.setLightPower(10, percent);
    // con.Screen.clearScreen();
    // con.Screen.setCursor(1,1);
    // con.Screen.print(Inertial.rotation(deg));
    // if (!shouldReject){
    //   con.rumble(".       ");
    // }
    // else{
    //   con.rumble(" ");
    // }
  

    // if (con.ButtonA.pressing() && f12loop){
    //   shouldReject=!shouldReject;
    //   task cReject = task(colorReject);
    //   f12loop = false;
    // }
    // else{
    //   f12loop = true;
    // }


    // controls the speed at which the robot moves
    // moving controls
    rightdrive.spin(fwd, con.Axis2.value(), pct);
    leftdrive.spin(fwd, con.Axis3.value(), pct);
    // intake controls
    if (!reject){
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
        intake.stop();
      }
    }
    //0,35,145
    //lift controls
    if (con.ButtonL2.pressing()){
      lbState = 0;
      task ladyBrownZero = task(ladyBrownMechScoring);
    }
    else if (con.ButtonL1.pressing()){
      if (f9loop){
        lbState += 1;
        f9loop = false;
      }
      if (lbState > 2){
        lbState = 1;
      }
      task ladyBrownIntake = task(ladyBrownMechScoring);
    }
    else if (con.ButtonRight.pressing()){
      lbState = 4;
      task ladyBrownDescore = task(ladyBrownMechScoring);
    }
    else{
      f9loop = true;
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

    //bonk
    if (con.ButtonB.pressing()){
      if (f5loop){
        bonk.open();
      }
      if (!f5loop){
        bonk.close();
      }
      f6loop = true;
    }
    else if (f6loop){
      f5loop = !f5loop;
      f6loop = false;
    }

    //intakelift
    if (con.ButtonDown.pressing()){
      if (f7loop){
        intakeLift.open();
      }
      if (!f7loop){
        intakeLift.close();
      }
      f8loop = true;
    }
    else if (f8loop){
      f7loop = !f7loop;
      f8loop = false;
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
