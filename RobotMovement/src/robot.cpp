#include <robot.h>

Robot::Robot(Motor *leftMotor, Motor *rightMotor)
{   
    _leftMotor = leftMotor;
    _rightMotor = rightMotor;
}

int Robot::DegreesToTime(int degrees)
{
    return map(degrees, 0, 360, 0, 1075);
}

void Robot::MoveForwards(int speed, int duration)
{
    _leftMotor->Enable(FORWARD, speed);
    _rightMotor->Enable(FORWARD, speed);
    delay(duration);
    this->Stop();
}

void Robot::MoveBackwards(int speed, int duration){
    _leftMotor->Enable(BACKWARD, speed);
    _rightMotor->Enable(BACKWARD, speed);
    delay(duration);
    this->Stop();
}

void Robot::Stop()
{
    _leftMotor->Enable(STOP, 0);
    _rightMotor->Enable(STOP, 0);
}

void Robot::TurnLeft(int degrees)
{
    int turnDuration = DegreesToTime(degrees);
    _leftMotor->Enable(FORWARD, TURN_SPEED);
    _rightMotor->Enable(BACKWARD, TURN_SPEED);
    delay(turnDuration);
    this->Stop();
}

void Robot::TurnRight(int degrees)
{
    int turnDuration = DegreesToTime(degrees);
    _leftMotor->Enable(BACKWARD, TURN_SPEED);
    _rightMotor->Enable(FORWARD, TURN_SPEED);
    delay(turnDuration);
    this->Stop();
}