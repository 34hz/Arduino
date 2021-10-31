
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
  //  myservo.write(14);
}

void loop()
{
  while (Serial.available() > 0)
  {
    pos = Serial.read();
    Serial.print(pos);
    if (pos <= 180 && pos >= 0) {
      myservo.write(pos);
      delay(700);
      pos = 0;

      myservo.write(96);
      delay(700);
    }
  }
}
