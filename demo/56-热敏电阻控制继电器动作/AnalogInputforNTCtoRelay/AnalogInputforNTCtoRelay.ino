/*

 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 通过检测热敏电阻的变化值，用于控制led的闪烁频率，值越大，闪烁越慢
 并设置一个数值区间，当大于高限数值时候继电器吸合，小于低限数值时候继电器释放
 数值区间保持原有状态。
 
 具体应用请参考论坛arduino专区

 如果使用LY-51S独立模块开发板，参考以下链接：
 http://www.doflye.net/thread-5295-1-1.html
 官方硬件和软件参考地址：
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = A0;    // 模拟输入引脚
int ledPin = 13;       // led指示灯引脚
int relayPin = 12;     // 定义继电器引脚，高低电平有效取决于继电器的连接方式
int sensorValue = 0;  //  模拟输入数值变量

void setup() {
  // 声明引脚为输出模式
  pinMode(ledPin, OUTPUT);  
  pinMode(relayPin, OUTPUT); 
}

void loop() {
  // 读取电位器电压值
  sensorValue = analogRead(sensorPin);    
  // 点亮led，LY-51S独立模块开发板上led模块则是熄灭led
  if(sensorValue>=800) digitalWrite(relayPin, HIGH);
  else if(sensorValue<=600) digitalWrite(relayPin, LOW);
  
  digitalWrite(ledPin, HIGH);  
  // 使用读取的这个模拟量值作为演示时间，单位ms，范围0-1023
  delay(sensorValue);          
  // 熄灭led，LY-51S独立模块开发板上led模块则是点亮led 
  digitalWrite(ledPin, LOW);   
  // 使用读取的这个模拟量值作为演示时间，单位ms，范围0-1023
  delay(sensorValue);                  
}
