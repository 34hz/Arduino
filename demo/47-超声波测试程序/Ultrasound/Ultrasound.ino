/* 
 超声波模块测距
 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 超声波测距：
 触发信号trig：触发高电平脉冲大于10us
 反馈信号echo：返回的高电平长度就是距离的us数字
 通过声波速度和采集到的时间计算出距离。
 
 超声波连接参考网址：
 http://www.doflye.net/viewthread.php?tid=5307&extra=
 
 */

// 引脚定义
const int trig = 8;    // 触发信号
const int echo = 9;    // 反馈信号


//初始化
void setup() {
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //触发端口设置为输出，反馈端口设置为输入
  Serial.begin(9600);
}
//主循环
void loop() {
  long IntervalTime=0; //定义一个时间变量
  while(1){
    digitalWrite(trig, 1);//置高电平
    delayMicroseconds(15);//延时15us
    digitalWrite(trig, 0);//设为低电平
    IntervalTime=pulseIn(echo, HIGH);//用自带的函数采样反馈的高电平的宽度，单位us
    float S=IntervalTime/58.00; //使用浮点计算出距离，单位cm
    Serial.println(S);//通过串口输出距离数值
    S=0;IntervalTime=0;//对应的数值清零。
    delay(500);//延时间隔决定采样的频率，根据实际需要变换参数
  }
}


