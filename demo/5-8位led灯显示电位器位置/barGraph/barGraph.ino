/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

 利用A0输入的模拟量，控制led点亮状态，可以直观看到电压大小
 
 使用独立模块开发板LY-51S连接详情：
 http://doflye.net/viewthread.php?tid=5294&extra=
 官方参考电路和说明
 http://www.arduino.cc/en/Tutorial/BarGraph
 */


// 引脚定义
const int analogPin = A0;   // 模拟输入
const int ledCount = 8;    // led个数

int ledPins[] = { 
  0,1,2, 3, 4, 5, 6, 7, };   // 对应的led引脚


void setup() {
  // 循环设置，把对应的led都设置成输出
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}

void loop() {
  // 读取电位器的值
  int sensorReading = analogRead(analogPin);
  // 把对应的值转化成0-最大led个数，这里是8
  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount);

  // 循环对比输出到led:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
   
    if (thisLed < ledLevel) {
      digitalWrite(ledPins[thisLed], HIGH);
    } 
 
    else {
      digitalWrite(ledPins[thisLed], LOW); 
    }
  }
}



