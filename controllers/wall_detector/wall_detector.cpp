/**
 * @file    wall_detector.cpp
 * @brief   Controller to detect walls.
 *
 * @author  Javier de Pinto Hernández <100284151@alumnos.uc3m.es>
 * @date    30-11-2014
 */

#include "MyRobot.h"

int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
