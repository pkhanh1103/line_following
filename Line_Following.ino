#include "Omni.h"

Omni myOmni;

int U[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
double irAngle[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 190, 202.5, 225, 247.5, 290, 292.5, 315 , 337.5};
unsigned long timeStamp = 0;

const int irThreshold = 275;
const int angleRange = 75;  // degrees
const int delayDuration = 5;
int angle = 0;
double newAngle = 0;
int count = 0;

const int moveSpeed = 100;

void setup() 
{
  Serial.begin(9600);
  timeStamp = millis();

  /*LineFollowing();
  
  angle += 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 500)
    myOmni.move(angle, moveSpeed);
  
  LineFollowing();*/
}

void loop() 
{
    myOmni.Motor1.spin(true, 250);
}    

void LineFollowing(void)
{
  count = 0;
  while(count < 4)
  {
    //count = 0;
    find_angle();
  
    if(count != 0)
    {
      newAngle = (int)(newAngle * 1.0 / count); 
      if(newAngle < 0)
        newAngle += 360;
      angle = round(newAngle);
      delay(delayDuration);
    }
    else 
      delay(delayDuration);
  
    myOmni.move(angle, 400);
    newAngle = 0;
  }
  myOmni.stop();
}

void find_angle(void)
{
  count = 0;
  
  int minAngle = angle - angleRange;
  if (minAngle < 0) 
    minAngle += 360;    
  
  int maxAngle = angle + angleRange;
  if (maxAngle >= 360)
    maxAngle -= 360;
  
  int value;
  if (minAngle < maxAngle) 
  {    
    for(int i = 0; i < 16; i++) 
    {
      if(irAngle[i] >= minAngle && irAngle[i] <= maxAngle) 
      {
        value = analogRead(U[i]);
        if(value > irThreshold) 
        {
          newAngle += irAngle[i];
          count ++;          
        } 
      }     
    }
  }
  else {
    for(int i = 0; i < 16; i++) 
    {
      if (irAngle[i] >= minAngle || irAngle[i] <= maxAngle) 
      {
        value = analogRead(U[i]);
        if (value > irThreshold) 
        {
          if(irAngle[i] <= maxAngle)
            newAngle += irAngle[i];
          else
            newAngle += (irAngle[i] - 360);
          count ++;
        } 
      }       
    }
  }
}
