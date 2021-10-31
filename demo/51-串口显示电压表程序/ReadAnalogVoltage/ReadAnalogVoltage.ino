/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

 串口显示模拟量，并转化为实际电压
 
 使用独立模块开发板LY-51S连接详情：
 http://doflye.net/viewthread.php?tid=5294&extra=
 */

// 初始化
void setup() {
  // 初始化串口参数
  Serial.begin(9600);
}

// 主循环
void loop() {
  // 读取A0的模拟值
  //使用独立模块开发板LY-51S连接电位器详情：
  //http://doflye.net/viewthread.php?tid=5295&extra=
  int sensorValue = analogRead(A0);
  // 转换数值 (0 - 1023) 变成 1个电压值 (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // 打印电压值到串口监视器
  //这里可以使用arduino自带的串口调试器，也可以使用德飞莱串口调试软件
  //下载地址：http://doflye.net/viewthread.php?tid=4929
  Serial.println(voltage);
}
