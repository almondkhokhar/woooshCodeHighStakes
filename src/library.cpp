#include "vex.h"
using namespace vex;

double angularDistanceToLinearDistance(double angularDistance, double diameter, double gearRatio)
{
    return angularDistance * M_PI / 180.0 * gearRatio * (diameter / 2.0);
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