#include "LineFollowing.h"

LineFollowing myRobot;

int speed = 250;

void setup() 
{
  myRobot.lineFollowing(speed);
  myRobot.directionChange(90);
  myRobot.lineFollowing(speed);
  myRobot.directionChange(-90);
  myRobot.lineFollowing(speed);
  myRobot.directionChange(-90);
  myRobot.lineFollowing(speed);
}

void loop() 
{
}    
