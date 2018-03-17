#include "Omni.h"

class LineFollowing
{
  public:

  /* ----- Khai báo các hàm ----- */
  void lineFollowing(int speed);          //Dò line với tốc độ mong muốn
  void directionChange(int deltaAngle);   //Chuyển sang hướng mới, hợp với hướng hiện tại một góc bằng deltaAngle

  private:

  /* ----- Bổ trợ cho các hàm public -----*/
  Omni myOmni;        //Khởi tạo đối tượng để điều khiển
  void findAngle();   //Tìm góc mới (để bám theo line)
  
  /* ----- Các mảng về cảm biến và góc ----- */
  int U[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
  double irAngle[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 190, 202.5, 225, 247.5, 290, 292.5, 315 , 337.5};

  /* ----- Các hằng số về cảm biến, góc ----- */
  const int irThreshold = 325;
  const int angleRange = 60;    //Vùng góc được quét (độ) - vùng quét càng nhỏ, đi càng mượt nhưng khả năng phát
                                //hiện ngã ba/ngã tư càng thấp
                                //Góc quét nên dao động từ 60 đến 75 độ

  /* ----- Các biến tìm góc ----- */
  int angle = 0;
  int irCount = 0;      //Số cảm biến nằm trên line
  double angleSum = 0;  //Tổng các góc dựa trên số cảm biến nằm trên line

  /* ----- Các biến lưu thời gian ----- */
  unsigned long lastCheckLineFollowing;
  unsigned long lastCheckDirectionChange;
};


