  /*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 LiquidCrystal库 - 文字显示方向
 
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
 * 10K resistor:   //使用LY-51S开发板已经连接好这些硬件，值需要连接对应的端口，非常方便。
 * ends to +5V and ground VO引脚接电位器抽头，用于调节对比度，LY-51S开发板只需要调节W1电位器。
 * wiper to LCD VO pin (pin 3)
 面包板连接电路图和详细说明英文版：
 http://arduino.cc/en/Tutorial/LiquidCrystalTextDirection
 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/viewthread.php?tid=5293&extra=
 
 */

// 头文件
#include <LiquidCrystal.h>

// 初始化引脚
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int thisChar = 'a';

void setup() {
  // 设置液晶行列值 
  lcd.begin(16, 2);
  // 打开光标
  lcd.cursor();
}

void loop() {
  // 显示'm'时光标方向运行
  if (thisChar == 'm') {
    // go right for the next letter
    lcd.rightToLeft(); 
  }
  // 显示's'时再次反向:
  if (thisChar == 's') {
    // go left for the next letter
    lcd.leftToRight(); 
  }
  // 显示'z'时复位清屏，重新循环:
  if (thisChar > 'z') {
    // 光标回到开始位置
    lcd.clear();
    lcd.home(); 
    // 从a字母开始显示
    thisChar = 'a';
  }
  // 打印出字符
  lcd.write(thisChar);
  // 等待1秒
  delay(1000);
  //调入下一个字母
  thisChar++;
}








