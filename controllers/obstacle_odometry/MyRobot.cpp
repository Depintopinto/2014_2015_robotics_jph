
/**
* @file MyRobot.cpp
* @brief The robot goes to the other side of the map avoiding the obstacle with odometry
*
* @author Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
* @date 30-11-2014
*/


#include "MyRobot.h"
//////////////////////////////////////////////
MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;
    //Enable the encoders
    enableEncoders(_time_step);
    //set the initial wheels speed
    _left_speed = 100;
    _right_speed = 100;
    //ser the initial distance and flag
    _distance = 0;
    flag = 1;
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
        if(flag == 2 || flag == 8){
            _distance = _right_encoder/ENCODER_RESOLUTION*WHEEL_RADIO;
        }else{
            _distance = _left_encoder/ENCODER_RESOLUTION*WHEEL_RADIO;
        }

        print_odometry_data();      

        //switch case to make the necesary steps to avoid the obstacle
        switch (flag){
        case 1:
            cout << "linea recta"<< endl;
            goStraight(5);
            break;
        case 2:
            turn_left();
            break;
        case 3:
            goStraight(3.5);
            break;
        case 4:
            turn_right();
            break;
        case 5:
            goStraight( 7);
            break;
        case 6:
            turn_right();
            break;
        case 7:
            goStraight(3.5);
            break;
        case 8:
            turn_left();
            break;
        case 9:
            goStraight(5);
            break;
        default:
            _left_speed = 0;
            _right_speed = 0;
            break;
        }

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
void MyRobot::turn_right()
{
    //if the distance is more tha a 90 degres turn
    if(_distance > 0.56){
        _left_speed = 0;
        _right_speed = 0;
        reset();
        flag ++;
    }
    else{
        _left_speed = MAX_SPEED/10;
        _right_speed = 0;        
    }

}

//////////////////////////////////////////////
void MyRobot::turn_left()
{
    //if the distance is more tha a 90 degres turn
    if(_distance > 0.56){        
        _left_speed = 0;
        _right_speed = 0;
        reset();
        flag ++;
    }
    else{
        _left_speed = 0;
        _right_speed = MAX_SPEED/10;        
    }
}

//////////////////////////////////////////////
void MyRobot::reset()
{
    setEncoders(0,0);    
}

//////////////////////////////////////////////
void MyRobot::goStraight(double dis){

    if(_distance >  dis){
        _left_speed = 0;
        _right_speed = 0;
        reset();
        flag ++;
    }
    else{

        if (_right_encoder > _left_encoder ){
            _left_speed = MAX_SPEED/2;
            _right_speed = (MAX_SPEED/2) - 10;
        }
        else if (_right_encoder  < _left_encoder ){
            _left_speed = (MAX_SPEED/2) - 10;
            _right_speed = (MAX_SPEED/2);
        }
        else{
            _left_speed = (MAX_SPEED/2);
            _right_speed = (MAX_SPEED/2);
        }
    }

}

