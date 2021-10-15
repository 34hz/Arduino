
/*
   旋转指令：FF FE b4
     FF FE 消息头
     b4 十进制180 旋转180度
   角度范围：0<= 旋转角度 <=180
   开机状态：开机默认旋转到0度位置

   串口参数: 115200 8 N 1

   信号引脚：~9
*/
#include <Servo.h>

Servo myservo;

int pos = 0;    // 用于存储舵机位置的变量

void setup()
{
  myservo.attach(9, 500, 2500);
  Serial.begin(115200);
  myservo.write(0);
}

void loop()
{
  while (Serial.available() > 0)
  {
    if (Serial.read() == 0xFF) {
      Serial.print(0xFF);
      if (Serial.read() == 0xFE) {
        Serial.print(0xFE);
        pos = Serial.read();
        if (pos <= 180 && pos >= 0) {
          int lastpos = myservo.read ();
          while (lastpos < pos) {
            myservo.write(++lastpos);
            delay(20);
          }
          while (lastpos > pos) {
            myservo.write(--lastpos);
            delay(20);
          }
          if (lastpos == pos) {
            myservo.write(lastpos);
            delay(20);
          }
          Serial.print(255);
          Serial.print(254);
          Serial.print(pos);
          pos = 0;
        }
      }
    }
  }
}
