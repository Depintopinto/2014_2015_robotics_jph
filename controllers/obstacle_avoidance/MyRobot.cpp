/**
 * @file    MyRobot.h
 * @brief   Controller for a robot to avoid obstacles.
 *
 * @author  Javier de Pinto Hernandez <100284151@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

    //Get and enable the distance sensors
    _distance_sensor[0] = getDistanceSensor("ds0");    
    _distance_sensor[1] = getDistanceSensor("ds1");    
    _distance_sensor[2] = getDistanceSensor("ds2");    
    _distance_sensor[3] = getDistanceSensor("ds3");    
    _distance_sensor[4] = getDistanceSensor("ds4");    
    _distance_sensor[5] = getDistanceSensor("ds5");    
    _distance_sensor[6] = getDistanceSensor("ds6");    
    _distance_sensor[7] = getDistanceSensor("ds7");    
    _distance_sensor[8] = getDistanceSensor("ds8");    
    _distance_sensor[9] = getDistanceSensor("ds9");    
    _distance_sensor[10] = getDistanceSensor("ds10");    
    _distance_sensor[11] = getDistanceSensor("ds11");    
    _distance_sensor[12] = getDistanceSensor("ds12");    
    _distance_sensor[13] = getDistanceSensor("ds13");    
    _distance_sensor[14] = getDistanceSensor("ds14");    
    _distance_sensor[15] = getDistanceSensor("ds15");

    for(int i=0; i<NUM_DISTANCE_SENSOR; i++)
    {
        _distance_sensor[i]->enable(_time_step);
    }

    //Start the robot with the mode FORWARD
    _mode = FORWARD;
}

//////////////////////////////////////////////
MyRobot::~MyRobot()
{
    _my_compass->disable();
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////
void MyRobot::run()
{
    double sum;
    while (step(_time_step) != -1)
    {
        get_distances();
        sum = 0;

        for (int i = 0; i < NUM_DISTANCE_SENSOR; i++)
        {
            sum = sum + _dist_val[i];
        }
        /*Checks if there is any distance sensor detecting a wall
          and if this wall is close enought (200) to change the mode
          from follow_compass to control */
        if (sum <= 200)
        {
            follow_compass(45);
        }        
        else
        {
            control();
            mode();
        }
        // Set the motor speeds        
        setSpeed(_left_speed, _right_speed);
    }
}
//////////////////////////////////////////////
double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);
    return deg;
}

//////////////////////////////////////////////
void MyRobot::follow_compass(double angle)
{
    // Read the sensors
    const double *compass_val = _my_compass->getValues();

    // Convert compass bearing vector to angle, in degrees
    _compass_angle = convert_bearing_to_degrees(compass_val);

    // Print sensor values to console
    cout << "Following compass angle (degrees): " << _compass_angle << endl;

    // Control the direction to the desired angle
    if (_compass_angle < (angle - 1))
    {
        // Turn right
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED /1.25;
    }
    else {
        if (_compass_angle > (angle + 1)) {
            // Turn left
            _left_speed = MAX_SPEED /1.25;
            _right_speed = MAX_SPEED;
        }
        else {
            // Move forward
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
        }
    }
}

//////////////////////////////////////////////
void MyRobot::mode()
{
    // Send the desired speed mode to the wheels
    switch (_mode){
    case FORWARD:
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED;
        break;
    case TURN_LEFT:
        _left_speed = MAX_SPEED / 1.3;
        _right_speed = MAX_SPEED;
        break;
    case TURN_RIGHT:
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED / 1.3;
        break;
    case TURN_LEFT_MORE:
        _left_speed = MAX_SPEED / 1.4;
        _right_speed = MAX_SPEED;
        break;
    case TURN_RIGHT_MORE:
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED / 1.4;
        break;
    case TURN_BACK_LEFT:
        _left_speed = -MAX_SPEED / 15.0;
        _right_speed = -MAX_SPEED / 5.0;
        break;
    case TURN_BACK_RIGHT:
        _left_speed = -MAX_SPEED / 5.0;
        _right_speed = -MAX_SPEED / 15.0;           
        break;      
    default:
        break;
    }
}

//////////////////////////////////////////////
void MyRobot::get_distances()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++)
    {
        _dist_val[i] = _distance_sensor[i]->getValue();
    }
}

//////////////////////////////////////////////

void MyRobot::control()
{
    // Read the compass sensor and convert compass bearing vector to angle, in degrees
    const double *compass_val = _my_compass->getValues();
    _compass_angle = convert_bearing_to_degrees(compass_val);

    //If the robot detect the end of a wall at the right side, and the compass point to rigth position
    //the robot start turning rigth
    if((((_dist_val[12]>400)||(_dist_val[11]>400))&& (_dist_val[0]==0) && (_dist_val[15]==0) && (_dist_val[13]==0) && (_dist_val[14]==0)&&(_dist_val[5]==0 || _dist_val[6]==0 || _dist_val[9]==0 || _dist_val[10] ==0)) && (_compass_angle>-100 && _compass_angle<100))
    {
        _mode = TURN_RIGHT_MORE;
        cout << "End right wall" << endl;
    }

    //If the robot detect the end of a wall at the left side, and the compass point to rigth position
    //the robot start turning left
    if((((_dist_val[3]>400)||(_dist_val[4]>400))&& (_dist_val[2]==0)&& (_dist_val[0]==0) && (_dist_val[15]==0) && (_dist_val[1]==0) && (_dist_val[14]==0)&&(_dist_val[5]==0 || _dist_val[6]==0 || _dist_val[9]==0 || _dist_val[10] ==0)) && (_compass_angle>0 && _compass_angle<200))
    {
        _mode = TURN_LEFT_MORE;
        cout << "End left wall" << endl;
    }

    //If the robot detect a wall in front
    if(((_dist_val[0]>DISTANCE || _dist_val[15]> DISTANCE) || (_dist_val[1]>3*DISTANCE || _dist_val[14]>3*DISTANCE)) && (_dist_val[7]<200 || _dist_val[8]<200))
    {
        //This if-else choose which side of the robot is near to the wall
        //and turn to that side
        if(_dist_val[3] == 0 && _dist_val[12] == 0)
        {
            if((_dist_val[2] > _dist_val[13]) || (_dist_val[1] > _dist_val[14]) || (_dist_val[0] > _dist_val[15]))
            {
                _mode = TURN_BACK_LEFT;
                cout << "left wall" << endl;
            }
            else
            {
                _mode = TURN_BACK_RIGHT;
                cout << "rigth wall" << endl;
            }

        }
        else
        {
            if(_dist_val[3] > _dist_val[12])
            {
                _mode = TURN_BACK_LEFT;
                cout << "left wall" << endl;
            }
            else
            {
                _mode = TURN_BACK_RIGHT;
                cout << "right wall" << endl;
            }
         }
    }
    else
    {
        //Logic to follow a wall depending if it is too close or too far to the wall
        if(((_dist_val[2]> 4*DISTANCE) || (_dist_val[13]< 3*DISTANCE  && _dist_val[13]!=0)) && (_dist_val[1]==0 || _dist_val[14]==0))
        {
            _mode = TURN_RIGHT;
            cout << "turn right" << endl;
        }
        else
        {
            if((_dist_val[13]> 4*DISTANCE || (_dist_val[3]< 3*DISTANCE && _dist_val[3]!=0)) && (_dist_val[1]==0 || _dist_val[14]==0))
            {
                _mode = TURN_LEFT;
                cout << "turn left" << endl;
            }
            else
            {
                //If the robot detects a wall behind it
                if (_dist_val[7] > 5*DISTANCE || _dist_val[6] > 3*DISTANCE || _dist_val[9] > 3*DISTANCE || _dist_val[8] > 5*DISTANCE)
                {
                    _mode = FORWARD;
                    cout << "forward" << endl;
                }
            }
        }
    }
}
