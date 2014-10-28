/**
 * @file    straight_compass.cpp
 * @brief   A template for webots projects.
 *
 * @author  Javier de Pinto <100284151@alumnos.uc3m.es>
 * @date    10-28-2014
 */

#include "MyRobot.h"

/*
 * Main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
