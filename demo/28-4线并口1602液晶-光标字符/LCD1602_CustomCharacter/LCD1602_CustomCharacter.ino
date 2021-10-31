/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 LiquidCrystal库 - 自定义字符
 
 演示了如何使用16X2液晶显示屏。该LiquidCrystal
 库适用于所有的兼容HD44780的LCD液晶。常用的是16引脚。

 
 引脚定义，这里使用4位数据模式，只写数据，不读数据:
 * LCD RS pin to digital pin 12      //数据/指令控制引脚
 * LCD Enable pin to digital pin 11  //使能引脚
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground 接GND       //读/写控制引脚，高电平是读数据，低电平是写数据
 * 10K resistor://使用LY-51S开发板已经连接好这些硬件，值需要连接对应的端口，非常方便。
 * ends to +5V and ground VO引脚接电位器抽头，用于调节对比度，LY-51S开发板只需要调节W1电位器。
 * wiper to LCD VO pin (pin 3)
 * A0接10K电位器
 面包板连接电路图和详细说明英文版：
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/viewthread.php?tid=5293&extra=
 
 
 */

// 包含头文件
#include <LiquidCrystal.h>

// 初始化引脚
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 自定义字符
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};
void setup() {
  // 创建一个新的字符
  lcd.createChar(0, heart);
  // 创建一个新的字符
  lcd.createChar(1, smiley);
  // 创建一个新的字符
  lcd.createChar(2, frownie);
  // 创建一个新的字符
  lcd.createChar(3, armsDown);  
  // 创建一个新的字符
  lcd.createChar(4, armsUp);  

  // 设置液晶行列数值 
  lcd.begin(16, 2);
  // 打印字符串
  lcd.print("I "); 
  lcd.write(0.0);//这里是老版本库的bug，应写成0，请下载新版软件就可以避免这个问题，具体请参考arduino官网
  lcd.print(" Arduino! ");
  lcd.write(1);

}

void loop() {
  // 读取A0引脚的值
  //使用独立模块开发板LY-51S连接电位器详情：
  //http://doflye.net/viewthread.php?tid=5295&extra=
  int sensorReading = analogRead(A0);
  // 结果处理至 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // 设置光标移动到下一行，第5位
  lcd.setCursor(4, 1);
  // 绘制小人手放下的状态
  lcd.write(3);
  delay(delayTime);
  lcd.setCursor(4, 1);
  // 绘制举起手状态
  lcd.write(4);
  delay(delayTime); 
}



