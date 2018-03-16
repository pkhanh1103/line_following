#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
//#include "Arduino-PID-Library-master\PID_v1.h"
//#include "Encoder-master\Encoder.h"
//#include "SimpleKalmanFilter-master\src\SimpleKalmanFilter.h"
#include <PID_v1.h>
#include <Encoder.h>
#include <SimpleKalmanFilter.h>

class Motor
{
  public:
  
  Motor(int _INa, int _INb, int _EN, int _A, int _B);   //Constructor - các tham số lần lượt là chân IN1, IN2,
                                                        //ENABLE của module L298; kênh A, kênh B của encoder

  void stop(void);                                      //Dừng motor
  
  void spin(bool direction, double _speedSet);          //Quay motor theo chiều thuận (true) hay nghịch (false)
                                                        //theo tốc độ mong muốn(RPM - vòng/phút). Hàm này thực  
                                                        //hiện PID và nên được gọi trong một vòng lặp
  
  double speed;                                         //Tốc độ motor đo được theo đơn vị RPM

  private:

  /* ----- Motor ----- */
  int INa;   //Chân IN1 của module L298 - điều khiển cực dương của motor
  int INb;   //Chân IN1 của module L298 - điều khiển cực âm của motor
  int EN;    //Chân ENABLE của module L298 - điều khiển tốc độ motor
  int A;     //Kênh A của encoder gắn với motor
  int B;     //Kênh B của encoder gắn với motor

  /* ----- PID ------ */
  int sampleRate;         //Chu kì lấy mẫu tốc độ motor (mặc định: 10 milli giây)
  double speedSet;        //Tốc độ motor mong muốn (RPM)
  double pwm;             //Xung PWM ghi vào chân ENABLE của module L298
  
  unsigned long now;          //Mốc thời gian hiện tại
  unsigned long lastCheck;    //Mốc thời gian tại lần cuối tốc độ motor được đo
  long oldPosition;           //Vị trí cũ mà encoder đo được
  long newPosition;           //Vị trí mới mà encoder đo được

  void pidSet(double kp, double ki, double kd, int _sampleRate);  //Đặt tham số cho thuật toán PID
  
  /* ----- Các đối tượng tạo từ các thư viện ngoài ----- */
  Encoder myEnc;                  //Đối tượng đọc tín hiệu encoder
  SimpleKalmanFilter myFilter;    //Đối tượng lọc nhiễu tín hiệu encoder
  PID myPID;                      //Đối tượng điều khiển tốc độ motor
};

#endif