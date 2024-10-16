#include "vex.h"
using namespace vex;


//function to declare drivetrain parameters
drivetrainObj::drivetrainObj(double wheelDiameterInput, double gearLPlusRatioInput)
{
    wheelDiameter = wheelDiameterInput;
    gearRatio = gearLPlusRatioInput;
}


//encoder values used to calculate distance travelled 
double drivetrainObj::getLeftEncoderValue()
{
    return leftdrive.position(deg);
}

double drivetrainObj::getRightEncoderValue()
{
    return rightdrive.position(deg);
}

double drivetrainObj::getEncoderValue()
{
    return ((getLeftEncoderValue() + getRightEncoderValue()) / 2.0);
}
void drivetrainObj::move(double targetDistance, double timeout)
{
    //arbitrary number used to get the majority of the distance travelled by driving at a proportional speed to the distance remaining to travel
    double distKp = 1000.0;
    //arbitrary number used to keep the robot driving in a straight line by adjusting the difference in speed of the two sides of the drivetrain
    double turnKp = 0.0;

    double distKi = 0.0;

    double turnKi = 0.0;

    double distKd = 0.0;

    double turnKd = 0.0;
    // records a starting position of the bot
    double startAng = Inertial.rotation(deg);
    double startPos = Drive.getEncoderValue();
    // establishes when we started the procedure
    int startTime = vex::timer::system();
    double errorSum = 0;
    double turnErrorSum = 0;
    bool firstLoop = true;
    double turnPrevError;
    double prevError = 0;
    double turnErr = 0;
    double error = targetDistance;
    double velocity;
    double turnVelocity;
    // limits the time the procedure can run
    while (vex::timer::system() - startTime < timeout * 1000)
    {
        // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
        prevError=error;
        turnPrevError=turnErr;
        double currentDistance = (Drive.getEncoderValue() - startPos) * M_PI / 180 * 3.25 / 2;
        error = targetDistance - currentDistance;
        // calculates the difference between our current angle and our initial angle
        double turnErr = startAng - Inertial.rotation(deg);
        errorSum += distKi * error * .02;
        turnErrorSum += turnErr * turnKi * .02;
        velocity = (prevError-error)/.02;
        turnVelocity = (turnPrevError-turnErr)/.02;
        double speed = error * distKp + errorSum  -  velocity * distKd;
        double turnSpeed = turnErr * turnKp + turnErrorSum - turnVelocity * turnKd;
        // set the drive to the correct speed
        rightdrive.spin(fwd, speed - turnSpeed, vex::voltageUnits::mV);
        leftdrive.spin(fwd, speed + turnSpeed, vex::voltageUnits::mV);

        wait(20, msec);
    }
    leftdrive.stop(brake);
    rightdrive.stop(brake);
}

void drivetrainObj::swing(double targetDistance, double timeout, double turnMult, double distKp, bool RightSide)
{

    // records a starting position of the bot
    double startPos = (right1.position(deg) + left1.position(deg)) / 2.0;
    // records a starting position of the bot 
    int startTime = vex::timer::system();
    // limits the time the procedure can run
    while (vex::timer::system() - startTime < timeout * 1000)
    {
        // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
        double speed = (targetDistance - (Drive.getEncoderValue() - startPos) * M_PI / 180 * wheelDiameter / 2) * distKp;
        // set the drive to the correct speed
        if (RightSide) {
        rightdrive.spin(fwd, speed * turnMult, pct);
        leftdrive.spin(fwd, speed, pct);
        }
        else
        {
        rightdrive.spin(fwd, speed, pct); 
        leftdrive.spin(fwd, speed * turnMult, pct);

        }
        
        wait(10, msec);
    }
    leftdrive.stop();
    rightdrive.stop();
}

void drivetrainObj::turn(double targetAngle, double timeout)
{
    // establishes when the turn started
    int startTime = vex::timer::system();
    double speed;
    double Kp = .28;
    double Ki = .28;
    double Kd = .28;
    double error;
    double errorSum=0;
    double prevError;
    double velocity;
    bool firstLoop = true;
    // limits the time so that it doesn't waste time fixing marginal error
    while (vex::timer::system() - startTime < timeout * 1000)
    {
        if (firstLoop){
        prevError=error;
        firstLoop=false;
        }
        else {
        prevError= error;
        }
        errorSum += error;
        velocity = (error-prevError)/.01;
        error =(targetAngle - Inertial.rotation(deg));
        speed = error * Kp + errorSum * Ki - velocity * Kd;
        rightdrive.spin(fwd, -speed, pct);
        leftdrive.spin(fwd, speed, pct);
        wait(10, msec);
        // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    }
    // stops slowly opposed to abruptly
    leftdrive.stop();
    rightdrive.stop();
}