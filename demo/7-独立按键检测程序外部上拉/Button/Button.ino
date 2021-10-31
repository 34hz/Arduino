/*
 按键
 
 通过按键控制led亮灭
 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 硬件连接：
 * led连接的13脚，默认开发板上有这个硬件连接
 * 按钮一端连接到+5V，另外一段连接到Pin2，
 * 10K 电阻连接pin2和GND之间
 * 德飞莱增强版上面有这个按键KEY_H，直接用1根杜邦线
 * 连接到Pin2引脚
 如果使用LY-51S独立模块开发板，参考以下链接：
 http://doflye.net/viewthread.php?tid=5296&extra=
 官方硬件和软件参考地址：
 http://www.arduino.cc/en/Tutorial/Button
 */

//定义引脚
const int buttonPin = 2;     // 按键位置
const int ledPin =  13;      // led位置

// 定义变量
int buttonState = 0;         // 读取按键状态存放变量

void setup() {
  // 初始化led引脚为输出
  pinMode(ledPin, OUTPUT);      
  // 初始化按键引脚为输入
  //关于按键部分可以到德飞莱论坛查询相关内容
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // 读取按键值
  buttonState = digitalRead(buttonPin);

  // 判断是否按键按下
  // 如果按下，按键的状态就是高电平
  if (buttonState == HIGH) {     
    // 点亮led，如果led的电路是反向连接的就是熄灭led
    //LY-51S独立模块开发板上的led就是低电平点亮，因为需要兼容标准的51单片机端口特性	
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // 否则熄灭led，如果led的电路是反向连接的就是点亮led
    //LY-51S独立模块开发板上的led就是低电平点亮，因为需要兼容标准的51单片机端口特性
    digitalWrite(ledPin, LOW); 
  }
}
