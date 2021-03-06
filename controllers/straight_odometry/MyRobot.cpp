/**
* @file MyRobot.h
* @brief The robot goes to the other side of the map with odometry
*
* @author Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
* @date 24-11-2014
*/


#include "MyRobot.h"
//////////////////////////////////////////////
MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;
    enableEncoders(_time_step);
    _left_speed = 100;
    _right_speed = 100;
    _distance = 0;
}
//////////////////////////////////////////////
MyRobot::~MyRobot()
{
    disableEncoders();
}
//////////////////////////////////////////////
void MyRobot::run()
{
    while (step(_time_step) != -1)
    {
        //Get the encoder values
        _left_encoder = getLeftEncoder();
        _right_encoder = getRightEncoder();

        //Converts rad to meters
        _distance = _left_encoder/ENCODER_RESOLUTION*WHEEL_RADIO;

        print_odometry_data();

        control(17.5);

        setSpeed(_left_speed, _right_speed);
    }
}
//////////////////////////////////////////////
void MyRobot::print_odometry_data()
{
    cout<< "Left Enc: " << _left_encoder << endl << "Right Enc: " << _right_encoder
        << endl << "Distance: " << _distance << endl;
}

//////////////////////////////////////////////
void MyRobot::control(double dis)
{
    if (_distance > dis){
        _left_speed = 0;
        _right_speed = 0;
    }
    else{

        if (_right_encoder > _left_encoder ){             
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED - 10;
        }
        else if (_right_encoder  < _left_encoder ){
            _left_speed = MAX_SPEED - 10;
            _right_speed = MAX_SPEED;
        }
        else{
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
        }
    }
}
