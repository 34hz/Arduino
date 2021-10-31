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

// change this to the number of steps on your motor
#define STEPS 512

// 定义引脚的连接
Stepper stepper(STEPS, 8, 10, 9, 11);

//上一次的读取模拟量
int previous = 0;
//初始化电机转动速度
void setup()
{
  stepper.setSpeed(20);
}
//主循环
void loop()
{
  // 读取AD值，在LY-51S可以直接通过电位器调节
  int val = analogRead(0);

  // 把速度设置为这次和上次读取的差值
  stepper.step(val - previous);

  // 记下这次读取值，方便下次比较
  previous = val;
}
