#include "Omni.h"

Omni myOmni;

//Các mảng về cảm biến và góc
int U[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
double irAngle[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 190, 202.5, 225, 247.5, 290, 292.5, 315 , 337.5};

//Các hằng số về cảm biến, góc
const int irThreshold = 275;
const int angleRange = 75;    //Góc quét (độ)
const int delayDuration = 5;

//Các biến tìm góc
int angle = 0;
double newAngle = 0;
int count = 0;

//Các biến thời gian
unsigned long timeStamp = 0;

void setup() 
{
  Serial.begin(9600);
  timeStamp = millis();

  LineFollowing();
  
  angle += 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();

  angle -= 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();

  angle -= 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();

  angle += 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();

  angle += 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();

  angle -= 90;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  timeStamp = millis();
  while (millis() - timeStamp <= 300)
    myOmni.move(angle, 100);
  myOmni.stop();
  
  LineFollowing();
}

void loop() 
{
}    

void LineFollowing(void)
{
  count = 0;
  while(count < 4)
  {
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
  
    myOmni.move(angle, 250);
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
