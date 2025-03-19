
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
bool f14loop = true;
bool f15loop = true;
bool isRed = true;
bool reject = false;
bool shouldReject = true;
bool rejectStart = false;
bool holdRing = false;
bool intakeRev = false;
bool antiJammy = false;
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
int antiJam(){
  while (true){
    if (upperIntake.current(pct) > 93  && !intakeRev && !(lbState== 1)){
      antiJammy = true;
      upperIntake.spin(fwd, -100, pct);
      wait(.15, sec);
    } 
    else{
      antiJammy = false;
      wait(.2, sec);
    }
  }
}
int lbIntake(){
  intake_Group.spin(fwd, -50, pct);
  wait(.1, sec);
  intake_Group.stop();
  return(0);
}
int ladyBrownMechScoring(){
  double lbkP = 1.2;
  double lbkD = .3;
  double lbSpeed = 0;
  task intContLB = task (lbIntake);
  if (lbState == 0){
    while(Rotation.position(deg)- .2 > 101){
      lbSpeed = lbkP * (101-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) - .2 > 101){
        lb.spin(fwd, lbSpeed,pct);
      
      }
      else {
        lb.stop();
  
      }
    }
    lb.stop();
  
    return(0);
  }
  if (lbState == 1){
    while(Rotation.position(deg)- .2 > 114.5 or Rotation.position(deg) + .2 < 114.5){
      lbSpeed = lbkP * (114.5-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 114.5){
        lb.spin(fwd, lbSpeed,pct);
        
      }
      else if (Rotation.position(deg) - .2 > 114.5){
        lb.spin(fwd, lbSpeed,pct);
       
      }
      else {
        lb.stop(hold);
        
      }
    }
    lb.stop(hold);
 
    return(0);
  }
    if (lbState == 2){
    while(Rotation.position(deg) - .2 > 249.5 or Rotation.position(deg) + .2 < 249.5){
      lbSpeed = lbkP * (249.5-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 249.5){
        lb.spin(fwd, lbSpeed ,pct);
        
      }
      else if (Rotation.position(deg) - .2 > 249.5){
        lb.spin(fwd, lbSpeed,pct);
      
      }
      else {
        lb.stop(hold);
        
      }
    }
    lb.stop(hold);
    
    return(0);
  }
  if (lbState == 3){
    while(Rotation.position(deg) - .2 > 150 or Rotation.position(deg) + .2 < 150){
      lbSpeed = lbkP * (150-Rotation.position(deg))  - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 150){
        lb.spin(fwd,  lbSpeed,pct);
       
      }
      else if (Rotation.position(deg) - .2 > 150 ){
        lb.spin(fwd,  lbSpeed,pct);
      
      }
      else {
        lb.stop(hold);
        
      }
    }
    lb.stop(hold);
   
    return(0);
  }
  if (lbState == 4){
    while(Rotation.position(deg) - .2 > 329 or Rotation.position(deg) + .2 < 329){
      lbSpeed = lbkP * (329-Rotation.position(deg)) - lbkD * lbSpeed;
      if (Rotation.position(deg) + .2 < 329){
        lb.spin(fwd, lbSpeed ,pct);
       
      }
      else if (Rotation.position(deg) - .2 > 329){
        lb.spin(fwd,  lbSpeed,pct);
        
      }
      else {
        lb.stop(hold);
       
      }
    }
    lb.stop(hold);
 
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
      double initPos = intake_Group.position(deg);
      double target = rejectAng+initPos;
      double rejSpeed;
      while (reject){
        double currPos = intake_Group.position(deg);
        double error = target - currPos;
        rejSpeed = error * rejectkP - rejectkD * rejSpeed;
        intake_Group.spin(fwd, rejSpeed, pct);

        if (currPos>target or currPos+2>target){
          intake_Group.spin(fwd, -50, pct);
          wait(.2, sec);
          intake_Group.stop();
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
      double initPos = intake_Group.position(deg);
      double target = rejectAng+initPos;
      double rejSpeed;
      while (reject){
        double currPos = intake_Group.position(deg);
        double error = target - currPos;
        rejSpeed = error * rejectkP - rejectkD * rejSpeed;
        intake_Group.spin(fwd, rejSpeed, pct);

        if (currPos>target or currPos+2>target){
          intake_Group.spin(fwd, -50, pct);
          wait(.2, sec);
          intake_Group.stop();
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
  wait(.7, sec);
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
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(23, 100, .85);
  intake_Group.stop();
  Drive.turn(-130, 100, .7);
  task firstClamp = task(clampOnebRB);
  Drive.moveDistance(-14, 100, .75);
  intake_Group.spin(fwd, 100, pct);
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
  intake_Group.stop();
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
  intake_Group.spin(fwd,100, pct);
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
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(15, 60, 18, 1);
  Drive.swing(19.5, 100, 49, .8);
  lbState = 1;
  task setLB = task(ladyBrownMechScoring);
  intake_Group.spin(fwd, 80, pct);
  Drive.swing(20.5, 70, 43, 1.1);
  intake_Group.stop();
  wait(.05,sec);
  lbState = 4;
  task scoreLB = task(ladyBrownMechScoring);
  Drive.moveDistance(3, 50, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(-13, 70, 162.5, 1);
  bonk.open();
  intake_Group.spin(fwd, 100,pct);
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
  intake_Group.spin(fwd, 100, pct);
  return(0);
}
int stopInt(){
  wait(.3, sec);
  intake_Group.stop();
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
  intake_Group.spin(fwd, 90, pct);
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
  // intake_Group.spin(fwd,100, pct);
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
//   intake_Group.spin(fwd, -100, pct);
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
//   intake_Group.spin(fwd, 100, pct);
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
  intake_Group.spin(fwd, 100, pct);
  wait(1.4, sec);
  intake_Group.spin(fwd, -100, pct);
  return(0);
}

int intContAWP(){
  while (!Optical.isNearObject()){
    intake_Group.spin(fwd, 60, pct);
  }
  intake_Group.stop();
  return(0);
}
int intContLower(){
  while (!TheOpps.isNearObject()){
    intake_Group.spin(fwd, 60, pct);
  }
  intake_Group.stop();
  return(0);
}
int intCont2AWP(){
  wait(.9, sec);
  intake_Group.stop();
  return(0);
}
void soloSig(){
  Optical.setLightPower(100, pct);
  Drive.swing(-12, 100, -90, .8);
  Drive.moveDistance(-5, 50, .5);
  Drive.moveDistance(1.7, 100, .4); // 2.35 for metal field

  intake_Group.spin(fwd, 100, pct);
  wait(.4, sec);
  Drive.swing(12, 100, -168, .8);
  lbState = 3;
  task score = task (ladyBrownMechScoring);
  task stoppers = task(intCont2AWP);
  Drive.moveDistance(34, 100, 1);
  Drive.turn(-236, 100, .65);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-21, 45, .9);
  Drive.turn(-185, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(30, 90, .93);
  intake_Group.stop();
  Drive.turn(19, 90, 1.1);

  task longDriveIntCont = task(stopIntBSAWP);
  Drive.moveDistance(76.2, 100, 1.7);
  Drive.turn(-43, 100, .75);
  clamp.close();
  intake_Group.spin(fwd, 60, pct);
  Drive.moveDistance(42 , 100, 1.1);
  task intCont = task(intContAWP);
  Drive.turn(0, 100, .53);
  task clamp2 = task(sigAWPClamping2);
  Drive.moveDistance(-30, 45, 1.1 );
  // lbState = 0;
  // task score2 = task (ladyBrownMechScoring);
  Drive.turn(-120, 100, .7);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(6, 100, .5);

}


int clampRPE(){
  wait(.25, sec);
  bonk.open();
  return(0);
}
int intStopRPE(){
  wait(.6, sec);
  intake_Group.stop();
  return(0);
}
int clampTwoRPE(){
  wait(1, sec);
  clamp.open();
  return(0);
}
int delayReleaseRPE(){
  wait(.4, sec);
  clamp.close();
  intake_Group.stop();
  return(0);
}
int bonkDelayRPE(){
  wait(.6, sec);
  bonk.open();
  return(0);
}
int slowintRPE(){
  wait(.15, sec);
  intake_Group.spin(fwd, 50, pct);
  return(0);
}
int C1RPE(){
  wait(.7, sec);
  clamp.open();
  return(0);
}
int intake2RPE(){
  intake_Group.spin(fwd, 100, pct);
  wait(.5, sec);
  intake_Group.stop();
  wait(.2, sec);
  intake_Group.spin(fwd, -100, pct);
  wait(.3, sec);
  intake_Group.stop();
  return(0);
}
int C2RPE(){
  wait(.84, sec);
  clamp.open();
  return(0);
}
int I3RPELB(){
  intake_Group.spin(fwd, 90, pct);
  wait(.7, sec);
  intake_Group.stop();
  wait(.1, sec);
  intake_Group.spin(fwd, -100, pct);
  wait(.05, sec);
  intake_Group.stop();
  return(0);
}
int intContRPE(){
  while (!Optical.isNearObject()){
    intake_Group.spin(fwd, 55, pct);
  }
  intake_Group.stop();
  return(0);
}
int intContSimple(){
  wait(.3, sec);
  while (!Optical.isNearObject()){
    intake_Group.spin(fwd, 60, pct);
  }
  intake_Group.stop();
  return(0);
}
void redPosElim(){
  task bonkers = task(bonky);
  task I1 = task (slowintRPE);
  Drive.swing(42, 95, -17, 1.05);
  task intCont = task(intContRPE);
  wait(.1, sec);
  Drive.swing(-12, 70, 66, 1.1);
  
  bonk.close();
  Drive.moveDistance(1, 100, .2);
  task C1 = task(C1RPE);
  Drive.moveDistance(-22, 40, 1);
  task I2 = task (intake2RPE);
  Drive.swing(37, 100, 144, 1.25);
  lbState = 1;
  task up = task (ladyBrownMechScoring);
  wait(.1, sec);
  task I3 = task (I3RPELB);
  bonk.open();
  Drive.moveDistance(23, 100, .9);
  Drive.turn(210, 70, .75);
  lbState = 3;
  task midstate = task (ladyBrownMechScoring);
  bonk.close();
  wait(.1, sec);
  Drive.turn(185, 100, .35);
  task intCont2 = task(intContAWP);
  Drive.moveDistance(8, 70, .8);
  clamp.close();
  Drive.moveDistance(-17, 100, .75);
  Drive.moveDistance(7, 100, .5);
  Drive.turn(120, 100, .7);
  Drive.swing(-20, 100, 178, 1);
  task C2 = task(C2RPE);
  Drive.moveDistance(-24.5, 35, 1.1);
  Drive.moveDistance(4, 100, .3);
  Drive.turn(8, 100, 1.2);
  intake_Group.spin(fwd, 100, pct);
  lbState = 2;
  task halfscore = task (ladyBrownMechScoring);
  Drive.swing(8, 100,22, .8);
  // lbState = 4;
  // task score = task (ladyBrownMechScoring);
  // wait(.3, sec);
  // Drive.moveDistance(-5, 100, .4);
  // lbState = 0;
  // task down = task (ladyBrownMechScoring);


  





  // Drive.swing(-13, 100, 60, 1);
  // Drive.swing(-15, 100, 125, 1);
  // Drive.moveDistance(-5, 40, .4);

  // Drive.turn(-53, 100, .5);
  // intake_Group.spin(fwd, 100, pct);
  // task intCont = task(intStopRPE);
  // Drive.moveDistance(27.5, 100, 1);
  // Drive.moveDistance(-14.3, 100, .7);
  // Drive.turn(90, 100, .7);
  // task firstClamp = task(clampOnebRB);
  // Drive.moveDistance(-23, 50, 1.1);
  // Drive.moveDistance(3, 100,.3);
  // Drive.turn(0, 100, .8);
  // intake_Group.spin(fwd, 100, pct);
  // task delayC1 = task(delayReleaseRPE);
  // Drive.moveDistance(-6, 100, .7);
  // Drive.moveDistance(8, 100, .5);
  // Drive.turn(-110, 100, .8);
  // task clamp2 = task(clampTwoRPE);
  // Drive.moveDistance(-20.5 , 35, 1.1);
  // Drive.turn(0, 100, .9);
  // intake_Group.spin(fwd, 100, pct);


  // Drive.moveDistance(-10, 40, .9);
  // intake_Group.spin(fwd, 100, pct);
  // Drive.turn(245, 100, .7);
  // Drive.swing(26, 100, 320, 1.4);
  // task debonk = task(bonkDelayRPE);
  // Drive.moveDistance(12, 100, .7);
  // Drive.moveDistance(-7, 100, .5);
  // bonk.close();
  // Drive.turn(200, 100, .4);
  // Drive.moveDistance(5, 100, .4);



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
  intake_Group.spin(fwd,100, pct);
  Drive.moveDistance( 21.647887323669252 , 100 , .9 );	
  intake_Group.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .5 );	
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -17.15492957724733 , 100 , .85 );	
  Drive.turn( 232.14743605677376 , 100 , .9 );
  intake_Group.spin(fwd, 100, pct);
  intakeLift.open();
  task contInt = task(dropInt);	
  Drive.moveDistance( 33.492957746054316 , 100 , 1 );	
  clamp.close();
  intake_Group.stop();	
  Drive.turn( 258 , 100 , .4 );	
  Drive.moveDistance( 22.873239436329776 , 100 , .9 );	
  Drive.turn( 90 , 100 , .9 );	
  Drive.moveDistance( 18.380281689907854 , 100 , .9 );	
  Drive.turn( 0 , 100 , 1.00000009 );	
  Drive.moveDistance( -5.309859154862269 , 100 , .9 );	
  intake_Group.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.moveDistance( 5.309859154862269 , 100 , .9 );
  Drive.turn( 128 , 100 , .8 );	
  Drive.moveDistance( -18.380281689907854 , 100 , 1.1 );	
  Drive.turn( 145 , 100 , .9 );	
  task C2 = task(testClamp2);
  Drive.moveDistance( -10.619718309724538 , 100 , 1.1 );	
  Drive.turn( -78.54593116361525 , 100 , 1.00000009 );	
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance( 22.056338027889428 , 100 , .9 );	}

void simAuto2(){	
  intake_Group.spin(fwd,100, pct);
  Drive.moveDistance( 21.647887323669252 , 100 , .9 );	
  intake_Group.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .9 );	
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -17.15492957724733 , 100 , .85 );	
  Drive.turn( 232.14743605677376 , 100 , .9 );	
  intake_Group.spin(fwd, 100, pct);
  intakeLift.open();
  task contInt = task(dropInt);
  Drive.moveDistance( 33.492957746054316 , 100 , 1 );	
  clamp.close();
  intake_Group.stop();
  Drive.turn( -68.11626120840089+360 , 100 , 1.00000009 );	
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance( 50.239436619081474 , 100 , 1.4 );	
  intake_Group.stop();
  Drive.moveDistance( 4.901408450642095 , 100 , .8 );	
  Drive.turn( -90+360 , 100 , .5 );	
  task C2 = task(testClamp2);
  Drive.moveDistance( -17.15492957724733 , 100 , .8 );	
  intake_Group.spin(fwd, 100, pct);
  }

int slowIntBNE(){
  wait(.5, sec);
  intake_Group.spin(fwd, 100, pct);
  wait(.4, sec);
  intake_Group.stop();
  return(0);
}

int lbDelayBNE(){
  wait(.2, sec);
  intake_Group.spin(fwd, -100, pct);
  wait(.2,sec);
  intake_Group.stop();
  lbState= 4;
  task score = task (ladyBrownMechScoring);
  wait(.5, sec);
  return(0);
}

int stopRingBNE(){
  while (holdRing){
    if (235 > Optical.hue() && Optical.hue() > 225){
      intake_Group.stop();
      return(0);
    }

  }
  return(0);
}
int conIntake2RNE(){
  wait(1.5, sec);
  intake_Group.stop();
  return(0);
}

//DONE CLEARS POSTIVE CORNER
void blueNegElimBad(){
  // Optical.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = false;
  // task cReject = task(colorReject);
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 26.3 , 60 , 1.1);	
  intake_Group.stop();
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -20.15492957724733 , 70 , 1 );	
  Drive.moveDistance(3,100, .3);
  intake_Group.spin(fwd, 100, pct);
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
  intake_Group.spin(fwd, 100, pct);
  task intCont3 = task(intContAWP);
  Drive.moveDistance(28, 100, .9);
  intakeLift.close();

  Drive.turn(-60, 100, .4);
  
  Drive.moveDistance(-16, 100, .8);
  Drive.moveDistance(1.2, 100, .3);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(-4.55, 100, .4);
  intake_Group.spin(fwd, 100, pct);


  // Drive.moveDistance(63,100, 1.6);
  // intakeLift.close();
  // Drive.turn(-180, 100, .7);
  // intake_Group.spin(fwd, 100, pct);
  // Drive.swing(17, 100, -90, .9);
  // Drive.turn(-93, 100, .2);
  // bonk.open();
  // Drive.moveDistance(14, 100, .75);
  // Drive.turn(45, 100, .9);
  // Drive.moveDistance(5, 100, .4);
  



}
int clamp1BNE(){
  wait(.75, sec);
  clamp.open();
  return(0);
}
void blueNegElim(){
  Optical.setLightPower(100, pct);
  Drive.moveDistance(6.3, 30, .7);
  lbState= 4;
  task up = task(ladyBrownMechScoring);
  wait(.5, sec);
  Drive.moveDistance(-10, 100, .7);
  lbState= 0;
  task down = task(ladyBrownMechScoring);
  intakeLift.open();
  intake_Group.spin(fwd, 100, pct);
  task I1 = task(intContAWP);
  Drive.turn(75, 100, .4);
  Drive.moveDistance(6, 60, .55);
  intakeLift.close();
  Drive.moveDistance(-2, 100, .25);
  Drive.moveDistance(3, 100, .3);
  Drive.turn(-9, 100, .85);
  task C1 = task(clamp1BNE);
  Drive.moveDistance(-34, 60, 1.1);
  Drive.turn(-180, 100, 1.1);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(12.6, 100, -138, 1);
  Drive.moveDistance(15, 80, .85);
  Drive.turn(-25, 100, 1);
  Drive.moveDistance(15, 100, .75);
  Drive.turn(60, 100, .7);
  Drive.swing(30, 100,110, .9);

  Drive.moveDistance(4.5, 100, .4);
  bonk.open();
  wait(.3, sec);
  Drive.moveDistance(-10, 100, .6);
  bonk.close();
  Drive.turn(90, 100, .3);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(8, 100, .6);
  Drive.moveDistance(-2, 100, .8);


  
}
int clamp1RNE(){
  wait(.9, sec);
  clamp.open();
  return(0);

}
int delayIntRNE(){
  wait(.4, sec);
  intake_Group.spin(fwd, -100, pct);
  return(0);
}
bool intakeCont = true;
int alwaysIntake(){
  while (intakeCont){
    intake_Group.spin(fwd, 100, pct);
    if (235 > Optical.hue() && Optical.hue() > 225){
      intake_Group.stop();
      break;
    }
  }
  return(0);
}
void redNegElim(){
  Optical.setLightPower(100, pct);
  Drive.moveDistance(6.3, 20, .8);
  lbState= 4;
  task up = task(ladyBrownMechScoring);
  wait(.5, sec);
  Drive.moveDistance(-10, 100, .7);
  lbState= 0;
  task down = task(ladyBrownMechScoring);
  intakeLift.open();
  intake_Group.spin(fwd, 100, pct);
  task I1 = task(intContAWP);
  Drive.turn(-77, 100, .4);
  Drive.moveDistance(8, 60, .65);
  intakeLift.close();
  wait(.1, sec);
  Drive.moveDistance(-3.5, 70, .35);
  Drive.moveDistance(1.5, 100, .3);
  Drive.turn(16, 100, .85);
  task C1 = task(clamp1RNE);
  Drive.moveDistance(-37, 45, 1.2);
  Drive.turn(175, 100, 1.1);
  task I3 = task (alwaysIntake);
  Drive.swing(11.3, 100, 134 , 1);
  Drive.moveDistance(15, 100, .85);
  Drive.turn(34, 100, 1);
  Drive.moveDistance(18, 100, .75);


  //9.3 sec

  // Drive.turn(-65, 100, .8);
  // Drive.moveDistance(30, 100, .8);


  Drive.turn(-10, 100, .7);
  intakeCont = false;
  task I2 = task (delayIntRNE);
  Drive.swing(86, 100, -70, 1.7);
  // bonk.open();
  // intake_Group.stop();
  // Drive.swing(45, 100, 45, 1.3);
  // Drive.turn(100, 100, .6);
  // Drive.turn(45, 100, .6);
  // Drive.moveDistance(5, 100, .4);
  // Drive.turn(150, 100, .8);



}
int conIntake3RNE(){
  wait(.6, sec);
  intake_Group.stop();
  return(0);
}
int RNEC1(){
  wait(.47, sec);
  clamp.open();
  return(0);
}
void redNegElimOld(){
  // Optical.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = false;
  // task cReject = task(colorReject);
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake_Group.stop();
  Drive.turn(-90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -19.15492957724733 , 70 , .95 );	
  Drive.moveDistance(2,100, .25);
  intake_Group.spin(fwd, 100, pct);
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
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(9,60, .9);
  intakeLift.close();
  intake_Group.spin(fwd, 100, pct);
  task intCont2 = task(conIntake3RNE);
  Drive.turn(45, 100, .55);
  Drive.moveDistance(-14.5, 100, .7);
  Drive.turn(-90, 100, .9);
  Drive.swing(-12, 100, 0, .9);
  Drive.moveDistance(.2, 100, .1); 
  intake_Group.spin(fwd, 100, pct);



}

void redNegElimKALA(){
  task intCont = task(slowIntBNE);
  Drive.moveDistance( 26.3 , 60 , 1.1);	
  intake_Group.stop();
  Drive.turn( -90 , 100 , .65 );	
  task C1 = task(testClamp);
  Drive.moveDistance( -20.15492957724733 , 70 , 1 );	
  Drive.moveDistance(3,100, .3);
  intake_Group.spin(fwd, 100, pct);
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
  intake_Group.spin(fwd, 100, pct);
  task intCont3 = task(intContAWP);
  Drive.moveDistance(28, 100, .9);
  intakeLift.close();

  Drive.turn(60, 100, .4);
  
  Drive.moveDistance(-16, 100, .8);
  Drive.moveDistance(1.2, 100, .3);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(-4.55, 100, .4);
  intake_Group.spin(fwd, 100, pct);


  // Drive.moveDistance(63,100, 1.6);
  // intakeLift.close();
  // Drive.turn(-180, 100, .7);
  // intake_Group.spin(fwd, 100, pct);
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
  wait(1.05, sec);
  clamp.open();
  return(0);
}
int lbSet(){
  wait(.5, sec);
  intake_Group.stop();
  return(0);
}
int openClampBPE(){
  wait(.8, sec);
  clamp.close();
  return(0);
}
int clampBPE3(){
  wait(.7, sec);
  clamp.open();
  return(0);
}
int intContBPE(){
  wait(.45, sec);
  intake_Group.stop();
  return(0);
}
int intCont2BPE(){
  wait(.65, sec);
  intake_Group.stop();
  return(0);
}
int intContBPEStop(){
  while (!(Optical.isNearObject())){
    intake_Group.spin(fwd, 60, pct);
  }
  if (!(240 > Optical.hue() && Optical.hue() > 220)){
    wait(.3, sec);
  }
  while (!(Optical.isNearObject())){
    intake_Group.spin(fwd, 60, pct);
  }
  if (!(240 > Optical.hue() && Optical.hue() > 220)){
    wait(.3, sec);
  }
  while (!(Optical.isNearObject())){
    intake_Group.spin(fwd, 60, pct);
  }
  intake_Group.stop();
  return(0);
}
void bluePosElim(){
  Optical.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = false;
  task bonky = task(bonkers);
  Drive.swing(36.6, 100, -11, .95);
  Drive.moveDistance(-10, 100, .65);
  bonk.close();
  Drive.swing(8, 100, -50, .8);
  Drive.swing(-12.5, 100, -90, 1.05);
  task C1 = task(clamp1BPE);
  Drive.moveDistance(-7, 45, .6);
  Drive.turn(-90, 100, .2);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(30, 100, .95);
  task I1 = task(intContBPE);
  Drive.moveDistance(-14.2, 100, .95);
  clamp.close();
  Drive.turn(-190, 100, .7);
  task C2 = task(clamp2BPE);
  Drive.swing(-14, 100, -215 , .9);
  Drive.moveDistance(-3, 30, .4);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(-200, 100, .6);

  bonk.open();
  task C4 = task(openClampBPE);
  Drive.swing(52.5, 100, -93, 1.8);
  clamp.close();
  bonk.open();
  wait(.15, sec);
  Drive.moveDistance(12, 100, .65);
  Drive.turn(-45, 100, .6);
  bonk.close();
  task I2 = task(intContBPEStop);
  Drive.turn(-80, 100, .35);
  // lbState = 1; 
  // task hang = task(ladyBrownMechScoring);
  Drive.swing(14, 65, 0, 1);
  Drive.moveDistance(10, 100, .7); 
  Drive.turn(36, 100, .45);
  Drive.swing(25, 100, -47, 1.7);
  intake_Group.stop();
  wait(.2, sec);
  task C3 = task(clampBPE3);
  Drive.moveDistance(-25, 70, 2);

  // lbState = 2; 
  // task score = task(ladyBrownMechScoring);


  // Drive.moveDistance(40, 100, 1);
  // Drive.turn(-270, 100, .7);
  // clamp.close();
  // intakeLift.open();
  // task I2 = task(intContAWP);
  // Drive.moveDistance(22.3, 100, .85);
  // intakeLift.close();
  // Drive.moveDistance(3.6, 30, .4);
  // Drive.moveDistance(-2.1, 100, .25);
  // Drive.swing(-15.3, 100, -435, 1.05);
  // Drive.swing(-16.5, 100, -360, 1.05);
  // Drive.moveDistance(-7, 100, .4);
  // Drive.moveDistance(2.1, 100, .25);
  // intake_Group.spin(fwd, 100, pct);
  // wait(.4, sec);



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
  intake_Group.spin(fwd, 100, pct);
  wait(.4, sec);
  intake_Group.stop();
  return(0);
}
int slowIntSP(){
  wait(.35, sec);
  intake_Group.spin(fwd, 100, pct);
  wait(.55, sec);
  intake_Group.stop();
  return(0);
}
int SNClamp(){
  wait(.9, sec);
  clamp.open();
  return(0);
}
//DONE
void simpleNegBlue(){
  task intCont = task(intContSimple);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake_Group.stop();
  Drive.turn( 90 , 100 , .65 );	
  task C1 = task(SNClamp);
  Drive.moveDistance( -22, 40 , 1 );	
  Drive.turn(-45, 100, .9);
  intake_Group.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
//Done
void simpleNegRed(){
  task intCont = task(intContSimple);
  Drive.moveDistance( 27 , 60 , 1.2);	
  intake_Group.stop();
  Drive.turn( -90 , 100 , .65 );	
  task C1 = task(SNClamp);
  Drive.moveDistance( -22 , 40 , 1 );	
  Drive.turn(45, 100, .9);
  intake_Group.spin(fwd, 100, pct);
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
  task intCont = task(intContSimple);
  Drive.moveDistance(23, 100, 1.1);
  intake_Group.stop();
  Drive.turn( -90 , 100 , .8 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  Drive.turn(45, 100, .9);
  intake_Group.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
//DONE
void simplePosRed(){
  Drive.moveDistance(10, 100, .7);
  Drive.turn(35, 100, .6);
  task intCont = task(intContSimple);
  Drive.moveDistance(22.5, 100, 1.1);
  intake_Group.stop();
  Drive.turn(90 , 100 , .8 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  Drive.turn(-45, 100, .9);
  intake_Group.spin(fwd, 100, pct);
  wait(3, sec);
  Drive.moveDistance(10, 100, .8);
}
void fractalRightStart(){
  Drive.swing(-12, 100, -90, .8);
  Drive.moveDistance(-5, 70, .35);
  Drive.moveDistance(2.05, 100, .3); // 2.35 for metal field

  intake_Group.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.swing(12, 100, -165, .8);
  Drive.moveDistance(33.5, 100, 1);
  intake_Group.stop();
  Drive.turn(-236, 100, .8);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-20, 45, .9);
  Drive.turn(-185, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(28,90, 1);
  intake_Group.stop();
  Drive.turn(-10, 90, 1.1);
  intake_Group.spin(fwd,100, pct);
  wait(3.8, sec);
  intake_Group.stop();
  Drive.moveDistance(34, 100, 1);
}
void fractalLeftStart(){
  Drive.swing(-12, 100, 90, .9);
  Drive.moveDistance(-5, 50, .5);
  Drive.moveDistance(1.7, 100, .3); // 2.35 for metal field

  intake_Group.spin(fwd, 100, pct);
  wait(.5, sec);
  Drive.swing(12, 100, 165, .8);
  Drive.moveDistance(35, 100, 1);
  intake_Group.stop();
  Drive.turn(236, 100, .8);
  task clamp1 = task(sigAWPClamping);
  Drive.moveDistance(-20, 45, .9);
  Drive.turn(180, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(27,90, .9);
  intake_Group.stop();
  Drive.turn(15, 90, 1.1);
  intake_Group.spin(fwd,100, pct);
  wait(3, sec);
  intake_Group.stop();
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
  intake_Group.spin(fwd, -100, pct);
  wait(.23, sec);
  intake_Group.stop();
  lbState=3;
  task ringMid1 = task(ladyBrownMechScoring);
  wait(.75, sec);
  return(0);
}
int hookRemove2(){
  wait(.55, sec);
  intake_Group.spin(fwd, -100, pct);
  wait(.23, sec);
  intake_Group.stop();
  return(0);
}
int intakeWait(){
  wait(.4, sec);
  intake_Group.spin(fwd, 100, pct);
  return(0);
}
int intakeSlowerStop(){  
  wait(2.25, sec);
  intake_Group.stop();
  return(0);
}
int hookSaver(){
  intake_Group.stop();
  wait(.15, sec);
  intake_Group.spin(fwd, 100, pct);
  return(0);
}
int intakeShortWait(){
  wait(.65, sec);
  intake_Group.spin(fwd, 100, pct);
  return(0);
}
int intakePause(){
  wait(.9, sec);
  intake_Group.stop();
  return(0);
}
int intakeOnOff(){
  wait(.35, sec);
  intake_Group.spin(fwd, -100, pct);
  wait(.2, sec);
  intake_Group.spin(fwd, 100, pct);
  return(0);
}

int unclamp(){
  wait(.4, sec);
  clamp.close();
  return(0);
}
int lastClamp(){
  wait(.95, sec);
  clamp.open();
  return(0);
}
int fasterClamping(){
  wait(.7, sec);
  clamp.open();
  return(0);
}

int intContAWPSkills(){
  wait(.15, sec);
  while (!Optical.isNearObject()){
    intake_Group.spin(fwd, 40, pct);
  }
  intake_Group.stop();
  return(0);
}
int upydown(){
  wait(.1, sec);
  intakeLift.close();
  return(0);
}
int doubleSkills(){
  wait(.05, sec);
  intake_Group.stop();
  return(0);
}
int doubleSkills2(){
  wait(.5, sec);
  intake_Group.spin(fwd, 45, pct);
  return(0);
}

int stopyint(){
  wait(.15, sec);
  intake_Group.stop();
  return(0);
}
void simHitSkills(){
  task noJam = task (antiJam);
  Inertial.setRotation(-132.4, deg);
  Optical.setLightPower(100, pct);
  TheOpps.setLightPower(100, pct);
  // shouldReject = true;
  // isRed = true;
  // task onlyReds = task(colorReject);
  lbState = 4;
  task alliance = task(ladyBrownMechScoring);
  wait(.65, sec);
  task slowClamp = task(clamping);
  Drive.moveDistance(-17, 50, .7);
  lbState=0;
  task state0 = task(ladyBrownMechScoring);
  Drive.turn(0, 100, .8);
  intake_Group.spin(fwd,100,pct);
  Drive.moveDistance(20, 100, .7);
  Drive.turn(26, 100, .4);
  task slowUp1 = task(slowUp);
  Drive.moveDistance(50, 80, 1.6);
  Drive.moveDistance(-14.5, 100, .7);
  Drive.turn(180, 100, .8);
  task removeHook = task(hookRemove);
  wait(.2, sec);
  task waitIntake = task(intakeWait);

  Drive.moveDistance(8.5, 100, .7);
  Drive.turn(90, 100, .7);
  intake_Group.spin(fwd, 100, pct);
  task intCont1 = task(intContAWP);
  Drive.moveDistance(10.9, 100, .7);
  lbState = 2;
  task ringScore1 = task(ladyBrownMechScoring);
  Drive.turn(90, 30, .15);
  Drive.moveDistance(6.8, 100, .55);
  Drive.turn(90, 100, .3);
  lbState = 0;
  task saveTheLady = task(ladyBrownMechScoring);
  Drive.moveDistance(-15.2, 100, 1);
  Drive.turn(180, 100, .8);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(33, 70, 1.1);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(45, 25, 1.8);


  Drive.moveDistance(-3, 100, .3);
  Drive.turn(60, 100, .75);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(18, 70, .9);
  Drive.turn(-17, 70, .6);
  Drive.moveDistance(-20, 100, .8);
  wait(.1, sec);
  clamp.close();
  intake_Group.spin(fwd, -100, pct);
  wait(.1, sec);
  Drive.moveDistance(5, 100, .4);
  Drive.turn(-50, 100, .6);
  task superMarioBrosSlow = task(intakeSlowerStop);
  Drive.moveDistance(40, 100, 1);
  Drive.turn(-50, 100, .4);
  task saveTheCaptain = task(intContLower);
  Drive.moveDistance(38, 100, .95);
  Drive.moveDistance(-2, 100, .28);
  Drive.turn(-135, 100, .7);
  task intCont2 = task(intContAWPSkills);
  Drive.moveDistance(46.6, 100, 1.2);

  Drive.turn(-37, 70, .85);
  task fastClamp = task(fasterClamping);
  Drive.moveDistance(-22, 45, .8);
  task onOff = task(intakeOnOff);
  Drive.turn(-44, 100, .25);

  wait(.4, sec);
  Drive.moveDistance(43 , 50 , 1.3);
  Drive.moveDistance(-3, 100, .25);
  task intCont4 = task(intContAWP);
  Drive.turn(-180, 100, .95);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(16, 70, 1);
  Drive.moveDistance(6, 40, .5);
  intake_Group.spin(fwd,100, pct);
  Drive.moveDistance(27, 30, 1.35);
  Drive.moveDistance(-4, 100, .4);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(-50, 100, .7);
  Drive.moveDistance(17, 70, .8);
  Drive.turn(20, 100, .6);
  Drive.moveDistance(-15, 100, .7);
  clamp.close();
  intake_Group.spin(fwd, -100, pct);
  Drive.turn(5.5, 100, .3);
  intake_Group.spin(fwd, 100, pct);
  // //28.4 seconds on 11/16/24 // 34.75 on 11/17/24
  lbState = 1;
  task ladyLift = task(ladyBrownMechScoring);
  intake_Group.spin(fwd, 40, pct);
  Drive.moveDistance(61, 70, 1.7);
  Drive.moveDistance(-7.45, 100, .7);
  task removeHook2 = task(hookRemove2);
  Drive.turn(-90, 100, .7);
  intake_Group.stop();
  lbState = 4; 
  task ladyStake2 = task(ladyBrownMechScoring);
  Drive.moveDistance(7, 100, .5);
  wait(.4, sec);
  Drive.moveDistance(-15, 100, .9, -90);
  Drive.turn(0, 100, .8);
  intake_Group.spin(fwd, 65, pct);
  lbState = 0;
  task ladyReset = task(ladyBrownMechScoring);
  Drive.moveDistance(25, 100, .75);
  task intcont6 = task(intContLower);
  Drive.turn(90, 100, .7);  
  task intCont = task(intContAWPSkills);
  Drive.moveDistance(27, 100, .9);
  Drive.turn(217, 100, 1);
  task lastClamp1 = task(lastClamp);
  Drive.moveDistance(-35, 55, 1.15);
  Drive.turn(144, 100, .65);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(38, 80, 1.3);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(45, 100, .6);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(34.5, 60, 40, 1.2);
  Drive.moveDistance(-2.5, 100, .25);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(12, 70, .6);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(117, 100, .8); 
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(22.5, 60, 180, 1.05);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(200, 100, .5);
  wait(.45, sec);
  clamp.close();
  wait(.1, sec);
  intake_Group.stop();
  Drive.moveDistance(-1000, 100, .6);
  Drive.moveDistance(5, 100, .35);
  Drive.turn(220, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(20, 100, 275, .7);
  Drive.swing(37, 100, 320, .85);
  Drive.swing(23, 100, 285, .73);
  Drive.moveDistance(1000, 100, 2);
  
 

}
void secondHalfSkills(){
  Inertial.setRotation(-90,deg);
  wait(.1, sec);
  Drive.turn(-90, 100, .7);
  intake_Group.stop();
  lbState = 4; 
  task ladyStake2 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .6);
  wait(.4, sec);
  Drive.moveDistance(-16, 100, 1, -90);
  Drive.turn(0, 100, .8);
  intake_Group.spin(fwd, 65, pct);
  lbState = 0;
  task ladyReset = task(ladyBrownMechScoring);
  Drive.moveDistance(25, 100, .75);
  task intcont6 = task(stopyint);
  Drive.turn(90, 100, .7);  
  task intCont = task(intContAWPSkills);
  Drive.moveDistance(25.5, 100, .9);
  Drive.turn(217, 100, 1);
  task lastClamp1 = task(lastClamp);
  Drive.moveDistance(-35, 55, 1.15);
  Drive.turn(144, 100, .65);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(38, 80, 1.3);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(45, 100, .6);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(34, 60, 40, 1.2);
  Drive.moveDistance(-2, 100, .25);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(0, 100, .6);
  Drive.moveDistance(12, 70, .6);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(-5, 100, .4);
  Drive.turn(130, 100, .8); 
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(21, 60, 180, 1);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(200, 100, .5);
  wait(.45, sec);
  clamp.close();
  wait(.1, sec);
  intake_Group.stop();
  Drive.moveDistance(-1000, 100, .55);
  Drive.moveDistance(5, 100, .35);
  Drive.turn(220, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.swing(20, 100, 275, .7);
  Drive.swing(37, 100, 320, .85);
  Drive.swing(23, 100, 280, .73);
  Drive.moveDistance(1000, 100, 2);
  
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
  intake_Group.stop();
  return(0);
}
void ringRushRed(){
  task bonkers = task(redRRBonk);
  intake_Group.spin(fwd,100, pct);
  Drive.swing(39.5, 100, -35, 1);
  Drive.moveDistance(2.3, 100, .25);
  task iStop = task(intContAWP);

  Drive.moveDistance(-9, 100, .7);
  
  Drive.swing(-14.5, 100, -60, .9);
  task C1 = task (redRingRushC1);
  Drive.moveDistance(-8, 60, .6);
  Drive.turn(-65, 100, .3);
  Drive.moveDistance(10, 100, .7);
  intake_Group.spin(fwd, 100, pct);
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
    intake_Group.spin(fwd, 100,pct);
  // }
  

}
int ringRushBLUEONLY(){
  while (true){
    if (Optical.hue() < 10 && !isRed && Optical.isNearObject()){
      intake_Group.stop();
      return(0);
    }
  }
}
void ringRushBlue(){
  task bonkers = task(redRRBonk);
  intake_Group.spin(fwd,60, pct);
  Drive.swing(39.5, 100, 35, 1);
  Drive.moveDistance(2.3, 100, .25);
  Drive.turn(90, 100, .5);
  task iStop = task(intContAWP);
  Drive.turn(35, 100, .5);
  Drive.moveDistance(-7, 100, .7);
  Drive.swing(-14.5, 100, 60, .9);
  task C1 = task (blueRingRushC1);
  Drive.moveDistance(-9, 60, .8);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(65, 100, .3);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(10, 100, .7);
  intake_Group.spin(fwd, 100, pct);
  bonk.close();
  wait(.3, sec);
  Drive.turn(77, 100, .5);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(23, 100, 1);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(200, 100, .9);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(31, 100, 1.15);
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(-10.5, 100, .7);
  intake_Group.spin(fwd, 100, pct);
  Drive.turn(260, 100, .6);
  intakeLift.open();
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(31, 80 , 1.1);
  intake_Group.spin(fwd, 100, pct);
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
    intake_Group.spin(fwd, 100,pct);
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
  intake_Group.spin(fwd, 100, pct);
  Drive.moveDistance(7, 70, .5);
  intakeLift.close();
  Drive.moveDistance(-3, 100, .3);
  Drive.moveDistance(5, 100, .4);
  task iStop = task(intContAWP);
  Drive.turn(0, 100, .65);
  task C1 = task(PTC1);
  Drive.moveDistance(-28, 50, 1);
  intake_Group.spin(fwd, 100, pct);

  
}
void wallstakePosBlue(){
  lbState = 3;
  task ladyStake3 = task(ladyBrownMechScoring);
  Drive.moveDistance(10, 100, .7);
  Drive.turn(-35, 100, .8);
  task iStop = task(intContAWP);
  Drive.moveDistance(23, 100, 1.1);
  intake_Group.stop();
  Drive.turn( -90 , 100 , .9 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  intake_Group.spin(fwd,100, pct);
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
  intake_Group.stop();
  Drive.turn(90 , 100 , .9 );	
  task C1 = task(posClamp);
  Drive.moveDistance( -26 , 40 , 1.8);	
  intake_Group.spin(fwd,100, pct);
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
void testing(){
  Drive.turn(360, 100, 15);
}

int clampNPE(){
  wait(.7, sec);
  clamp.open();
  wait(.4, sec);
  intake_Group.spin(fwd, 100, pct);
  return(0);
}
int delayDropNPE(){
  wait(.4, sec);
  clamp.close();
  return(0);
}
void newPalElims(){
  Optical.setLightPower(100, pct);
  lbState = 3;
  task ladyStake1 = task(ladyBrownMechScoring);
  intake_Group.spin(fwd, 100, pct);
  task iStop = task(intContAWP);
  Drive.swing(25.3, 100, 90, 1.25);
  task C1 = task(clampNPE);
  Drive.moveDistance(-26, 50, 1);
  Drive.swing(50, 80, 175, 2);
  bonk.open();
  intake_Group.stop();
  Drive.moveDistance(17, 60, .9);
  Drive.turn(260, 60, 1);
  bonk.close();
  Drive.turn(250, 50, .3);
  Drive.turn(365, 100, .9);
  intake_Group.spin(fwd, -100, pct);
  task dropG = task (delayDropNPE);
  Drive.moveDistance(40.3, 70, 2);
  Drive.turn(405, 100, .4);


  // Drive.swing(32.5, 100, 49, 1.5);
  // intake_Group.stop();
  lbState = 2;
  task ladyStake2 = task(ladyBrownMechScoring);
  // Drive.moveDistance(16, 100, .9);
  // lbState = 4;
  // task ladyStake3 = task(ladyBrownMechScoring);
  // wait(.45, sec);
  // Drive.moveDistance(-10, 100, .9);


}


void (*autonsList[])() =
{
  simplePosRed, //DONE Preload at bottom of intake_Group on a hook
  simHitSkills, // Done
  simpleNegRed,//DONE
  simpleNegBlue,//DONE 
  redNegElim,// Needs Tuning Est: 30 minutes + Color sort 
  soloSig, // Needs redesigned route Est 2 hours 
  bluePosElim, // Done 
  redPosElim, // Done
  blueNegElim,//DONE STRAIGHT AT RING
  fractalRightStart,
  simplePosBlue,//DONE Preload at bottom of intake_Group on a hook
  newPalElims,
  fractalLeftStart,
  ringRushRed, 
  secondHalfSkills,
  testing,
  wallstakePosRed,
  wallstakePosBlue,
  ringRushBlue,
  blueClampRush,
  redNegElimKALA, //DONE READY Straight at ring
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
    con.Screen.print((upperIntake.temperature(fahrenheit) + lowerIntake.temperature(fahrenheit))/2);
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

  // lbState = 0;
  // task ringOne1 = task(ladyBrownMechScoring);

  // isRed = true;
  // task cReject = task(colorReject);
  task printcon = task(conInfo);
  wait(.01, sec);
  task noJamPorFavor = task(antiJam);
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
      intake_Group.spin(fwd, 100, pct);
    }
    // intake_Group control
    if (!reject){
      if (con.ButtonR2.pressing())
      {
        intake_Group.spin(fwd, -100, pct);
        intakeRev = true;
      }
      else if (!antiJammy){
        if (con.ButtonR1.pressing())
        {
          intake_Group.spin(fwd, 100, pct);
          intakeRev = false;
        }
        else 
        {
          intake_Group.stop();
          intakeRev = false;
        }
    }
  }
    //0,35,145
    //lb controls
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
    if (con.ButtonA.pressing()){
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

    if (con.ButtonDown.pressing()){
      if (f14loop){
        ringRush.open();
      }
      if (!f14loop){
        ringRush.close();
      }
      f15loop = true;
    }
    else if (f15loop){
      f14loop = !f14loop;
      f15loop = false;
    }


    //intakelift
    if (con.ButtonB.pressing()){
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





