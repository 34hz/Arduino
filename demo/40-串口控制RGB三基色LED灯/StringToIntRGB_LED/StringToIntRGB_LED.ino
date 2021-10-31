/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 通过串口软件写入对应的数据，格式如下：r,g,b,然后加入回车键
 r代表红色，范围是0-255，g代表绿色，范围是0-255，b代表蓝色，范围是0-255
 系统会处理相应的数据并返回相应的值到串口，通过写入不同的数据可以实现
 三色led灯的调光变色功能。
 
 The circuit:
 * led的3个脚连接到9,10,11脚
 * 阳极连接到VCC
 
 通过PWM功能进行调光，实现3种颜色混合显示
 
 德飞莱配套的连接电路和实物图，参考以下链接：
 http://www.doflye.net/viewthread.php?tid=5310&extra=
 */

String inString = "";    // 字符串缓冲区
int currentColor = 0;
int red, green, blue = 0;
//初始化
void setup() {
  // 打开串口通讯功能等待串口打开
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // 发送信息
  Serial.println("\n\nString toInt() RGB:");
  Serial.println();
  // 设置led端口方向:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  // 打开13脚led作为电源指示:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}
//主循环
void loop() {
  int inChar;

  // 读取串口发送的信息:
  if (Serial.available() > 0) {
    inChar = Serial.read();
  }

  if (isDigit(inChar)) {
    // 把读取的1个字节变换成字符类型，并添加到字符串中
    inString += (char)inChar; 
  }

  // 如果遇到逗号，转换数据，并设置相应的颜色，把对应的计数值加1
  if (inChar == ',') {
    // 根据读取到的计数值处理不同的颜色数据
    switch (currentColor) {
    case 0:    // 0 = red 表示红色
      red = inString.toInt();
      // 把字符串情况，等待处理下一个
      inString = ""; 
      break;
    case 1:    // 1 = green:表示绿色
      green = inString.toInt();
      // 把字符串情况，等待处理下一个
      inString = ""; 
      break;
    }
    currentColor++;
  }
  // 如果输入的是回车符号，就是最后一个数据
  if (inChar == '\r') {
    blue = inString.toInt();

    // 写入对应的PWM值
    analogWrite(11,  255 - red);
    analogWrite(9, 255 - green);
    analogWrite(10, 255 - blue);

    // 打印对应的数据到串口
    Serial.print("Red: ");
    Serial.print(red);
    Serial.print(", Green: ");
    Serial.print(green);
    Serial.print(", Blue: ");
    Serial.println(blue);

    // 清空字符串缓冲区，等待下一次处理数据
    inString = ""; 
    // 复位当前颜色的计数值
    currentColor = 0;
  }

}

