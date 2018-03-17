#include "Omni.h"
#include "definition.h"

const int sampleRate = 7;
const double kp = 7;
const double ki = 12;
const double kd = 0.02;

Omni::Omni():
  Motor1(IN1, IN2, EN1, A1, B1),
  Motor2(IN3, IN4, EN2, A2, B2),
  Motor3(IN5, IN6, EN3, A3, B3)
{
  Motor1.pidSet(kp, ki, kd, sampleRate);
  Motor2.pidSet(kp, ki, kd, sampleRate);
  Motor3.pidSet(kp, ki, kd, sampleRate);    
}

void Omni::stop(void)
{
  Motor1.stop();  
  Motor2.stop();
  Motor3.stop();
}

void Omni::rotate(boolean typeRot, double speed)
{
  if (typeRot == true)
  {
    Motor1.spin(true, speed);
    Motor2.spin(true, speed);
    Motor3.spin(true, speed);
  }
  else
  {
    Motor1.spin(false, speed);
    Motor2.spin(false, speed);
    Motor3.spin(false, speed);
  }
}

void Omni::move(int angle, double speed)
{
  sine = sin(angle * PI / 180.0);
  cosine = cos(angle * PI / 180.0);
  V3 = sine;
  V1 = -(sqrt(3) * cosine + sine) * 0.5;
  V2 = (sqrt(3) * cosine - sine) * 0.5;

  maxSpeed = abs(V1);
  if(maxSpeed < abs(V2))
    maxSpeed = abs(V2);
  if(maxSpeed < abs(V3))
    maxSpeed = abs(V3);

  V1 = V1 * (speed / maxSpeed);
  V2 = V2 * (speed / maxSpeed);
  V3 = V3 * (speed / maxSpeed);

  if(V1 >= 0)
    Motor1.spin(true, abs(V1));
  else 
    Motor1.spin(false, abs(V1));

  if(V2 >= 0)
    Motor2.spin(true, abs(V2));
  else 
    Motor2.spin(false, abs(V2));

  if(V3 >= 0)
    Motor3.spin(true, abs(V3));
  else 
    Motor3.spin(false, abs(V3));
}
