/* 
 * Motor Library, for controlling Srobot Omni motor
 * Creat  ed by Khanh Pham Feb 02, 2018 
 */

#include "Motor.h"

Motor::Motor(int _INa, int _INb, int _EN, int _A, int _B):
  myEnc(_A, _B),
  myPID(&speed, &pwm, &speedSet, 7.00, 10.00, 0.05, DIRECT),   //Đặt tham số PID
  myFilter(0.05, 0.05, 0.005) //Lọc nhiễu Kalman
{
  INa = _INa;   //Chân IN1 của module L298 - điều khiển cực dương của motor
  INb = _INb;   //Chân IN1 của module L298 - điều khiển cực âm của motor
  EN = _EN;     //Chân ENABLE của module L298 - điều khiển tốc độ motor
  A = _A;       //Kênh A của encoder gắn với motor
  B = _B;       //Kênh B của encoder gắn với motor

  //Setup các chân
  pinMode(INa, OUTPUT);
  pinMode(INb, OUTPUT);
  pinMode(EN, OUTPUT);

  //Setup PID
  myPID.SetMode(AUTOMATIC);  //Khởi động PID
  
  //Reset thông số
  speed = 0;
  pwm = 0;
  speedSet = 0;
  oldPosition = 0;
  newPosition = 0;  
}

/*void Motor::pidSet(double kp, double ki, double kd, int _sampleRate)
{
  sampleRate = _sampleRate;
  myPID.SetTunings(kp, ki, kd);
  myPID.SetSampleTime(sampleRate);
  now = millis();
  lastCheck = millis();
}*/

void Motor::spin(bool direction, double _speedSet)
{
  if (_speedSet == 0)
  {
    digitalWrite(INa, 0);
    digitalWrite(INb, 0);
    return;
  }
  if (direction == true)
  {
    digitalWrite(INa, 1);
    digitalWrite(INb, 0);  
  }
  else
  {
    digitalWrite(INa, 0);
    digitalWrite(INb, 1);
  }
  
  speedSet = _speedSet;
  now = millis();
  
  //Thực hiện PID sau mỗi chu kì lấy mẫu
  if (now - lastCheck >= sampleRate)
  {
    newPosition = myEnc.read();
    speed = abs(newPosition - oldPosition) * 60000 / 1734 / sampleRate;
    speed = myFilter.updateEstimate(speed);
    oldPosition = newPosition;
    lastCheck = now;
  }

  myPID.Compute();
  analogWrite(EN, pwm);
}

void Motor::stop(void)
{
  //Cung cấp đồng thời một mức điện áp vào hai cực của motor
  //tạo thành lực hãm điện từ, giảm ảnh hưởng của quán tính
  digitalWrite(INa, 0);
  digitalWrite(INb, 0);
}