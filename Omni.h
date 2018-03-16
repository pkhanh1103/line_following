#ifndef Omni_h
#define Omni_h
#include "Arduino.h"
#include <SMotor.h>
#include "definition.h"

class Omni
{
  public:
    Omni();                                     //Constructor

    void stop(void);                            //Dừng omni

    void rotate(boolean typeRot, double RPM);   //Xoay omni theo chiều dương (true) hoặc âm (false)
                                                //Quy ước: chiều dương là ngược chiều kim đồng hồ
    
    void move(int angle, double RPM);           //Di chuyển omni theo góc và tốc độ mong muốn

    //Các đối tượng motor
    SMotor Motor1;
    SMotor Motor2;
    SMotor Motor3;

  private:
    double maxSpeed;
    double V1, V2, V3;
    double sine, cosine;
};

#endif
