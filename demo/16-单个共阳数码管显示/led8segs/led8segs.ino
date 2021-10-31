/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

 1个共阳数码管，显示0-9数字
 
 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/thread-5298-1-1.html
 
 */
int ledCount=8;
//定义段码，这里是共阴段码，如果是共阳只需要在程序中把读到的值按位取反即可
const unsigned char dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int ledPins[] = { 
  0,1,2, 3, 4, 5, 6, 7, };   // 对应的led引脚


void setup() {
// 循环设置，把对应的led都设置成输出
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}
// 数据处理，把需要处理的byte数据写到对应的引脚端口。
void deal(unsigned char value){
 for(int i=0;i<8;i++)
   digitalWrite(ledPins[i],!bitRead(value,i));//使用了bitWrite函数，非常简单
   // !bitRead(value,i)，这里前面加！(非运算符号)，取决于使用的是共阴还是共阳数码管。
}
// 主循环
void loop() {
  // 循环显示0-9数字
  for(int i=0;i<10;i++){
     deal(dofly_DuanMa[i]);//读取对应的段码值
     delay(1000);          //调节延时，2个数字之间的停留间隔
  }
  }




