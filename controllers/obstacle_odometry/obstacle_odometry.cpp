/**
 * @file    obstacle_odometry.cpp
 * @brief   The robot goes to the other side of the map avoiding the obstacle with odometry
 *
 * @author  @author Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
 * @date    30-11-2014
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
