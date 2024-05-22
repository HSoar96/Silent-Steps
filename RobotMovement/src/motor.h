#ifndef MOTOR_DEFINED
#define MOTOR_DEFINED
#include <globals.h>

enum directions
{
  FORWARD, 
  BACKWARD,
  LEFT,
  RIGHT,
  STOP
};

class Motor {
  public:
    Motor(int enable, int inA, int inB);
    
    int GetEnable();
    int GetInA();
    int GetInB();

    void Enable(directions dir, int speed);    
    
  private:
    int _enable;
    int _inA;
    int _inB;
    void SetupPins();
};
#endif