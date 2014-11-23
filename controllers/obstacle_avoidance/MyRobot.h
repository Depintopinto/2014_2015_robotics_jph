/**
 * @file    MyRobot.h
 * @brief   Controller for a robot to avoid obstacles.
 *
 * @author  Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
 * @date    2014-11
 */


#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED 80
#define NUM_DISTANCE_SENSOR 16
#define DISTANCE 100


class MyRobot : public DifferentialWheels {
private:

    int _time_step;

    Compass * _my_compass;
    double _compass_angle;

    double _left_speed, _right_speed;

    double _dist_val[NUM_DISTANCE_SENSOR];
    DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];

    /**
    * @brief Function to get the values of the distance sensors
    * @param
    * @return
    */
    void get_distances();

    /**
    * @brief Send the mode to the motors
    * @param
    * @return
    */
    void mode();

    /**
    * @brief Function that follow the angle we desired
    * @param the desired angle
    * @return
    */
    void follow_compass(double angle);

    /**
    * @brief Function with the logic of the controller
    * that allow the robot to avoid an obstable
    * @param
    * @return
    */
    void control();


    enum Mode {
        FORWARD,
        TURN_LEFT,
        TURN_RIGHT,
        TURN_BACK_LEFT,
        TURN_BACK_RIGHT,
        TURN_LEFT_MORE,
        TURN_RIGHT_MORE
    };

    Mode _mode;

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
    * @brief Function with the logic of the controller
    * @param
    * @return
    */
    void run();

    /**
    * @brief Converting bearing vector from compass to angle (in degrees).
    * @param bearing vector of compass
    * @return
    */
    double convert_bearing_to_degrees(const double* in_vector);


};

