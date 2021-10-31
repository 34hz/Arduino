/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 通过检测光敏电阻的值用于改变输出音调。
 * 光敏电阻一端接VCC，一端接10K电阻
 * 10K电阻另外一段接GND
 * 外接8欧姆喇叭
 如果使用LY-51S独立模块开发板，上面自带光敏电阻模块，只需要简单连接杜邦线即可。
 
 
 如果使用LY-51S独立模块开发板，参考以下链接：
 http://www.doflye.net/viewthread.php?tid=5297&extra=
 官方硬件和软件参考地址：
 http://arduino.cc/en/Tutorial/Tone2
 
 */


void setup() {
  // 初始化串口参数，这里仅仅作为调试使用
  Serial.begin(9600);
}

void loop() {
  // 从传感器读入模拟量数据
  int sensorReading = analogRead(A0);
  // 打印这个数据到串口以便能知道数据的具体数值
  Serial.println(sensorReading);
  // 把读入的模拟量(这种情况下, 光敏电阻读出值400 - 1000 )
  // 换算出频率范围 (120 - 1500Hz)
  // 根据实际传感器的参数改变下面的最大值和最小值
  int thisPitch = map(sensorReading, 400, 1000, 120, 1500);

  // 播放对应频率的声音
  tone(9, thisPitch, 10);
  delay(1);        // 延时，等待数据稳定后读取
}






