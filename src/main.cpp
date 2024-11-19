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
bool f2loop = true;
bool f3loop = true;
bool f4loop = true;
bool f5loop = true;
bool f6loop = true;
bool f7loop = true;
bool f8loop = true;
bool f9loop = true;
bool f10loop = true;

bool f12loop = true;
bool isRed = false;
bool reject = false;
bool shouldReject = true;
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
  while (shouldReject){
    //416
    //855
    //1258
    if (230 > Optical.hue() && Optical.hue() > 220 && isRed && Optical.isNearObject()){
      reject = true;
      wait(.1, sec);
      intake.stop();
      wait(.2, sec);
      reject = false;
      f4loop = true;
    }
    if (Optical.hue() < 10 && !isRed && Optical.isNearObject()){
      reject = true;
      wait(.1, sec);
      intake.stop();
      wait(.2, sec);
      reject = false;
      f4loop = true;
    }
  }
  return(0);
}
 int ladyBrownMechZero(){
  while(Rotation.position(deg)- 3 > 25){
    if (Rotation.position(deg)  > 350){
      lift.spin(fwd, 100,pct);
      lift2.spin(fwd, 100,pct);
    }
    else if (Rotation.position(deg) - 3 > 25){
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
  if (lbState == 1){
    while(Rotation.position(deg)- 5 > 38 or Rotation.position(deg) + 5 < 38 ){
      if (Rotation.position(deg) + 5 < 38){
        lift.spin(fwd, 70,pct);
        lift2.spin(fwd, 70,pct);
      }
      else if (Rotation.position(deg) - 5 > 38){
        lift.spin(fwd, -70,pct);
        lift2.spin(fwd, -70,pct);
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
  //   while(Rotation.position(deg)- 3 > 47 or Rotation.position(deg) + 3 < 47 ){
  //     if (Rotation.position(deg) + 3 < 47){
  //       lift.spin(fwd, 70,pct);
  //       lift2.spin(fwd, 70,pct);
  //     }
  //     else if (Rotation.position(deg) - 3 > 47){
  //       lift.spin(fwd, -70,pct);
  //       lift2.spin(fwd, -70,pct);
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
    while(Rotation.position(deg) - 3 > 157.5 or Rotation.position(deg) + 3 < 157.5){
      if (Rotation.position(deg) + 3 < 157.5){
        lift.spin(fwd, 100,pct);
        lift2.spin(fwd, 100,pct);
      }
      else if (Rotation.position(deg) - 3 > 157.5){
        lift.spin(fwd, -100,pct);
        lift2.spin(fwd, -100,pct);
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
    while(Rotation.position(deg) - 3 > 70 or Rotation.position(deg) + 3 < 70){
      if (Rotation.position(deg) + 3 < 70){
        lift.spin(fwd, 80,pct);
        lift2.spin(fwd, 80,pct);
      }
      else if (Rotation.position(deg) - 3 > 70 ){
        lift.spin(fwd, -100,pct);
        lift2.spin(fwd, -100,pct);
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

void AWPNegBlue(){
  clamp.open();
  Drive.swing(-25, 100, -60, 1);
  Drive.moveDistance(-5, 100, .5);
  clamp.close();
  Drive.turn(-90, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(28, 20, 2);
  Drive.moveDistance(-11, 100, .7);
  Drive.turn(-180, 100, .7);
  Drive.moveDistance(16, 70, .9);
  Drive.moveDistance(-15, 100, .8);
  Drive.turn(-158, 100, .5);
  Drive.moveDistance(16, 100, .8);
  Drive.moveDistance(-18, 100, 1);
  Drive.turn(-270, 100, .8);
  Drive.moveDistance(30, 70, 1.2);

}

void AWPNegRed(){
  clamp.open();
  Drive.swing(-25, 100, 60, 1);
  Drive.moveDistance(-5, 100, .5);
  clamp.close();
  Drive.turn(90, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(26, 20, 2);
  Drive.moveDistance(-9, 100, .7);
  Drive.turn(180, 100, .7);
  Drive.moveDistance(15, 100, .9);
  Drive.moveDistance(-14, 100, .8);
  Drive.turn(155, 100, .8);
  Drive.moveDistance(11, 100, .8);
  Drive.moveDistance(-16, 100, 1);
  Drive.turn(270, 100, .8);
  Drive.moveDistance(23, 70, 1.2);

}
int fasterClamping(){
  wait(.65, sec);
  clamp.open();
  return(0);
}
int fasterClamping2(){
  wait(.85, sec);
  clamp.open();
  return(0);
}
void AWPPosBlue(){
  Drive.swing(-15.5, 100, 90, .9);
  Drive.moveDistance(-5, 100, .4);
  intake.spin(fwd,100,pct);
  wait(.8,sec);
  Drive.turn(150, 100,.7);
  Drive.swing(20,100,30,1);
  Drive.turn(20, 100, .7);
  Drive.moveDistance(45, 100, 1);
  Drive.turn(-45, 100, .5);
  intake.spin(fwd, -100, pct);
  wait(.4, sec);
  intake.stop();
  clamp.open();
  Drive.moveDistance(-12, 50, 1);
  clamp.close();
  intake.spin(fwd,100,pct);
  Drive.moveDistance(-6, 100, .5);
  Drive.turn(0,100,.8);
  wait(.6, sec);
  clamp.open();
  Drive.moveDistance(32,100, 1.2);
  intake.stop();
  Drive.turn(-90, 100, .7);
  Drive.moveDistance(-9, 100, .6);
  Drive.turn(-60, 100, .5);
  Drive.moveDistance(-9.2, 30, 1);
  clamp.close();
  Drive.turn(-180, 100, .8);
  Drive.moveDistance(12, 100, .8);

}

void simpleAWPposBlue(){
  clamp.open();
  Drive.swing(-25, 100, 60, 1);
  Drive.moveDistance(-5, 100, .5);
  clamp.close();
  Drive.turn(90, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(26, 20, 2);
  intake.stop();
  Drive.turn(0, 100, .7);
  Drive.moveDistance(-9, 100, .6);
  Drive.turn(30, 100, .5);
  Drive.moveDistance(-9.2, 30, 1);
  clamp.close();
  Drive.turn(-90, 100, .8);
  Drive.moveDistance(18, 100, .8);
}

void AWPPosRed(){
  clamp.open();
  Drive.swing(-25, 100, -60, 1);
  Drive.moveDistance(-5, 100, .5);
  clamp.close();
  Drive.turn(-95, 100, .8);
  intake.spin(fwd, 100, pct);
  wait(.8, sec);
  clamp.open();
  Drive.moveDistance(30, 20, 2);
  intake.stop();
  wait(.2, sec);
  Drive.turn(0, 100, .7);
  Drive.moveDistance(-13, 100, .9);
  intake.stop();
  Drive.turn(-20, 100, .5);
  Drive.moveDistance(-4, 40, .5);
  clamp.close();
  intake.spin(fwd, 100, pct);


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
void blueMOGORush(){
  isRed = false;
  task onlyBlues = task(colorReject);
  Drive.moveDistance(-33, 100, 1.1);
  Drive.turn(36, 100, .6);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-11, 40, .8);
  intake.spin(fwd,100,pct);
  Drive.turn(-20, 100, .5);
  task clampReleaser = task(clampRelease);
  Drive.moveDistance(39, 100, 1);
  Drive.turn(35, 100, .6);
  task fastClamp2 = task(fasterClamping2);
  Drive.moveDistance(-24, 40, 1.4);
  Drive.moveDistance(3, 100, .3);
  intake.spin(fwd, 100, pct);
  intakeLift.open();
  Drive.turn(-60, 100, .7);
  Drive.moveDistance(30, 70, 1.1);
  intakeLift.close();
  Drive.moveDistance(-7, 100, .33);
  clamp.close();
  Drive.turn(-160, 100, .7);
  Drive.moveDistance(2, 100, .33);
  Drive.turn(-182, 100, .6);
  Drive.moveDistance(-8, 100, .6);
  intake.spin(fwd, 100, pct);
  // wait(.5, sec);
  // Drive.moveDistance(6, 100, .4);
  // Drive.turn(-320, 100, .7);
  // Drive.moveDistance(-32, 100, .8);
  // clamp.open();
  // wait(.15, sec);
  // Drive.turn(-465, 100, .8);
  // Drive.moveDistance(30, 100, .8);
  // Drive.turn(-525, 100, .5);
  // Drive.moveDistance(15, 100, .6);
  // Drive.moveDistance(-628, 100, .7);
  // Drive.moveDistance(20, 100, .6);

}
void bluePlus(){
  isRed = false;
  Drive.swing(-20, 100, 30, .7);
  clamp.open();
  wait(.15, sec);
  intake.spin(fwd, 100, pct);
  Drive.swing(37, 100, 77, 1.1);
  bonk.open();
  wait(.3, sec);
  Drive.moveDistance(5, 60, .6);
  Drive.turn(155, 100, .7);
  bonk.close();
  wait(.15, sec);
  Drive.swing(35, 30, 200, 1.7);
  clamp.close();
  intake.stop();
  Drive.moveDistance(19, 100, .7);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(37, 100, .8);
  Drive.moveDistance(-7, 100, .7);
  clamp.open();
  wait(.15, sec);
}

void bluePlusCorner(){
  bonk.open();
  wait(.2, sec);
  Drive.moveDistance(5, 100, .5);
  Drive.turn(70, 40, 1);
  Drive.turn(0, 100, .8);
  bonk.close();
  Drive.moveDistance(-10, 100, .6);
  Drive.turn(-60, 100, .6);
  Drive.moveDistance(-29,100, .8);
  clamp.open();
  wait(.15, sec);
  intake.spin(fwd, 100, pct);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(28, 40, 1.8);
  Drive.moveDistance(-9, 100, .4);
  wait(.3, sec);
  clamp.close();
  Drive.moveDistance(12, 100, .4);
  Drive.turn(-62, 100, .7);
  intake.stop();
  Drive.moveDistance(-13, 100, .7);
  clamp.open();
}
void testing(){
  Drive.moveDistance(10, 100, 13);
  Drive.turn(135,100, 2);
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
  wait(.3, sec);
  intake.stop();
  return(0);
}
void skills(){
  lift.stop(hold);
  lift2.stop(hold);
  intake.spin(fwd, 100, pct);
  wait(.65, sec);
  Drive.turn(35.5, 100, .4);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(43, 100, 1.1);
  task slowintake = task(intakeSlowStop);
  Drive.turn(-45, 100, .7);
  task waitintake = task(intakeWait);
  Drive.moveDistance(27, 100, .8);
  task slowintake2 = task(intakeSlowerStop);
  Drive.turn(40, 100, .6);
  Drive.swing(27 , 100, 0, .8);
  Drive.swing(31, 100, 90, 1);
  Drive.moveDistance(-13, 80, .7);
  clamp.open();
  wait(.15, sec);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(26, 100, .8);
  Drive.moveDistance(35, 20, 1.2);
}

int clamping(){
  wait(.65, sec);
  clamp.open();
  return(0);
}
int lastClamp(){
  wait(1.2, sec);
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
void simHitSkills(){
  Optical.setLightPower(100, pct);
  isRed = true;
  task onlyReds = task(colorReject);
  intake.spin(fwd,100,pct);
  wait(.45, sec);
  Drive.moveDistance(15, 100, .7);
  lbState=0;
  task state0 = task(ladyBrownMechZero);
  Drive.turn(-90,100, .6);
  task slowClamp = task(clamping);
  Drive.moveDistance(-23.5, 40, 1.1);
  Drive.turn(0, 100, .7);
  Drive.moveDistance(20, 100, .7);
  Drive.turn(28, 100, .6);
  task slowUp1 = task(slowUp);
  Drive.moveDistance(46, 80, 1.4);
  intake.spin(fwd,60,pct);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(180, 70, .8);
  task removeHook = task(hookRemove);
  wait(.2, sec);
  task waitIntake = task(intakeWait);
  Drive.moveDistance(12.1, 100, .7);
  Drive.turn(90, 100, .7);
  Drive.moveDistance(11, 70, .7);
  lbState = 2;
  task ringScore1 = task(ladyBrownMechScoring);
  Drive.turn(90, 30, .3);
  Drive.moveDistance(1000, 100, .5);
  Drive.turn(90, 100, .4);
  Drive.moveDistance(-12, 100, .8);
  task saveTheLady = task(ladyBrownMechZero);
  Drive.turn(180, 100, .8);
  Drive.moveDistance(36, 70, 1.1);
  Drive.moveDistance(33, 20, 1.9);
  Inertial.setRotation(180, deg);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(50, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(16, 70, .9);
  Drive.turn(-17, 70, .6);
  Drive.moveDistance(-15, 100, .6);
  wait(.5, sec);
  clamp.close();
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-51, 100, .6);
  task superMarioBrosSlow = task(intakeSlowerStop);
  Drive.moveDistance(40, 100, 1);
  Drive.turn(-51, 100, .2);
  task saveTheCaptain = task(hookSaver);
  Drive.moveDistance(33, 100, .9);
  Drive.turn(-135, 100, .7);
  task slowStartViolation = task(intakeShortWait);
  task slowEndViolation = task(intakePause);
  Drive.moveDistance(47, 100, 1.2);
  Drive.turn(-37, 100, .7);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-15, 50, .8);
  task onOff = task(intakeOnOff);
  Drive.turn(-49, 100, .4);
  wait(.7, sec);
  Drive.moveDistance(33 , 45 , 1.3);
  Drive.turn(-180, 100, .9);
  Drive.moveDistance(23, 30, 1.5);
  Drive.moveDistance(12, 30, 1.1);
  Inertial.setRotation(-180, deg);
  Drive.turn(-55, 100, .7);
  Drive.moveDistance(16, 70, .7);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(-8, 100, .6);
  clamp.close();
  Drive.turn(0, 100, .5);
  // //28.4 seconds on 11/16/24 // 34.75 on 11/17/24
  lbState = 1;
  task ladyLift = task(ladyBrownMechScoring);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(54, 70, 1.7);
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
  Drive.turn(-90, 100, .6);
  wait(.4, sec);
  lbState = 2;
  task ladyStake2 = task(ladyBrownMechScoring);

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
  Drive.turn(7, 100, .7);
  lbState = 1;
  task ladyLiftYes = task(ladyBrownMechScoring);
  Drive.moveDistance(47, 100, 1.3);
  Drive.turn(0, 100, .3);
  Drive.moveDistance(17, 100, .7);
  Inertial.setRotation(0, deg);
  Drive.moveDistance(-3, 100, .3);
  Drive.turn(-90, 100, .8);
  Drive.moveDistance(-8, 40, .6);
  clamp.open();
  Drive.swing(40, 100, -225, 1.4);
  Drive.moveDistance(-6, 100, .5);
  clamp.close();
  Drive.turn(180, 100, .55);
  Drive.moveDistance(7, 100, .4);

  //52.85 11/17/24



  
}

void simHitSkillsTimeOpt(){
  isRed = true;
  task onlyReds = task(colorReject);
  intake.spin(fwd,100,pct);
  wait(.45, sec);
  Drive.moveDistance(15, 100, .7);
  lbState=0;
  task state0 = task(ladyBrownMechZero);
  Drive.turn(-90,100, .6);
  task slowClamp = task(clamping);
  Drive.moveDistance(-23.5, 40, 1);//-.1
  Drive.turn(0, 100, .6);//-.1
  Drive.moveDistance(20, 100, .7);
  Drive.turn(28, 100, .5);//-.1
  task slowUp1 = task(slowUp);
  Drive.moveDistance(46, 80, 1.4);
  intake.spin(fwd,60,pct);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(180, 70, .75);//-.05
  task removeHook = task(hookRemove);
  //-.2
  task waitIntake = task(intakeWaitTimeOpt);
  Drive.moveDistance(13.1, 100, .6);//-.1
  Drive.turn(90, 100, .6);//-.1
  Drive.moveDistance(11, 70, .6);//-.1
  lbState = 3;
  task ringScore1 = task(ladyBrownMechScoring);
  Drive.turn(90, 30, .3);
  Drive.moveDistance(1000, 100, .3);//-.2
  Drive.turn(90, 100, .4);
  Drive.moveDistance(-12, 100, .8);
  task saveTheLady = task(ladyBrownMechZero);
  Drive.turn(180, 100, .6);//-.2
  Drive.moveDistance(36, 70, 1);//-.1
  Drive.moveDistance(30, 20, 1.6);//-.3 and sped up 13%
  Inertial.setRotation(180, deg);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(50, 100, .7);
  Drive.moveDistance(16, 70, .9);
  Drive.turn(-17, 70, .5);//-.1
  Drive.moveDistance(-15, 100, .6);
  wait(.4, sec);//-.1
  clamp.close();
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-51, 100, .4);//-.2
  task superMarioBrosSlow = task(intakeSlowerStop);
  Drive.moveDistance(40, 100, 1);
  Drive.turn(-51, 100, .2);
  task saveTheCaptain = task(hookSaver);
  Drive.moveDistance(33, 100, .9);
  Drive.turn(-135, 100, .7);
  task slowStartViolation = task(intakeShortWait);
  task slowEndViolation = task(intakePause);
  Drive.moveDistance(47, 100, 1.2);
  Drive.turn(-37, 100, .7);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-15, 50, .8);
  task onOff = task(intakeOnOff);
  Drive.turn(-51, 100, .5);
  //-.7
  Drive.moveDistance(31 , 45 , 1.1);//-.2
  Drive.turn(-180, 100, .7);//-.2
  Drive.moveDistance(23, 30, 1.3);//-.2
  Drive.moveDistance(17, 35, .9);//-.2 sped up 5%
  Inertial.setRotation(-180, deg);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(-55, 100, .7);
  Drive.moveDistance(16, 70, .7);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(-8, 100, .5);//-.1
  clamp.close();
  Drive.turn(0, 100, .4);//-.1
  //-4.35 = 30.3
  // //28.4 seconds on 11/16/24 // 34.65 on 11/17/24
  lbState = 1;
  task ladyLift = task(ladyBrownMechScoring);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(50, 70, 1.4);//-.3
  Drive.turn(28, 100, .4);
  wait(.4, sec);
  task removeIntakeHook = task(hookRemoved);
  task pauseIntake = task(intakeWait70);
  wait(.3, sec);
  Drive.moveDistance(28, 50, 1);//-.3
  Drive.turn(0, 100, .4);//-.1
  task removeIntakeHooked = task(hookRemoved);
  Drive.moveDistance(-24.3, 70, 1);
  Drive.turn(-90, 100, .6);
  task dosSteaksPorFavor = task(stake2);
  Drive.moveDistance(20, 70, .7);
  wait(.2, sec);//-.2
  Drive.moveDistance(-20, 100, .9);//-.1
  intake.spin(fwd, 70, pct);
  Drive.turn(45, 100, .6);
  lbState = 1;
  task lady1 = task(ladyBrownMechScoring);
  Drive.moveDistance(36, 70, 1);//-.1
  task wallStake2 = task(hookRemoved);
  Drive.turn(-50, 100, .6);//-.1
  task pauseIntakeBlue = task(intakeWait70);
  Drive.moveDistance(29, 60, 1);//-.1
  //-.3
  Drive.turn(-180, 100, .8);//-.1
  Drive.moveDistance(43, 100, 1);
  task removeIntakeHookedQuattro = task(hookRemove);
  Drive.turn(-90, 100, .6);
  lbState = 3;
  task audiQuattro = task(ladyBrownMechScoring);
  Drive.moveDistance(30, 100, .8);
  Drive.moveDistance(-17, 100, 1);
  Drive.turn(9, 100, .7);
  Drive.moveDistance(60, 100, 1.4);
  Inertial.setRotation(0, deg);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(-90, 100, .8);
  Drive.moveDistance(-8, 40, .6);
  clamp.open();
  Drive.moveDistance(34, 100, .9);
  Drive.turn(-225, 100, .9);
  clamp.close();
  Drive.moveDistance(-100, 100, .4);
  Drive.turn(-180, 100, .5);
  Drive.moveDistance(11, 100, .8);
  Drive.turn(-90, 100, .6);
  task lastMOGO = task(lastClamp);
  Drive.moveDistance(-60, 100, 1.4);
  Drive.turn(-225, 100, .8);
 
  //-6.05 = 46.7
  //52.75 11/17/24

}
void testing2(){
  Drive.moveDistance(10, 100, 1);
  Drive.turn(180, 100, 1);
  Drive.moveDistance(10, 100, 1);
  Drive.turn(360, 100, 1);
  Drive.moveDistance(10, 100, 1);
  Drive.turn(540, 100, 1);
  Drive.moveDistance(10, 100, 1);
  Drive.turn(720, 100, 1);
  Drive.moveDistance(10, 100, 1);
  Drive.turn(900, 100, 1);
  Drive.moveDistance(10, 100, 1);
  Drive.turn(1080, 100, 1);

}
int AWPInt(){
  intake.spin(fwd, 40, pct);
  wait(.7, sec);
  intake.stop();
  return(0);
}
void AWPPusher(){
  Optical.setLightPower(100,pct);
  isRed = false;
  task sorting = task(colorReject);
  task AWP = task(AWPInt);
  Drive.moveDistance(-12, 30, 1.5);
  Drive.turn(90, 70, .9);
  Drive.moveDistance(-6.2, 100, .6);
  intake.spin(fwd, 100, pct);
  wait(.6, sec);
  Drive.moveDistance(3, 100, .4);
  Drive.turn(130, 100, .6);
  Drive.moveDistance(12, 70, 1.1);
  intake.stop();
  Drive.turn(150, 100, .4);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(37, 100, 1);
  intake.stop();
  
}
void (*autonsList[])() =
{
  simHitSkills,
  blueMOGORush,
  bluePlusCorner,
  bluePlus,
  AWPPusher,
  simHitSkillsTimeOpt,
  testing2, 
  skills,
  testing,
  blueMOGORush,
  // simpleAWPposBlue,
  // AWPPosBlue,
  // AWPPosRed,
  // AWPNegBlue,
  // skills,
  // AWPNegRed,
  
  

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
  Optical.setLightPower(100, percent);
  isRed = true;
  task printcon = task(conInfo);
  task cReject = task(colorReject);
  while (true)
  {
    // con.Screen.clearScreen();
    // con.Screen.setCursor(1,1);
    // con.Screen.print(Inertial.rotation(deg));
    if (!shouldReject){
      con.rumble("..--..--");
    }
  

    if (con.ButtonA.pressing() && f12loop){
      shouldReject = !shouldReject;
      f12loop = false;
    }
    else{
      f12loop = true;
    }
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
      task ladyBrownZero = task(ladyBrownMechZero);
      lbState = 0;
    }
    else if (con.ButtonL1.pressing()){
      if (f9loop){
        lbState += 1;
        f9loop = false;
      }
      if (lbState == 3){
        lbState = 1;
      }
      task ladyBrownIntake = task(ladyBrownMechScoring);
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
