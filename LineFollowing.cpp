#include "LineFollowing.h"

void LineFollowing::lineFollowing(int speed)   
{
  irCount = 0;
  lastCheckLineFollowing = millis();

  //Khi gặp ngã ba/ngã tư, số cảm biến trên line lớn hơn 3
  while(irCount <= 3)
  {
    findAngle();    
    if(millis() - lastCheckLineFollowing >= 2) //Sau mỗi 2 milli giây, tìm góc mới
    {
      if(irCount != 0)
      {
        //Góc mới bằng trung bình của tổng các góc đang nằm trên line
        angle = (int)(angleSum * 1.0 / irCount); 
        if(angle < 0)
          angle += 360;
      }
      lastCheckLineFollowing = millis();
    }
    myOmni.move(angle, speed);
    angleSum = 0;
  }

  //Dừng lại tại ngã ba/ngã tư
  myOmni.stop();
  delay(100);
}

void LineFollowing::findAngle(void)
{
  irCount = 0;
  
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
          angleSum += irAngle[i];
          irCount ++;          
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
            angleSum += irAngle[i];
          else
            angleSum += (irAngle[i] - 360);
          irCount ++;
        } 
      }       
    }
  }
}

void LineFollowing::directionChange(int deltaAngle)
{
  angle += deltaAngle;
  if (angle < 0)
    angle += 360;
  else if (angle > 360)
    angle -= 360;
  
  lastCheckDirectionChange = millis();
  while(millis() - lastCheckDirectionChange <= 200)
    myOmni.move(angle, 150);
  myOmni.stop();
}
