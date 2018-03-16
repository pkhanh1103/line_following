#ifndef Omni_h
#define Omni_h
#include "Arduino.h"
#include "Motor.h"
#include "definition.h"

class Omni
{
  public:
    Omni();                                     //Constructor

    void stop(void);                            //Stop omni moving

    void rotate(boolean typeRot, double RPM);   //Rotate omni (true = anti-clockwise, 
                                                //false = clockwise)
    
    void move(int angle, double RPM);           //Move omni in desired angle at desired speed
    
    Motor Motor1;                               //Motor objects
    Motor Motor2;
    Motor Motor3;

    double maxSpeed;
    double V1, V2, V3;
    double sine, cosine;
    
  private:
    /*Motor Motor1;
    Motor Motor2;
    Motor Motor3;*/
    /*double maxSpeed;
    double V1, V2, V3;
    double sine, cosine;*/
  
};

#endif
