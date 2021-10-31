/*
 输入内部上拉功能
 
 这个演示内部上拉功能，我们不需要单独使用外部的上拉电阻，
 因为芯片内部集成了上拉电阻，大约20K，只要通过设置寄存器
 打开这个上拉功能即可。
 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 硬件连接：
 * led连接的13脚，默认开发板上有这个硬件连接
 * 按键一端连接到+GND，另外一段连接到Pin2，
 * 德飞莱增强版上面有这个按键KEY_L，直接用1根杜邦线
 * 连接到Pin2引脚
 如果使用LY-51S独立模块开发板，参考以下链接：
 http://doflye.net/viewthread.php?tid=5296&extra=
 官方硬件和软件参考地址：
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 
 */

void setup(){
  //使能串口功能，设置对应的参数
  Serial.begin(9600);
  //使能pin2为输入，并启用内部上拉功能。
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT); 

}

void loop(){
  //读取按键状态值
  int sensorVal = digitalRead(2);
  //打印这个值到串口监视器
  //这里可以使用arduino自带的串口调试器，也可以使用德飞莱串口调试软件
  //下载地址：http://doflye.net/viewthread.php?tid=4929
  Serial.println(sensorVal);
  
  // 内部上拉电阻等效于外部上拉电阻，在硬件部分我们
  // 节省了1个电阻，有利于电路的简化。
  // 同时把这个状态反应到led
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  } 
  else {
    digitalWrite(13, HIGH);
  }
}



