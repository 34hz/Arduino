/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

 8位数码管动态扫描原理 74hc573x2 适用于LY-51S开发板
 
 
 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/thread-5299-1-1.html
 
 */
int ledCount=8;
//定义段码，这里是共阴段码，可以使用数码管段码软件改变数组值或者任意显示形状
//德飞莱提供免费数码管段码软件，不需安装，绿色软件，下载地址如下：
//http://doflye.net/viewthread.php?tid=726
const unsigned char dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//位码
unsigned char const dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
int ledPins[] = { 
  0,1,2, 3, 4, 5, 6, 7, };   // 对应的8位数据引脚LY-51S独立模块开发板上接J3，0脚接D0以此类推
int latchA = 8;//位码锁存控制端LY-51S独立模块开发板上接J2 A端
int latchB = 9;//段码锁存控制端LY-51S独立模块开发板上接J2 B端

void setup() {
// 循环设置，把对应的端口都设置成输出
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  pinMode(latchA, OUTPUT); 
  pinMode(latchB, OUTPUT); 
  }
}
// 数据处理，把需要处理的byte数据写到对应的引脚端口。
void deal(unsigned char value){
 for(int i=0;i<8;i++)
   digitalWrite(ledPins[i],bitRead(value,i));//使用了bitWrite函数，非常简单
   // !bitRead(value,i)，这里前面加！(非运算符号)，取决于使用的是共阴还是共阳数码管。
}
// 主循环
void loop() {
  // 循环显示0-9数字
  for(int i=0;i<8;i++){
    
     deal(0);//清空段码，不显示，不然会造成”鬼影“
     digitalWrite(latchB,HIGH);
     digitalWrite(latchB,LOW);
     deal(dofly_WeiMa[i]);//读取对应的段码值
     digitalWrite(latchA,HIGH);
     digitalWrite(latchA,LOW);
     deal(dofly_DuanMa[i]);//读取对应的段码值
     digitalWrite(latchB,HIGH);
     digitalWrite(latchB,LOW);
     delay(2);          //调节延时，2个数字之间的停留间隔
  }
  }




