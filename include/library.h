#ifndef LIBRARY_H
#define LIBRARY_H

#include "vex.h"
using namespace vex;

/**
 * @brief converts angular distance to linear distance
 *
 * @param angularDistance (deg)
 * @param diameter the diameter of angular object
 * @param gearRatio the mechanical advantage from the input angle to the output angle
 * @return double (inches)
 */
extern double angularDistanceToLinearDistance(double angularDistance, double diameter, double gearRatio);

/**
 * @brief returns the value bounded by a maximum and/or minimum limit.
 * 
 * @param value 
 * @param min 
 * @param max 
 * @return double 
 */

class toggleBoolObject
{
public:
    /**
     * @brief Construct a new toggle Boolean object
     * @param initialValue the value the boolean will be set to initaly
     */
    toggleBoolObject(bool initialValue);

    /**
     * @brief Set the Boolean objects value manually
     *
     * @param value the value the boolean will be manually set to
     */
    void setValue(bool value);

    /**
     * @brief changes the boolean object's value based on input from the controller
     * on the first loop in which the button value is true the objects's value will toggle
     * subsequent loops will not change the value until the button value becomes false again
     *
     * @param buttonValue whether the button is being pressed. Used to determine if the boolean object should be toggled
     */
    void changeValueFromInput(bool buttonValue);

    /**
     * @brief Get the Value of the boolean object
     *
     * @return true
     * @return false
     */
    bool getValue();

private:
    void init();
    bool firstLoop;
    bool toggleValue;
};

#endif