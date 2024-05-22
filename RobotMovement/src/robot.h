#ifndef ROBOT_DEFINED
#define ROBOT_DEFINED
#include <globals.h>
#include <motor.h>

#define TURN_SPEED 100

class Robot
{
  public:
    Robot(Motor *leftMotor, Motor *rightMotor);

    void MoveForwards(int speed, int duration);
    void MoveBackwards(int speed, int duration);
    void TurnLeft(int degrees);
    void TurnRight(int degrees);
    void Stop();

  private:
    Motor *_leftMotor;
    Motor *_rightMotor;
    int DegreesToTime(int degrees);
};
#endif