/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 IIC 1602显示，优点是只占用2个数据线就能同时显示8个液晶屏，每个液晶内容都单独显示。

 德飞莱ICC 液晶模块连接方式链接详情
 http://www.doflye.net/viewthread.php?tid=5303&extra=
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//第一个地址就是液晶模块的地址，一般地址范围是0x20~0x27，共8个地址，最多同时连接8个液晶模块
//此时需要模块支持地址选择，德飞莱IIC模块可以通过跳电阻选择地址，默认0x27
void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  //背光部分需要参考硬件电路，有的厂家是用高电平驱动，德飞莱则使用低电平。
  //可以通过修改库的值改变其内容，如果简单化可以直接使用相反的函数调用。
  //比如直接用lcd.nobacklight();当做打开背光功能使用。 
  lcd.print("www.doflye.net");
  lcd.setCursor(0, 1);
  lcd.print("Hello, world!");
}

void loop()
{
}
