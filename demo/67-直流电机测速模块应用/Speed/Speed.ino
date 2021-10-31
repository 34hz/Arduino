/* 

 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 通过测量高电平时间，计算转一圈时间，这里是粗略计算，因为不同的遮光圆盘参数不同
 更多更新请参考德飞莱论坛
 
 
 
 */

// 引脚定义
const int analogInPin = A0;  // 模拟输入引脚
const int analogOutPin = 9; //  PWM输出引脚

int sensorValue = 0;        // 电位器电压值
int outputValue = 0;        // 模拟量输出值（PWM）
const int echo = 10;        // 反馈信号


//初始化
void setup() {
  pinMode(echo, INPUT);
  //反馈端口设置为输入
  Serial.begin(9600);
}
//主循环
void loop() {
  long IntervalTime=0; //定义一个时间变量
    // 读取模拟量值
  sensorValue = analogRead(analogInPin);            
  // 变换数据区间
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // 输出对应的PWM值
  analogWrite(analogOutPin, outputValue);  //通过电位器调节PWM
  
    IntervalTime=pulseIn(echo, HIGH);//用自带的函数采样反馈的高电平的宽度，单位ms，电机模块有个圆盘，盘上有4个条形孔
	//每次检测的高电平时间是孔与孔之间的时间（这里忽略孔的宽度，假设孔为0，这个是粗略计算，也可以通过圆盘的距离算系数）
	//IntervalTime x 4 表示转一周的时间，1分钟的转数：60x1000000（1S换算成us）/IntervalTime x 4
	//得出15000000/IntervalTime 就是每分钟转数。
	//根据德飞莱测速模块的尺寸分析，条形方孔占圆盘的1/4，估算得到如下公式，具体精确值用户可以自行测量计算。
    float S=10000000/IntervalTime; //使用浮点计算出r/min
    Serial.print(S);//通过串口输出数值
    Serial.println("  r/min");//通过串口输出数值
    S=0;IntervalTime=0;//对应的数值清零。


}


