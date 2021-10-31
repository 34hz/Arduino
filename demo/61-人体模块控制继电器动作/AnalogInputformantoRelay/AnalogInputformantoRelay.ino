/*

 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 人体模块输出数字电平，有人接近输出高电平，通过检测电平改变继电器状态。

 如果使用LY-51S独立模块开发板，参考以下链接：
 http://www.doflye.net/thread-5295-1-1.html
 官方硬件和软件参考地址：
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */


int ledPin = 13;       // led指示灯引脚
int inPin  = 12;       // 定义输入引脚
int buttonState;             // 读取的当前按键状态
void setup() {
  // 声明引脚为输出模式
  pinMode(ledPin, OUTPUT);  
  pinMode(inPin, INPUT);
}

void loop() {
   buttonState = digitalRead(inPin);
  if(buttonState == HIGH) //如果读入是高电平，说明有人进入区域 
	digitalWrite(ledPin, HIGH);  //吸合继电器
  delay(3000);          //延时1s    
  buttonState = digitalRead(inPin); 
  if(buttonState == LOW) //如果读入是低电平
	digitalWrite(ledPin, LOW);  //释放继电器  
}
