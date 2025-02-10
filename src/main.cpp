
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
bool isRed = true;
bool reject = false;
bool shouldReject = true;
bool rejectStart = false;
bool holdRing = false;
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

int ladyBrownMechScoring(){
  double lbkP = 1.2;
  double lbkD = .3;
  double lbSpeed;

  if (lbState == 0){
    while(Rotation.position(deg)- .2 > 27){
      lbSpeed = lbkP * (27-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg)  > 350){
        lift.spin(fwd, lbSpeed,pct);
        lift2.spin(fwd, lbSpeed,pct);
      }
      else if (Rotation.position(deg) - .2 > 27){
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
int colorReject(){
  double rejectkP = 7;
  double rejectkD = 0;
  double rejectAng = 47;
  bool lbBack = false;
  while (shouldReject){
    
    if (235 > Optical.hue() && Optical.hue() > 225 && isRed){
      if (lbState == 1){
        lbBack = true;
        lbState = 2;
        task deflection = task(ladyBrownMechScoring);
      }
      reject = true;
      double initPos = intake.position(deg);
      double target = rejectAng+initPos;
      double rejSpeed;
      while (reject){
        double currPos = intake.position(deg);
        double error = target - currPos;
        rejSpeed = error * rejectkP - rejectkD * rejSpeed;
        intake.spin(fwd, rejSpeed, pct);

        if (currPos>target or currPos+2>target){
          intake.spin(fwd, -50, pct);
          wait(.2, sec);
          intake.stop();
          reject = false;
          wait(.1, sec);
          if (lbBack) {
            lbState = 1;
            task reflection = task(ladyBrownMechScoring);
            lbBack = false;
          }
        }
      }
      
    }
    if (Optical.hue() < 10 && !isRed && Optical.isNearObject()){
      if (lbState == 1){
        lbBack = true;
        lbState = 2;
        task deflection = task(ladyBrownMechScoring);
      }
      reject = true;
      double initPos = intake.position(deg);
      double target = rejectAng+initPos;
      double rejSpeed;
      while (reject){
        double currPos = intake.position(deg);
        double error = target - currPos;
        rejSpeed = error * rejectkP - rejectkD * rejSpeed;
        intake.spin(fwd, rejSpeed, pct);

        if (currPos>target or currPos+2>target){
          intake.spin(fwd, -50, pct);
          wait(.2, sec);
          intake.stop();
          reject = false;
          wait(.1, sec);
          if (lbBack) {
            lbState = 1;
            task reflection = task(ladyBrownMechScoring);
            lbBack = false;
          }
        }
      }
    }
  }
  return(0);
}
int antiJam(){
  while (!(lbState == 1)){
    if (intake.current() > 20 && intake.velocity(pct) < 1){
      reject = true;
      intake.spin(fwd, -100, pct);
      wait(.2, sec);
      intake.stop();
      reject = false;
    }

  }
  return(0);
}


void pre_auton(void) {
  //calibrate inertial sensor
  rightDrive_Group.resetPosition();
  leftDrive_Group.resetPosition();
  Inertial.calibrate(3);
  Brain.Screen.clearScreen();
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("1=Solo Sig, 2=SoloSigRush");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("3=SimpleRedNeg, 4=SimpleREDPos");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("5=SimpleBlueNeg, 6=SimpleBluePos");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("7=DualRingRushRed, 8=InsideRingRushRed");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("9=NoRushNegRed, 10=DualRingRushBlue");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("11=InsideRingRushBlue, 12=NoRushNegBlue");
  // while (true){
  //   if (Brain.Screen.pressing() && f10loop){
  //     f10loop = false;
  //     if (autoSelect == 9){
  //       autoSelect = -1;
  //     }
  //     autoSelect += 1;
  //     Brain.Screen.setCursor(1,1);
  //     Brain.Screen.clearLine();
  //     Brain.Screen.print("Auto", autoSelect);
  //   }
  //   else {
  //     f10loop = true;
  //   }
  // }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


int bonky(){
  wait(.8, sec);
  bonk.open();
  return(0);
}
int clampOnebRB(){
  wait(.9, sec);
  clamp.open();
  return(0);
}
void mogoRushBlue(){
  task bonkers = task(bonky);
  Drive.swing(38, 100, -6, .89);
  Drive.moveDistance(-10, 100, .55);
  
  bonk.close();
  wait(.05, sec);
  Drive.moveDistance(-12, 100, .6);
  Drive.turn(-58, 100, .5);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(23, 100, .85);
  intake.stop();
  Drive.turn(-130, 100, .7);
  task firstClamp = task(clampOnebRB);
  Drive.moveDistance(-14, 100, .75);
  intake.spin(fwd, 100, pct);
  // Drive.turn(-65, 100, .6);
  // Drive.swing(20, 100, -90, .8);
  // lbState = 4;
  // task setLB2 = task(ladyBrownMechScoring);

}
int bonkyRing(){
  wait(.62, sec);
  bonk.open();
  return(0);
}
int intStopRingRush(){
  wait(.4, sec);
  intake.stop();
  return(0);
}
int clampRingRush(){
  wait(.43, sec);
  bonk.close();
  clamp.open();
  return(0);
}
// int bonkCloseRR(){
//   wait(.7, sec);
//   bonk.close();
//   return(0);
// }
void ringRushBlue3(){
  isRed = false;
  shouldReject = true;
  task cReject = task(colorReject);
  task bonkers = task(bonkyRing);
  intake.spin(fwd,100, pct);
  Drive.swing(40, 100, -27, 1);
  Drive.moveDistance(4, 100, .4);
 
  task iStop = task(intStopRingRush);
  Drive.moveDistance(-12, 100, .7);
  Drive.turn(20, 100, .5);
  Drive.swing(-29.5, 60, 119, 1.3);
  Drive.swing(-11, 50, 150, .7);
  task C1 = task(clampRingRush);
  Drive.moveDistance(-8, 70, .55);
  bonk.close();
  intake.spin(fwd, 100, pct);
  Drive.swing(15, 60, 18, 1);
  Drive.swing(19.5, 100, 49, .8);
  lbState = 1;
  task setLB = task(ladyBrownMechScoring);
  intake.spin(fwd, 80, pct);
  Drive.swing(20.5, 70, 43, 1.1);
  intake.stop();
  wait(.05,sec);
  lbState = 4;
  task scoreLB = task(ladyBrownMechScoring);
  Drive.moveDistance(3, 50, .5);
  intake.spin(fwd, 100, pct);
  Drive.swing(-13, 70, 162.5, 1);
  bonk.open();
  intake.spin(fwd, 100,pct);
  Drive.swing(38, 100, 180, 1.1);
  Drive.turn(260, 100, .7);
  bonk.close();
  Drive.turn(150, 100, .75);
  Drive.swing(13, 100, 270, 1.1);
  Drive.moveDistance(15, 70, 1);



  

}
void test(){
  Drive.turn(-15, 100, .6);
  Drive.swing(35, 100, 0, 1);
  lbState = 4;
  task setLB = task(ladyBrownMechScoring);
}
int clampAWPB(){
  wait(.3, sec);
  clamp.open();
  return(0);

}

int slowInt(){
  wait(.8, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int stopInt(){
  wait(.3, sec);
  intake.stop();
  return(0);
}

int dropIntLift(){
  wait(1.1, sec);
  intakeLift.close();
  return(0);
}
 void simpleAWPposBlue(){
  Optical.setLightPower(10, pct);
  isRed= false;
  shouldReject = true;
  task cReject = task(colorReject);
  Drive.swing(-25, 80, 60, 1);
  Drive.moveDistance(-5, 80, .5);
  clamp.open();
  Drive.turn(90, 80, .7);
  intake.spin(fwd, 90, pct);
  Drive.moveDistance(20, 80, 1.2);
  // Drive.turn(0, 100, .7);
  // Drive.moveDistance(-9, 100, .6);
  // Drive.turn(30, 100, .5);
  // Drive.moveDistance(-9.2, 30, 1);
  // clamp.close();
  // Drive.turn(-90, 100, .8);
  // Drive.moveDistance(18, 100, .8);

  Drive.turn(-55, 80, 1);
  clamp.close();
  // intakeLift.open();
  // task intDelay = task(slowInt);
  // task dropInt = task(dropIntLift);
  // Drive.moveDistance(60, 80, 1.4);
  // task intakeDelay = task(stopInt);
  // Drive.turn(-110, 100, .8);
  // Drive.moveDistance(-12.1, 100, 1);
  // Drive.turn(-180, 100, .6);
  // Drive.moveDistance(-7, 100, .5);
  // intake.spin(fwd,100, pct);
  // Drive.moveDistance(.5, 100, .2);
  // wait(.5, sec);
  // Drive.moveDistance(4, 100, .3);
  // Drive.turn(-120, 100, .6);
  // Drive.moveDistance(55, 100, 1.5);

  Drive.swing(60, 100, 0, 1.3);
  lbState = 4;
  task scoreLB = task(ladyBrownMechScoring);

 }
int clampBWP(){
  wait(.7, sec);
  clamp.open();
  return(0);

}
// void blueWP(){
//   isRed= false;
//   shouldReject = true;
//   task cReject = task(colorReject);
//   intake.spin(fwd, -100, pct);
//   Drive.moveDistance(11.5, 50, .8);
//   Drive.turn(90, 40, .8);
//   Drive.moveDistance(-.4, 40, .4);
//   lbState = 4;
//   task scoreLB = task(ladyBrownMechScoring);
//   wait(.7, sec);
//   lbState = 0;
//   task lower = task(ladyBrownMechScoring);
//   Drive.swing(-7, 100, 40, .8);
//   task C1 = task(clampBWP);
//   Drive.swing(-37, 100, 63, 1.1);
//   Drive.turn(180, 100, .7);
//   intake.spin(fwd, 100, pct);
//   Drive.moveDistance(23, 100, .8);

  
// }
int sigAWPClamping(){
  wait(.6 , sec);
  clamp.open();
  return(0);
}
int sigAWPClamping2(){
  wait(.85 , sec);
  clamp.open();

  return(0);
}

int stopIntBSAWP(){
  intake.spin(fwd, 100, pct);
  wait(1.4, sec);
  intake.spin(fwd, -100, pct);
  return(0);
}

int intContAWP(){
  while (!Optical.isNearObject()){
    intake.spin(fwd, 60, pct);
  }
  intake.stop();
  return(0);
}
int intCont2AWP(){
  while (!Optical.isNearObject()){
    intake.spin(fwd, 50, pct);
  }
  intake.stop();
  return(0);
}
void soloSig(){
  Drive.swing(-12, 100, -90, .8);
  Drive.moveDistance(-5, 50, .5);
  Drive.moveDistance(1.7, 100, .4); // 2.35 for metal field

  intake.spin(fwd, 100, pct);
  wait(.4, sec);
  Drive.swing(12, 100, -165, .8);
  lbState = 3;
  task score = task (ladyBrownMechScoring);
  Drive.moveDistance(34, 100, 1);
  task stoppers = task(intCont2AWP);
  Drive.turn(-236, 100, .65);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-20, 45, .9);
  Drive.turn(-185, 100, .5);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(29, 90, .9);
  intake.stop();
  Drive.turn(19, 90, 1.1);

  task longDriveIntCont = task(stopIntBSAWP);
  Drive.moveDistance(76, 100, 1.7);
  Drive.turn(-42, 100, .75);
  clamp.close();
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(43 , 100, 1.1);
  task intCont = task(intContAWP);
  Drive.turn(0, 100, .53);
  task clamp2 = task(sigAWPClamping2);
  Drive.moveDistance(-30, 45, 1.1 );
  lbState = 0;
  task score2 = task (ladyBrownMechScoring);
  Drive.turn(-120, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(6, 100, .5);

}


int clampRPE(){
  wait(.25, sec);
  bonk.open();
  return(0);
}
int intStopRPE(){
  wait(.6, sec);
  intake.stop();
  return(0);
}
int clampTwoRPE(){
  wait(.85, sec);
  clamp.open();
  return(0);
}
void redPosElim(){
  task bonkers = task(bonky);
  Drive.swing(36, 100, -10, .89);
  Drive.moveDistance(-7, 100, .55);
  
  bonk.close();
  wait(.2, sec);
  Drive.moveDistance(-13, 100, .7);
  Drive.turn(-52, 100, .5);
  intake.spin(fwd, 100, pct);
  task intCont = task(intStopRPE);
  Drive.moveDistance(27.5, 100, 1);
  Drive.moveDistance(-9, 100, .6);
  Drive.turn(90, 100, .7);
  task firstClamp = task(clampOnebRB);
  Drive.moveDistance(-23, 50, 1.1);
  Drive.moveDistance(3, 100,.3);
  intake.spin(fwd, 100, pct);
  wait(.45, sec);
  intake.stop();
  Drive.turn(105, 100, .7);
  clamp.close();
  Drive.moveDistance(36, 100, 1.2);
  Drive.turn(173, 100, .8);
  Drive.moveDistance(-13 , 70, .65);
  task clamp2 = task(clampTwoRPE);
  Drive.turn(150, 100, .4);
  Drive.moveDistance(-7, 40, .6);
  intake.spin(fwd, 100, pct);
  Drive.turn(180, 100, .7);


} 

int testClamp(){
  wait(.53, sec);
  clamp.open();
  return(0);
}
int testClamp2(){
  wait(.65, sec);
  clamp.open();
  return(0);
}



int dropInt(){
  wait(.7, sec);
  intakeLift.close();
  return(0);
}


void simAuto(){	
  intake.spin(fwd,100, pct);
  Drive.moveDistance( 21.647887323669252 , 100 , .9 );	
  intake.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .5 );	
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -17.15492957724733 , 100 , .85 );	
  Drive.turn( 232.14743605677376 , 100 , .9 );
  intake.spin(fwd, 100, pct);
  intakeLift.open();
  task contInt = task(dropInt);	
  Drive.moveDistance( 33.492957746054316 , 100 , 1 );	
  clamp.close();
  intake.stop();	
  Drive.turn( 258 , 100 , .4 );	
  Drive.moveDistance( 22.873239436329776 , 100 , .9 );	
  Drive.turn( 90 , 100 , .9 );	
  Drive.moveDistance( 18.380281689907854 , 100 , .9 );	
  Drive.turn( 0 , 100 , 1.00000009 );	
  Drive.moveDistance( -5.309859154862269 , 100 , .9 );	
  intake.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.moveDistance( 5.309859154862269 , 100 , .9 );
  Drive.turn( 128 , 100 , .8 );	
  Drive.moveDistance( -18.380281689907854 , 100 , 1.1 );	
  Drive.turn( 145 , 100 , .9 );	
  task C2 = task(testClamp2);
  Drive.moveDistance( -10.619718309724538 , 100 , 1.1 );	
  Drive.turn( -78.54593116361525 , 100 , 1.00000009 );	
  intake.spin(fwd, 100, pct);
  Drive.moveDistance( 22.056338027889428 , 100 , .9 );	}

void simAuto2(){	
  intake.spin(fwd,100, pct);
  Drive.moveDistance( 21.647887323669252 , 100 , .9 );	
  intake.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .9 );	
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -17.15492957724733 , 100 , .85 );	
  Drive.turn( 232.14743605677376 , 100 , .9 );	
  intake.spin(fwd, 100, pct);
  intakeLift.open();
  task contInt = task(dropInt);
  Drive.moveDistance( 33.492957746054316 , 100 , 1 );	
  clamp.close();
  intake.stop();
  Drive.turn( -68.11626120840089+360 , 100 , 1.00000009 );	
  intake.spin(fwd, 100, pct);
  Drive.moveDistance( 50.239436619081474 , 100 , 1.4 );	
  intake.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .8 );	
  Drive.turn( -90+360 , 100 , .5 );	
  task C2 = task(testClamp2);
  Drive.moveDistance( -17.15492957724733 , 100 , .8 );	
  intake.spin(fwd, 100, pct);
  }

int slowIntBNE(){
  wait(.5, sec);
  intake.spin(fwd, 100, pct);
  wait(.4, sec);
  intake.stop();
  return(0);
}

int lbDelayBNE(){
  wait(.2, sec);
  intake.spin(fwd, -100, pct);
  wait(.2,sec);
  intake.stop();
  lbState= 4;
  task score = task (ladyBrownMechScoring);
  wait(.5, sec);
  return(0);
}

int stopRingBNE(){
  while (holdRing){
    if (235 > Optical.hue() && Optical.hue() > 225){
      intake.stop();
      return(0);
    }

  }
  return(0);
}
int conIntake2RNE(){
  wait(1.5, sec);
  intake.stop();
  return(0);
}

//DONE CLEARS POSTIVE CORNER
void blueNegElim(){
  // Optical.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = false;
  // task cReject = task(colorReject);
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 26.3 , 60 , 1.1);	
  intake.stop();
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -20.15492957724733 , 70 , 1 );	
  Drive.moveDistance(3,100, .3);
  intake.spin(fwd, 100, pct);
  wait(.1, sec);
  Drive.turn(35, 100, .67);
  Drive.moveDistance(17.16, 100, .8);
  lbState = 1; 
  task up = task(ladyBrownMechScoring);
  Drive.moveDistance(-24.5, 100, .93);
  // Drive.turn(62, 100, .35);
  // Drive.swing(37.5, 100, 53, 1.2);
  // task lbDelay = task(lbDelayBNE);
  // Drive.moveDistance(5.3, 100, 1);
  Drive.turn(70, 100, .38);
  Drive.swing(28.5, 100, 49, 1.2);
  task lbDelay = task(lbDelayBNE);
  Drive.moveDistance(13.4, 100, 1);


  Drive.moveDistance(-53, 100, 1.25);
  // lbState = 0; 
  // task down = task(ladyBrownMechScoring);
  Drive.turn(-90, 100, .8);
  clamp.close();
  task intCont2 = task(conIntake2RNE);
  intakeLift.open();
  intake.spin(fwd, 100, pct);
  task intCont3 = task(intContAWP);
  Drive.moveDistance(28, 100, .9);
  intakeLift.close();

  Drive.turn(-60, 100, .4);
  
  Drive.moveDistance(-16, 100, .8);
  Drive.moveDistance(1.2, 100, .3);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(-4.55, 100, .4);
  intake.spin(fwd, 100, pct);


  // Drive.moveDistance(63,100, 1.6);
  // intakeLift.close();
  // Drive.turn(-180, 100, .7);
  // intake.spin(fwd, 100, pct);
  // Drive.swing(17, 100, -90, .9);
  // Drive.turn(-93, 100, .2);
  // bonk.open();
  // Drive.moveDistance(14, 100, .75);
  // Drive.turn(45, 100, .9);
  // Drive.moveDistance(5, 100, .4);
  



}
int conIntake3RNE(){
  wait(.6, sec);
  intake.stop();
  return(0);
}
int RNEC1(){
  wait(.47, sec);
  clamp.open();
  return(0);
}
void redNegElim(){
  // Optical.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = false;
  // task cReject = task(colorReject);
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake.stop();
  Drive.turn(-90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -19.15492957724733 , 70 , .95 );	
  Drive.moveDistance(2,100, .25);
  intake.spin(fwd, 100, pct);
  wait(.1, sec);
  Drive.turn(-35, 100, .67);
  wait(.05, sec);
  Drive.moveDistance(17.16, 100, .8);
  lbState = 1; 
  task up = task(ladyBrownMechScoring);
  Drive.moveDistance(-25, 100, .93);
  Drive.turn(-65, 100, .35);
  Drive.swing(35, 100, -49, 1.2);
  task lbDelay = task(lbDelayBNE);
  Drive.moveDistance(6.7, 100, 1);
  Drive.moveDistance(-53, 100, 1.25);
  lbState = 0; 
  task down = task(ladyBrownMechScoring);
  Drive.turn(85, 100, .8);
  clamp.close();
  intakeLift.open();
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(9,60, .9);
  intakeLift.close();
  intake.spin(fwd, 100, pct);
  task intCont2 = task(conIntake3RNE);
  Drive.turn(45, 100, .55);
  Drive.moveDistance(-14.5, 100, .7);
  Drive.turn(-90, 100, .9);
  Drive.swing(-12, 100, 0, .9);
  Drive.moveDistance(.2, 100, .1); 
  intake.spin(fwd, 100, pct);



}
void redNegElimKALA(){
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 26.3 , 60 , 1.1);	
  intake.stop();
  Drive.turn( -90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -20.15492957724733 , 70 , 1 );	
  Drive.moveDistance(3,100, .3);
  intake.spin(fwd, 100, pct);
  wait(.1, sec);
  Drive.turn(-35, 100, .67);
  Drive.moveDistance(17.16, 100, .8);
  lbState = 1; 
  task up = task(ladyBrownMechScoring);
  Drive.moveDistance(-24.5, 100, .93);
  // Drive.turn(62, 100, .35);
  // Drive.swing(37.5, 100, 53, 1.2);
  // task lbDelay = task(lbDelayBNE);
  // Drive.moveDistance(5.3, 100, 1);
  Drive.turn(-70, 100, .38);
  Drive.swing(28.5, 100, -49, 1.2);
  task lbDelay = task(lbDelayBNE);
  Drive.moveDistance(13.4, 100, 1);


  Drive.moveDistance(-53, 100, 1.25);
  // lbState = 0; 
  // task down = task(ladyBrownMechScoring);
  Drive.turn(90, 100, .8);
  clamp.close();
  task intCont2 = task(conIntake2RNE);
  intakeLift.open();
  intake.spin(fwd, 100, pct);
  task intCont3 = task(intContAWP);
  Drive.moveDistance(28, 100, .9);
  intakeLift.close();

  Drive.turn(60, 100, .4);
  
  Drive.moveDistance(-16, 100, .8);
  Drive.moveDistance(1.2, 100, .3);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(-4.55, 100, .4);
  intake.spin(fwd, 100, pct);


  // Drive.moveDistance(63,100, 1.6);
  // intakeLift.close();
  // Drive.turn(-180, 100, .7);
  // intake.spin(fwd, 100, pct);
  // Drive.swing(17, 100, -90, .9);
  // Drive.turn(-93, 100, .2);
  // bonk.open();
  // Drive.moveDistance(14, 100, .75);
  // Drive.turn(45, 100, .9);
  // Drive.moveDistance(5, 100, .4);
}
int bonkers(){
  wait(.75, sec);
  bonk.open();
  return(0);
}
int clamp1BPE(){
  wait(.4, sec);
  clamp.open();
  return(0);
}
int clamp2BPE(){
  wait(1.2, sec);
  clamp.open();
  return(0);
}
int lbSet(){
  wait(.5, sec);
  intake.stop();
  return(0);
}
int openClampBPE(){
  wait(1, sec);
  clamp.close();
  return(0);
}
int intContBPE(){
  wait(.45, sec);
  intake.stop();
  return(0);
}
int intCont2BPE(){
  wait(.65, sec);
  intake.stop();
  return(0);
}

void bluePosElim(){
  // Optical.setLightPower(10, pct);
  // shouldReject = true;
  // isRed = false;
  task bonky = task(bonkers);
  Drive.swing(36.6, 100, -11, .95);
  Drive.moveDistance(-10, 100, .65);
  bonk.close();
  Drive.swing(8, 100, -50, .8);
  Drive.swing(-12.5, 100, -90, .9);
  task C1 = task(clamp1BPE);
  Drive.moveDistance(-7, 45, .6);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(27, 100, .9);
  task I1 = task(intContBPE);
  Drive.moveDistance(-11.2, 100, .85);
  clamp.close();
  Drive.turn(-190, 100, .7);
  task C2 = task(clamp2BPE);
  Drive.swing(-14.5, 100, -215 , .9);
  Drive.moveDistance(-6.4, 40, .6);
  intake.spin(fwd, 100, pct);
  Drive.turn(-200, 100, .6);
  // task bCont = task(goofyBonkBPE);
  // Drive.swing(57, 100, -90, 1.8);
  // clamp.close();
  // bonk.open();
  // wait(.15, sec);
  // Drive.moveDistance(12, 100, .65);
  // Drive.turn(-45, 100, .6);
  // bonk.close();
  // Drive.turn(-80, 100, .35);
  // lbState = 1; 
  // task hang = task(ladyBrownMechScoring);
  // Drive.swing(14, 65, 0, 1);
  // Drive.moveDistance(10, 100, .7); 
  // Drive.turn(36, 100, .45);
  // Drive.swing(37, 100, -47, 1.7);
  // intake.stop();
  // wait(.2, sec);
  // lbState = 2; 
  // task score = task(ladyBrownMechScoring);


  Drive.moveDistance(40, 100, 1);
  Drive.turn(-270, 100, .7);
  clamp.close();
  intakeLift.open();
  task I2 = task(intContAWP);
  Drive.moveDistance(22.3, 100, .85);
  intakeLift.close();
  Drive.moveDistance(3.6, 30, .4);
  Drive.moveDistance(-2.1, 100, .25);
  Drive.swing(-15.3, 100, -435, 1.05);
  Drive.swing(-16.5, 100, -360, 1.05);
  Drive.moveDistance(-7, 100, .4);
  Drive.moveDistance(2.1, 100, .25);
  intake.spin(fwd, 100, pct);
  wait(.4, sec);



}
int BCRC1(){
  wait(1, sec);
  clamp.open();
  return(0);
}
void blueClampRush(){
  task C1 = task(BCRC1);
  Drive.swing(-42.5, 100, 37, 1.2);
  Drive.moveDistanceTimeout(10, 100, 14, true);
  Drive.turn(20, 100, .5);
}
int slowIntSN(){
  wait(.5, sec);
  intake.spin(fwd, 100, pct);
  wait(.4, sec);
  intake.stop();
  return(0);
}
int slowIntSP(){
  wait(.35, sec);
  intake.spin(fwd, 100, pct);
  wait(.55, sec);
  intake.stop();
  return(0);
}
int SNClamp(){
  wait(.9, sec);
  clamp.open();
  return(0);
}
//DONE
void simpleNegBlue(){
  task intCont = task(slowIntSN);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake.stop();
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(SNClamp);
  Drive.moveDistance( -21.15492957724733 , 40 , 1 );	
  Drive.turn(-45, 100, .9);
  intake.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
//Done
void simpleNegRed(){
  task intCont = task(slowIntSN);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake.stop();
  Drive.turn( -90 , 100 , .65 );	
  task C1 = task(SNClamp);
  Drive.moveDistance( -21.15492957724733 , 40 , 1 );	
  Drive.turn(45, 100, .9);
  intake.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
int posClamp(){
  wait(.84, sec);
  clamp.open();
  return(0);
}
//DONE
void simplePosBlue(){
  Drive.moveDistance(10, 100, .7);
  Drive.turn(-35, 100, .6);
  task intCont = task(slowIntSP);
  Drive.moveDistance(23, 100, 1.1);
  intake.stop();
  Drive.turn( -90 , 100 , .8 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  Drive.turn(45, 100, .9);
  intake.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
//DONE
void simplePosRed(){
  Drive.moveDistance(10, 100, .7);
  Drive.turn(35, 100, .6);
  task intCont = task(slowIntSP);
  Drive.moveDistance(22.5, 100, 1.1);
  intake.stop();
  Drive.turn(90 , 100 , .8 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  // Drive.turn(-45, 100, .9);
  intake.spin(fwd, 100, pct);
  // wait(3, sec);
  // Drive.moveDistance(10, 100, .8);
}
void fractalRightStart(){
  Drive.swing(-12, 100, -90, .8);
  Drive.moveDistance(-5, 70, .35);
  Drive.moveDistance(2.05, 100, .3); // 2.35 for metal field

  intake.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.swing(12, 100, -165, .8);
  Drive.moveDistance(33.5, 100, 1);
  intake.stop();
  Drive.turn(-236, 100, .8);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-20, 45, .9);
  Drive.turn(-185, 100, .5);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(28,90, 1);
  intake.stop();
  Drive.turn(-10, 90, 1.1);
  intake.spin(fwd,100, pct);
  wait(3.8, sec);
  intake.stop();
  Drive.moveDistance(34, 100, 1);
}
void fractalLeftStart(){
  Drive.swing(-12, 100, 90, .9);
  Drive.moveDistance(-5, 50, .5);
  Drive.moveDistance(1.7, 100, .3); // 2.35 for metal field

  intake.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.swing(12, 100, 165, .8);
  Drive.moveDistance(35, 100, 1);
  intake.stop();
  Drive.turn(236, 100, .8);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-20, 45, .9);
  Drive.turn(180, 100, .5);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(27,90, .9);
  intake.stop();
  Drive.turn(15, 90, 1.1);
  intake.spin(fwd,100, pct);
  wait(3, sec);
  intake.stop();
  Drive.moveDistance(32, 100, 1);
}

// SKILLS START

int clamping(){
  wait(.7, sec);
  clamp.open();
  return(0);
}
int slowUp(){
  wait(1, sec);
  lbState = 1;
  task ringOne1 = task(ladyBrownMechScoring);
  return(0);
}
int hookRemove(){
  wait(.55, sec);
  intake.spin(fwd, -100, pct);
  wait(.23, sec);
  intake.stop();
  lbState=3;
  task ringMid1 = task(ladyBrownMechScoring);
  wait(.75, sec);
  return(0);
}

int intakeWait(){
  wait(.55, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakeSlowerStop(){
  wait(2.1, sec);
  intake.stop();
  return(0);
}
int hookSaver(){
  intake.stop();
  wait(.3, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakeShortWait(){
  wait(.65, sec);
  intake.spin(fwd, 100, pct);
  return(0);
}
int intakePause(){
  wait(.9, sec);
  intake.stop();
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
int lastClamp(){
  wait(1, sec);
  clamp.open();
  return(0);
}
int fasterClamping(){
  wait(.7, sec);
  clamp.open();
  return(0);
}

int intContAWPSkills(){
  wait(.3, sec);
  while (!Optical.isNearObject()){
    intake.spin(fwd, 40, pct);
  }
  intake.stop();
  return(0);
}
void simHitSkills(){
  // Optical.setLightPower(10, pct);
  // shouldReject = true;
  // isRed = true;
  intake.spin(fwd,100,pct);
  // task onlyReds = task(colorReject);
  wait(.45, sec);
  Drive.moveDistance(14, 100, .7);
  lbState=0;
  task state0 = task(ladyBrownMechScoring);
  Drive.turn(-90,100, .6);
  task slowClamp = task(clamping);
  Drive.moveDistance(-23.5, 40, 1.1);
  Drive.turn(0, 100, .8);
  Drive.moveDistance(20, 100, .7);
  Drive.turn(26, 100, .4);
  task slowUp1 = task(slowUp);
  Drive.moveDistance(50, 80, 1.6);
  intake.spin(fwd,60,pct);
  Drive.moveDistance(-13, 100, .65);
  Drive.turn(180, 70, .8);
  task removeHook = task(hookRemove);
  wait(.2, sec);
  task waitIntake = task(intakeWait);
  Drive.moveDistance(9.5, 100, .7);
  Drive.turn(90, 100, .7);
  intake.spin(fwd, 100, pct);
  task intCont1 = task(intContAWP);
  Drive.moveDistance(11, 70, .7);
  lbState = 2;
  task ringScore1 = task(ladyBrownMechScoring);
  Drive.turn(90, 30, .15);
  Drive.moveDistance(1000, 100, .5);
  Drive.turn(90, 100, .4);
  lbState = 0;
  task saveTheLady = task(ladyBrownMechScoring);
  Drive.moveDistance(-16, 100, 1);
  Drive.turn(180, 100, .8);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(33, 70, 1.1);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(45, 25, 1.9);
  Inertial.setRotation(180, deg);
  Drive.moveDistance(-3, 100, .4);
  Drive.turn(60, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(16, 70, .9);
  Drive.turn(-17, 70, .6);
  Drive.moveDistance(-20, 100, .8);
  wait(.1, sec);
  clamp.close();
  intake.spin(fwd, -100, pct);
  wait(.1, sec);
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-51, 100, .6);
  task superMarioBrosSlow = task(intakeSlowerStop);
  Drive.moveDistance(40, 100, 1);
  Drive.turn(-51, 100, .2);
  task saveTheCaptain = task(hookSaver);
  Drive.moveDistance(36, 100, .95);
  Drive.turn(-135, 100, .7);
  task intCont2 = task(intContAWPSkills);
  Drive.moveDistance(47.3, 90, 1.5);

  Drive.turn(-37, 100, .7);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-22, 45, .8);
  task onOff = task(intakeOnOff);
  Drive.turn(-44, 100, .3);

  wait(.4, sec);
  Drive.moveDistance(43 , 50 , 1.3);
  Drive.moveDistance(-3, 100, .3);
  task intCont4 = task(intContAWP);
  Drive.turn(-180, 100, .9);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(23, 30, 1.5);
  Drive.moveDistance(18, 30, 1.1);
  Inertial.setRotation(-180, deg);
  Drive.moveDistance(-3, 100, .3);
  Drive.turn(-55, 100, .7);
  Drive.moveDistance(16, 70, .7);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(-10, 100, .6);
  clamp.close();
  Drive.turn(0, 100, .4);
  // //28.4 seconds on 11/16/24 // 34.75 on 11/17/24
  lbState = 1;
  task ladyLift = task(ladyBrownMechScoring);
  intake.spin(fwd, 70, pct);
  Drive.moveDistance(60.5, 70, 1.7);
  Drive.moveDistance(-6, 100, .45);
  Drive.turn(-90, 100, .9);
  intake.stop();
  lbState = 2; 
  task ladyStake2 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .6);
  wait(.4, sec);
  Drive.moveDistance(-20, 100, 1, -90);
  Drive.turn(40, 100, .7);
  lbState = 0;
  task ladyReset = task(ladyBrownMechScoring);
  intake.spin(fwd, 60, pct);
  task intCont = task(intContAWP);
  Drive.moveDistance(35, 70, 1.3);
  Drive.turn(217, 100, 1.1);
  task lastClamp1 = task(lastClamp);
  Drive.moveDistance(-33, 50, 1.2);
  Drive.turn(142, 100, .8);
  intake.spin(fwd, 60, pct);
  Drive.moveDistance(31, 100, .9);
  Drive.turn(46, 100, .6);
  Drive.moveDistance(33, 60, 1.3);

  // Drive.turn(238, 100, .8);
  // wait(.3,sec);
  // task Yay = task(unclamp);
  // wait(.1, sec);
  // intake.stop();
  // Drive.moveDistance(-30, 100, .8);
  // Drive.moveDistance(5, 100, .2);
  // Drive.moveDistance(-1000, 100,.3);
  // Drive.turn(228, 100, .5);
  // Drive.moveDistance(18, 100, .65);
  // intake.spin(fwd, 60, pct);
  // Drive.turn(275, 100, .45);
  // Drive.moveDistance(43, 100, 1.1);
  // Drive.turn(315, 100, .45);
  // Drive.moveDistance(23, 100, .7);
  // Drive.turn(280, 100, .4);
  // Drive.moveDistance(38, 100, 1);
  // Drive.moveDistance(-10, 100, .4);
  // lbState = 2; 
  // task hang = task(ladyBrownMechScoring);
  // Drive.turn(327, 100, 1);
  // intake.stop();
  // Drive.moveDistance(-55, 100, 1.3);
  // Drive.turn(315, 100, .2);
  // Drive.moveDistance(-1000, 45, .4);
  // Drive.moveDistance(4, 100, .3);

  Drive.turn(87, 100, .5);
  Drive.moveDistance(11, 50, .9);
  Drive.turn(200, 100, .8);
  wait(.3, sec);
  intake.stop();
  clamp.close();
  wait(.1, sec);
  Drive.moveDistance(-1000, 100, .6);
  Drive.moveDistance(5, 100, .35);
  Drive.turn(220, 100, .5);
  Drive.swing(20, 100, 275, .9);
  Drive.swing(37, 100, 320, 1);
  Drive.swing(20, 100, 280, .8);
  Drive.moveDistance(1000, 100, 1.05);
  Drive.swing(-9, 100, 350, .8);
  Drive.swing(-20, 100, 315, 1);
  intake.stop();
  lbState = 3; 
  task ladyStake3 = task(ladyBrownMechScoring);
  Drive.moveDistance(-1000, 54, 1);
  
 

}
int redRingRushC1(){
  wait(.4, sec);
  clamp.open();
  return(0);
}
int blueRingRushC1(){
  wait(.5, sec);
  clamp.open();
  return(0);
}
int redRRBonk(){
  wait(.69, sec);
  bonk.open();
  return(0);
}
int intCont1RRR(){
  wait(.6, sec);
  intake.stop();
  return(0);
}
void ringRushRed(){
  task bonkers = task(redRRBonk);
  intake.spin(fwd,100, pct);
  Drive.swing(39.5, 100, -35, 1);
  Drive.moveDistance(2.3, 100, .25);
  task iStop = task(intContAWP);

  Drive.moveDistance(-9, 100, .7);
  
  Drive.swing(-14.5, 100, -60, .9);
  task C1 = task (redRingRushC1);
  Drive.moveDistance(-8, 60, .6);
  Drive.turn(-65, 100, .3);
  Drive.moveDistance(10, 100, .7);
  intake.spin(fwd, 100, pct);
  bonk.close();
  wait(.3, sec);
  Drive.turn(-77, 100, .5);
  Drive.moveDistance(23, 100, 1);
  Drive.turn(-200, 100, .9);
  
  Drive.moveDistance(31, 60, 1.6);
  Drive.moveDistance(-10.5, 100, .7);
  Drive.turn(-270, 100, .6);
  intakeLift.open();
  Drive.moveDistance(30, 100 , .9);
  intakeLift.close();
  wait(.4, sec);
  Drive.moveDistance(-10, 100, .7);
  // clamp.close();
  Drive.moveDistance(10,100, .7);
  // task iStop2 = task(intContAWP);
  // Drive.turn(-360, 100, .6);
  // Drive.moveDistance(-15, 80, 1);
  // Drive.moveDistance(2.1, 100, .3);
  // while(true){
    intake.spin(fwd, 100,pct);
  // }
  

}
int ringRushBLUEONLY(){
  while (true){
    if (Optical.hue() < 10 && !isRed && Optical.isNearObject()){
      intake.stop();
      return(0);
    }
  }
}
void ringRushBlue(){
  task bonkers = task(redRRBonk);
  intake.spin(fwd,60, pct);
  Drive.swing(39.5, 100, 35, 1);
  Drive.moveDistance(2.3, 100, .25);
  Drive.turn(90, 100, .5);
  task iStop = task(intContAWP);
  Drive.turn(35, 100, .5);
  Drive.moveDistance(-7, 100, .7);
  Drive.swing(-14.5, 100, 60, .9);
  task C1 = task (blueRingRushC1);
  Drive.moveDistance(-9, 60, .8);
  intake.spin(fwd, 100, pct);
  Drive.turn(65, 100, .3);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(10, 100, .7);
  intake.spin(fwd, 100, pct);
  bonk.close();
  wait(.3, sec);
  Drive.turn(77, 100, .5);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(23, 100, 1);
  intake.spin(fwd, 100, pct);
  Drive.turn(200, 100, .9);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(31, 100, 1.15);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(-10.5, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.turn(260, 100, .6);
  intakeLift.open();
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(31, 80 , 1.1);
  intake.spin(fwd, 100, pct);
  intakeLift.close();
  wait(.4, sec);
  Drive.moveDistance(-4, 100, .35);
  // clamp.close();
  Drive.moveDistance(10,100, .65);
  task colorStop = task(ringRushBLUEONLY);
  // task iStop2 = task(intContAWP);
  // Drive.turn(-360, 100, .6);
  // Drive.moveDistance(-15, 80, 1);
  // Drive.moveDistance(2.1, 100, .3);
  // while(true){
    intake.spin(fwd, 100,pct);
  // }
  bonk.open();
  Drive.swing(60, 100, -135+360, 1.2);
  Drive.turn(500, 100, .6);
  

}

int PTC1(){
  wait(.8, sec);
  clamp.open();
  return(0);
}
void PTFinals(){
  lbState = 4;
  task ladyStake3 = task(ladyBrownMechScoring);
  wait(.3, sec);
  Drive.moveDistance(-5, 100, .4);
  intakeLift.open();
  Drive.turn(95, 100, .7);
  intake.spin(fwd, 100, pct);
  Drive.moveDistance(7, 70, .5);
  intakeLift.close();
  Drive.moveDistance(-3, 100, .3);
  Drive.moveDistance(5, 100, .4);
  task iStop = task(intContAWP);
  Drive.turn(0, 100, .65);
  task C1 = task(PTC1);
  Drive.moveDistance(-28, 50, 1);
  intake.spin(fwd, 100, pct);

  
}
void wallstakePosBlue(){
  lbState = 3;
  task ladyStake3 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .7);
  Drive.turn(-35, 100, .8);
  task iStop = task(intContAWP);
  Drive.moveDistance(23, 100, 1.1);
  intake.stop();
  Drive.turn( -90 , 100 , .9 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  intake.spin(fwd,100, pct);
  Drive.moveDistance(37, 100, 1);
  Drive.turn(0, 100, .9);
  clamp.close();
  Drive.moveDistance(9.5, 100, .8);
  Drive.turn(-50, 100, .7);
  Drive.moveDistance(3, 20, .3);
  lbState = 4;
  task ladyStake = task(ladyBrownMechScoring);
  
}
void wallstakePosRed(){
  lbState = 3;
  task ladyStake3 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .7);
  Drive.turn(35, 100, .8);
  task iStop = task(intContAWP);
  Drive.moveDistance(23, 100, 1.1);
  intake.stop();
  Drive.turn(90 , 100 , .9 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  intake.spin(fwd,100, pct);
  Drive.moveDistance(34, 100, 1);
  Drive.turn(0, 100, .9);
  clamp.close();
  Drive.moveDistance(15.8, 100, .8);
  Drive.turn(50, 100, .7);
  lbState = 2;
  task ladyStake = task(ladyBrownMechScoring);
  Drive.moveDistance(5, 20, .4);
  lbState = 4;
  task ladyStake2 = task(ladyBrownMechScoring);
  
}
void (*autonsList[])() =
{
  wallstakePosRed,
  simplePosRed, //DONE Center flex wheel center of inside tile
  wallstakePosBlue,
  simplePosBlue,//DONE Center flex wheel center of inside tile
  fractalLeftStart,
  simHitSkills,
  soloSig, // DONE 4.25 in from right side field tile locking to first drive screw
  fractalRightStart,
  ringRushBlue,
  ringRushRed, 
  blueNegElim,//DONE STRAIGHT AT RING
  redPosElim,
  bluePosElim, // Done up to Alliance NEEDS TUNING
  blueClampRush,
  redNegElimKALA, //DONE READY Straight at ring
  simpleNegBlue,//DONE STRAIGHT AT RING
  simpleNegRed,//DONE STRAIGHT AT RING
  redNegElim,// TEST BEFORE RUN 
  redPosElim,
  mogoRushBlue,
  
  
  
  

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
    con.Screen.print("Bat");
    con.Screen.print(Brain.Battery.capacity(percent));
    con.Screen.print("   Int:");
    con.Screen.print(intake.temperature(fahrenheit));
    con.Screen.setCursor(2, 1);
    con.Screen.print("Left  ");
    con.Screen.print((left1.temperature(fahrenheit) + left2.temperature(fahrenheit) + left3.temperature(fahrenheit)) / 3);
    con.Screen.setCursor(3, 1);
    con.Screen.print("Right  ");
    con.Screen.print((right1.temperature(fahrenheit) + right2.temperature(fahrenheit) + right3.temperature(fahrenheit)) / 3);
    wait(2, sec);
  }
  return (0);
}
int DClamp(){
  wait(1.2, sec);
  clamp.open();
  return(0);
}
void usercontrol()
{
  // lbState = 4; 
  // task ladyStake2 = task(ladyBrownMechScoring);
  // wait(.3, sec);
  // task C1 = task (DClamp);
  // Drive.swing(-16, 100, -65, 1);
  // Drive.moveDistance(-5, 70, .35);
  lbState = 0;
  task ringOne1 = task(ladyBrownMechScoring);
  // isRed = true;
  // task cReject = task(colorReject);
  task printcon = task(conInfo);
  while (true)
  {
    // if (!(lbState == 1) && f13loop){

    //   task noJam = task(antiJam);
    //   f13loop = false;
    // }

    // Optical.setLightPower(100, percent);
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
    if (!con.ButtonA.pressing()){
      rightdrive.spin(fwd, con.Axis2.value(), pct);
      leftdrive.spin(fwd, con.Axis3.value(), pct);
    }
    else {
      rightdrive.spin(fwd, -10, pct);
      leftdrive.spin(fwd, -10, pct);
    }
    if (con.ButtonLeft.pressing()){
      Drive.moveDistance(2.1, 100, .3);
      intake.spin(fwd, 100, pct);
    }
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
    else if (con.ButtonUp.pressing()){
      lbState = 3;
      task ladyBrownZero = task(ladyBrownMechScoring);
    }
    else if (con.ButtonL1.pressing()){
      if (f9loop){
        lbState += 1;
        f9loop = false;
      }
      if (lbState > 2){
        lbState = 1;
        f13loop = true;
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


    if (con.ButtonA.pressing()){
      if (con.Axis2.value() < -50 && con.Axis2.value() < -50 ){
        rightdrive.spin(fwd, -60, pct);
        leftdrive.spin(fwd, -60, pct);
      }
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





