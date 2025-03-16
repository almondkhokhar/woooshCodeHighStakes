#include "vex.h"
using namespace vex;

//**********************//
// constructor function //
//**********************//

drivetrainObj::drivetrainObj(double wheelDiam, double gR)
{
    wheelDiameter = wheelDiam;
    gearRatio = gR;
}

//****************//
// public members //
//****************//

void drivetrainObj::runLeftSide(double voltage)
{
    leftDrive_Group.spin(fwd, nearbyint(voltage), vex::voltageUnits::mV);
}

void drivetrainObj::runRightSide(double voltage)
{
    rightDrive_Group.spin(fwd, nearbyint(voltage), vex::voltageUnits::mV);
}

void drivetrainObj::stopLeftSide(vex::brakeType brakeType)
{
    leftDrive_Group.stop(brakeType);
}

void drivetrainObj::stopRightSide(vex::brakeType brakeType)
{
    rightDrive_Group.stop(brakeType);
}

void drivetrainObj::setBrakeType(vex::brakeType brakeType)
{
    leftDrive_Group.setStopping(brakeType);
    rightDrive_Group.setStopping(brakeType);
}

void drivetrainObj::moveDistance(double targetDistance, double maxSpeed, double timeout, double correctHeading)
{
    // initalize objects for PID control
    MiniPID distanceControl(1100, 0,1000);
    MiniPID headingControl(550, 1, 1000);
    // configure pid controls
    distanceControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);
    headingControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);

    // track inital values to use for calculating total change
    double startPos = getDriveEncoderValue();
    double startAngle = correctHeading;
    double startTime = vex::timer::system();

    // condition exits loops after some amount of time has passed
    while (vex::timer::system() - startTime <= timeout * 1000)
    {
        // calculate the total distance the encoder has traveled in degrees
        double encoderDistance = getDriveEncoderValue() - startPos;

        // converts the encoder distance to inches traveled
        double travelDistance = angularDistanceToLinearDistance(encoderDistance, wheelDiameter, gearRatio);
        // stores the current heading of the robot
        double actualAngle = correctHeading;
        // gets ouptput from pid controller for travel speed
        double output = distanceControl.getOutput(travelDistance, targetDistance);
        // gets output from pid controller for turning speed
        double correctionFactor = headingControl.getOutput(actualAngle, startAngle);

        if (true)
        {
            runLeftSide(output + correctionFactor);
            runRightSide(output - correctionFactor);
        }
        else
        {
            runLeftSide(output);
            runRightSide(output);
        }
        wait(20, msec);
        
    }
    stopLeftSide(vex::brakeType::coast);
    stopRightSide(vex::brakeType::coast);
}
void drivetrainObj::moveDistanceTimeout(double targetDistance, double maxSpeed, double timeout, bool correctHeading)
{
    // initalize objects for PID control
    MiniPID distanceControl(1100, 0,1000);
    MiniPID headingControl(550, 1, 1000);
    // configure pid controls
    distanceControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);
    headingControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);

    // track inital values to use for calculating total change
    double startPos = getDriveEncoderValue();
    double startAngle = Inertial.rotation(deg);
    double startTime = vex::timer::system();
    double prevVal = 0;
    double counter= 0;
    // condition exits loops after some amount of time has passed
    while (vex::timer::system() - startTime <= timeout * 1000)
    {
        // calculate the total distance the encoder has traveled in degrees
        double encoderDistance = getDriveEncoderValue() - startPos;
        

        // converts the encoder distance to inches traveled
        double travelDistance = angularDistanceToLinearDistance(encoderDistance, wheelDiameter, gearRatio);
        // stores the current heading of the robot
        double actualAngle = Inertial.rotation(deg);
        // gets ouptput from pid controller for travel speed
        double output = distanceControl.getOutput(travelDistance, targetDistance);
        // gets output from pid controller for turning speed
        double correctionFactor = headingControl.getOutput(actualAngle, startAngle);

        if (correctHeading)
        {
            runLeftSide(output + correctionFactor);
            runRightSide(output - correctionFactor);
        }
        else
        {
            runLeftSide(output);
            runRightSide(output);
        }
        
        if (encoderDistance -.05 > prevVal){
            counter +=1;

        }

        if (counter > 20){
            break;
        }
        
        wait(20, msec);
    }
    stopLeftSide(vex::brakeType::coast);
    stopRightSide(vex::brakeType::coast);
}

void drivetrainObj::moveDistance(double targetDistance, double maxSpeed, double timeout)
{
    moveDistance(targetDistance, maxSpeed, timeout, true);
}

void drivetrainObj::swing(double targetDistance, double maxSpeed, double targetAngle, double timeout)
{
    // initalize objects for PID control
    MiniPID distanceControl(1100, 5, 5000);
    MiniPID headingControl(300, 2, 1200);
    // configure pid controls
    distanceControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);
    headingControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);

    // track inital values to use for calculating total change
    double startPos = getDriveEncoderValue();
    double startAngle = Inertial.rotation(deg);
    double startTime = vex::timer::system();
    double currTargetAngle = Inertial.rotation(deg);

    // condition exits loops after some amount of time has passed
    while (vex::timer::system() - startTime <= timeout * 1000)
    {
        // calculate the total distance the encoder has traveled in degrees
        double encoderDistance = getDriveEncoderValue() - startPos;
        // converts the encoder distance to inches traveled
        double travelDistance = angularDistanceToLinearDistance(encoderDistance, wheelDiameter, gearRatio);
        // stores the current heading of the robot
        double actualAngle = Inertial.rotation(deg);
        // cacluates the percent of distance driven to target distance
        double fracComplete = travelDistance / targetDistance;
        // sets current target angle to that percentage between the start agnle and the final target angle
        currTargetAngle = (targetAngle - startAngle) * fracComplete + startAngle;
        // gets ouptput from pid controller for travel speed
        double output = distanceControl.getOutput(travelDistance, targetDistance);
        // gets output from pid controller for turning speed
        double correctionFactor = headingControl.getOutput(actualAngle, currTargetAngle);

        // sends command to run motors at desired speeds
        runLeftSide(output + correctionFactor);
        runRightSide(output - correctionFactor);
        wait(20, msec);
    }
    stopLeftSide(vex::brakeType::coast);
    stopRightSide(vex::brakeType::coast);
}

void drivetrainObj::turn(double targetAngle, double maxSpeed, double timeout)
{
    // initalize object for PID control
    MiniPID angleControl(400, 2, 3000);
    // configure PID controller
    angleControl.setOutputLimits(-120 * maxSpeed, 120 * maxSpeed);
    angleControl.setMaxIOutput(0);
    // store the inital time
    double startTime = vex::timer::system();

    // condition exits loops after some amount of time has passed
    while (vex::timer::system() - startTime <= timeout * 1000)
    {
        // stores the robots current heading
        double actualAngle = Inertial.rotation(deg);
        // gets output from PID controller for desired turn spped
        double output = angleControl.getOutput(actualAngle, targetAngle);

        // only introduce the integral portion of the PID if the robot is within 5 degrees of the target
        // this helps to prevent overshoot and integral windup
        if (fabs(targetAngle - actualAngle) < 5)
        {
            angleControl.setMaxIOutput(2000);
        }
        // set the motors to the desired speed
        runLeftSide(output);
        runRightSide(-output);
        wait(10, msec);
        printf("\n%f", Inertial.rotation(deg));
        
    }
    stopLeftSide(vex::brakeType::coast);
    stopRightSide(vex::brakeType::coast);
}

//*****************//
// private members //
//*****************//

double drivetrainObj::getLeftDriveEncoderValue()
{
    return (left1.position(deg)+left2.position(deg))/2;
}

double drivetrainObj::getRightDriveEncoderValue()
{
    return (right2.position(deg)+right2.position(deg))/2;
}

double drivetrainObj::getDriveEncoderValue()
{
    return (getLeftDriveEncoderValue() + getRightDriveEncoderValue()) / 2;
}