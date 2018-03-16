#include "Omni.h"

const int sampleRate = 10;
const double kp = 7;
const double ki = 7;
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

void Omni::rotate(boolean typeRot, double RPM)
{
  if (typeRot == true)
  {
    Motor1.spin(true, RPM);
    Motor2.spin(true, RPM);
    Motor3.spin(true, RPM);
  }
  else
  {
    Motor1.spin(false, RPM);
    Motor2.spin(false, RPM);
    Motor3.spin(false, RPM);
  }
}

void Omni::move(int angle, double RPM)
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

  V1 = V1 * (RPM / maxSpeed);
  V2 = V2 * (RPM / maxSpeed);
  V3 = V3 * (RPM / maxSpeed);

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
