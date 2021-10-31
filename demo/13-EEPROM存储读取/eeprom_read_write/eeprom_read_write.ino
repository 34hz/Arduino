/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 arduino使用的是AVR单片机，单片机内部自带EEPROM，EEPROM可以存储一些需要变换的或者需要记忆的数据。
 这里用最简单的方式，通过读写来记忆开机的次数，通过按复位或者反复开关电源验证结果。
 */

#include <EEPROM.h>

//设置读取EEPROM的地址
int address = 0;
byte value;
//初始化
void setup()
{
  // 用串口显示相应的信息
  Serial.begin(9600);
  value = EEPROM.read(address);//读取
  //显示开机次数
  Serial.print("power on times:");
  Serial.print(value, DEC);//十进制显示数值
  Serial.println();//打回车，这样看上去清晰
  value=value+1;   //对应的开机次数加1
  EEPROM.write(address,value);//然后存储
  //这里是德飞莱做的测试，由于一个字节只能显示255次，所以超过这个数值溢出清零。
  //真正需要开机次数的需要做一个数据变换。由于bootloader的原因，开电源一次可能会被多次执行。
  //部分内容可以在德飞莱论坛搜索  
  
}

void loop()
{
  //主循环可以自行加入其它操作

 
}
