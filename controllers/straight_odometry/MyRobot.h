#ifndef MY_ROBOT_H_
#define MY_ROBOT_H_

/**
* @file MyRobot.h
* @brief The robot goes to the other side of the map with odometry
*
* @author Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
* @date 24-11-2014
*/

#include <iostream>
#include <webots/DifferentialWheels.hpp>

using namespace webots;
using namespace std;
#define MAX_SPEED 100
#define ENCODER_RESOLUTION 5
#define WHEEL_RADIO 0.0825



class MyRobot : public DifferentialWheels {
private:
    double _left_encoder, _right_encoder;
    double _left_speed, _right_speed;
    double _distance;
    int _time_step;
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
* @brief Prints the distance and encoders values
* @param
* @return
*/
    void print_odometry_data();
    /**
* @brief Logic to get the desired distance
* @param the desired distance
* @return
*/
    void control(double dis);
    /**
* @brief User defined function for initializing and running the template class.
* @param
* @return
*/
    void run();
};


#endif

