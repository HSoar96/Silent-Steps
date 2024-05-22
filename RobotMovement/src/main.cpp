#include <globals.h>
#include <robot.h>
#include <EEPROM.h>
#include <triangulation.h>

#define MAX_DRIVE_TIME 1200
#define MIN_DRIVE_TIME 500

Motor *leftMotor;
Motor *rightMotor;
Robot *robot;
double angleToTurn = -1;


void setup() 
{
  Serial.begin(BAUD_RATE);
  // Error codes are retreived from EEPROM and printed.
  GetLastErrors();
  // Error codes are then cleared from EEPROM.
  ClearErrors();

  // Setup the microphones.
  pinMode(MIC_A, INPUT);
  pinMode(MIC_B, INPUT);
  pinMode(MIC_C, INPUT);

  analogReadRes(10);
  
  // Setup robot classes.
  try
  {
    leftMotor = new Motor(EN_1,IN_1,IN_2);
    rightMotor = new Motor(EN_2,IN_3,IN_4); 
    robot = new Robot(leftMotor, rightMotor);
  }
  catch(Error& e)
  {
    HandleError(e);
  } 

  delay(1000);
}

void loop() 
{
  try
  {
    angleToTurn = Listen();
  }
  catch(Error& e)
  {
    HandleError(e);
  }
  
  if(angleToTurn != -1)
  {
    Serial.println(angleToTurn);
    try
    {
      if(angleToTurn < 180)
      {
        robot->TurnRight(angleToTurn);
        robot->MoveForwards(100,random(MIN_DRIVE_TIME,MAX_DRIVE_TIME));
      }
      else
      {
        robot->TurnLeft(360 - angleToTurn);
        robot->MoveForwards(100, random(MIN_DRIVE_TIME,MAX_DRIVE_TIME));
      }
    }
    catch(Error& e)
    {
      HandleError(e);
    }
    angleToTurn = -1;
    delay(500);
  }
}
