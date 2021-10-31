
/* 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 通过电压输入控制步进电机转动步数
 使用的电机不同，得到的参数不同，可以选用官方推荐的电机。
 使用德飞莱LY-51S开发板连接详情：
 http://www.doflye.net/viewthread.php?tid=5306&extra=
 官方参考信息
 http://www.arduino.cc/en/Reference/Stepper
 */
 
#include <Stepper.h>

const int stepsPerRevolution = 512;  // 电机每一转动一圈所需要的步数，这个因不同的电机有差别
//这里使用5线单极型电机，带机械减速齿轮，减速比1/16，步进角度是5.625/16

// 初始化引脚
Stepper myStepper(stepsPerRevolution, 8,10,9,11);            

void setup() {
  // 设置转速
  myStepper.setSpeed(5);
  // 初始化串口
  Serial.begin(9600);
}

void loop() {
  // 正向转一圈
   Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  
   // 反向转一圈
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500); 
}

