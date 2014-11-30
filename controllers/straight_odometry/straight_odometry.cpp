/**
* @file straight_odometry.cpp
* @brief The robot goes to the other side of the map with odometry
*
* @author Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
* @date 24-11-2014
*/

#include "MyRobot.h"

/**
 * @brief Main program.
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}

