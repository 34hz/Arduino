/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 读取Pin2的电平信号，并把结果打印到串口，也同时反映到LED灯
 */

// 定义引脚
int pushButton = 2;
int led = 13;
// 初始化
void setup() {
  // 初始化串口
  Serial.begin(9600);
  // 把按键引脚设置为输入
  // 德飞莱增强版有高电平和低电平触发的2个按键，都可以使用，直接接KEY_H或者KEY_L
 
  pinMode(pushButton, INPUT); // 独立模块LY-51S开发板上独立按键K1-K8都可以使用。
  //把led引脚设置为输出
  pinMode(led, OUTPUT);       // 独立模块LY-51S开发板上LED1-LED8都可以使用。
}
// 使用独立模块开发板LY-51S连接详情：
// http://doflye.net/viewthread.php?tid=5294&extra=
// 主循环
void loop() {
  // 读取输入引脚的值
  int buttonState =  digitalRead(pushButton);
  // 读取的数值反映到led上
  digitalWrite(led, buttonState);
  // 打印结果到串口
  Serial.println(buttonState);
  //这里可以使用arduino自带的串口调试器，也可以使用德飞莱串口调试软件
  //下载地址：http://doflye.net/viewthread.php?tid=4929
  delay(10);        // 延时大小决定循环读取的时间间隔
}



