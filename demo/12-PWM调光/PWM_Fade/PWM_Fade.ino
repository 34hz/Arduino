/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 利用PWM功能实现调光效果
 
 使用独立模块开发板LY-51S连接详情：
 http://doflye.net/viewthread.php?tid=5294&extra=
 */

int led = 9;           // led引脚定义，这里需要使用有PWM功能的引脚
int brightness = 0;    // led亮度
int fadeAmount = 5;    // 调节的单步间隔

// 初始化
void setup()  { 
  // led引脚定义位输出
  pinMode(led, OUTPUT);// 独立模块LY-51S开发板上LED1-LED8都可以使用。
} 

// 主循环
void loop()  { 
  // 设置了led的亮度
  analogWrite(led, brightness);    

  // 下一个循环调整led亮度
  brightness = brightness + fadeAmount;

  // 到最大值后反向调整 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // 等待30ms   
  delay(30);                            
}

