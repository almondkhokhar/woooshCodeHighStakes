#include "vex.h"
using namespace vex;

double angularDistanceToLinearDistance(double angularDistance, double diameter, double gearRatio)
{
    return angularDistance * M_PI / 180.0 * gearRatio * (diameter / 2.0);
}

double clamp(double value, double min, double max)
{
    // if the value is less than the min then just return the min
    if (value < min)
    {
        return min;
    }

    // if the value excedes the maximimum then return the max
    if (value > max)
    {
        return max;
    }

    // else return the origional value
    return value;
}

double clamp_min(double value, double min)
{
    // if the value is less than the min then just return the min
    if (value < min)
    {
        return min;
    }

    // else return the origional value
    return value;
}

double clamp_max(double value, double max)
{
    // if the value excedes the maximimum then return the max
    if (value > max)
    {
        return max;
    }

    // else return the origional value
    return value;
}

toggleBoolObject::toggleBoolObject(bool initialValue)
{
    firstLoop = true;
    toggleValue = initialValue;
}

void toggleBoolObject::setValue(bool value)
{
    toggleValue = value;
}

void toggleBoolObject::changeValueFromInput(bool buttonValue)
{

    if (buttonValue)
    {
        if (firstLoop)
        {
            firstLoop = false;
            toggleValue = !toggleValue;
        }
    }
    else
    {
        firstLoop = true;
    }
}

bool toggleBoolObject::getValue()
{
    return toggleValue;
}