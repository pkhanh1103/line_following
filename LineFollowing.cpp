#include "LineFollowing.h"

/* ----- Nội dung các hàm ----- */
void LineFollowing::lineFollowing(int speed)   
{
  irCount = 0;
  lastCheckLineFollowing = millis();

  //Khi gặp ngã ba/ngã tư, số cảm biến trên line lớn hơn 3
  while(irCount <= 3)
  {
    findAngle();    
    if(millis() - lastCheckLineFollowing >= 5) //Sau mỗi 5 milli giây, tìm góc mới
    {
      if(irCount != 0)
      {
        //Góc mới bằng trung bình của tổng các góc đang nằm trên line
        newAngle = (int)(newAngle * 1.0 / irCount); 
        if(newAngle < 0)
          newAngle += 360;
        angle = round(newAngle);
      }
      lastCheckLineFollowing = millis();
    }
    myOmni.move(angle, speed);
    newAngle = 0;
  }

  //Dừng lại tại ngã ba/ngã tư
  myOmni.stop();
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
          newAngle += irAngle[i];
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
            newAngle += irAngle[i];
          else
            newAngle += (irAngle[i] - 360);
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
  while(millis() - lastCheckDirectionChange <= 100)
    myOmni.move(angle, 200);
  myOmni.stop();
}

