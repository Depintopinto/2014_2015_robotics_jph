/**
 * @file    MyRobot.h
 * @brief   Controller to detect walls.
 *
 * @author  Javier de Pinto Hernández <100284151@alumnos.uc3m.es>
 * @date    30-11-2014
 */

#include <iostream>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;


class MyRobot : public DifferentialWheels {
private:
    int _time_step;

    Camera * _forward_camera;

    double _left_speed, _right_speed;

public:
    /**
    * @brief Empty constructor of the class.
    * @param
    * @return
    */
    MyRobot();

    /**
    * @brief Destructor of the class.
    * @param
    * @return
    */
    ~MyRobot();

    /**
    * @brief User defined function for initializing and running the template class.
    * @param
    * @return
    */
    void run();
};
