/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 普通时钟功能,串口更新程序
 
 使用串行595数码管模块连接详情：
 http://www.doflye.net/viewthread.php?tid=5305&extra=
 
 */
/*
//定义段码，这里是共阴段码，可以使用数码管段码软件改变数组值或者任意显示形状
 //德飞莱提供免费数码管段码软件，不需安装，绿色软件，下载地址如下：
 //http://doflye.net/viewthread.php?tid=726
 */
const unsigned char dofly_DuanMa[10]={
  0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//位码
unsigned char const dofly_WeiMa[]={
  0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
long previousMillis = 0; 
//设置对应的端口
int latch = 8;
int srclk = 9;
int ser = 10;
//主题部分是通过LY-51S的移植，仅需改变扫描部分即可
// 对应的8位数据引脚LY-51S独立模块开发板上接J3，0脚接D0以此类推
//int latchA = 8;//位码锁存控制端LY-51S独立模块开发板上接J2 A端
//int latchB = 9;//段码锁存控制端LY-51S独立模块开发板上接J2 B端
unsigned char displayTemp[8];

void setup() {
  // 循环设置，把对应的端口都设置成输出
  // 这里使用德飞莱串口数码管模块，595芯片控制
    pinMode(latch, OUTPUT); 
    pinMode(ser, OUTPUT); 
    pinMode(srclk, OUTPUT);
    Serial.begin(9600);
  
}
//把数据用串行转并行输出到595
void SendByte(unsigned char dat)
{    
  static unsigned char i; 
        
   for(i=0;i<8;i++)
        {
         digitalWrite(srclk,0);
         digitalWrite(ser,bitRead(dat,7-i));//这里也可以用arduino自带的函数操作，主用于595类型的输出，自查帮助文件。
         digitalWrite(srclk,1);
         }
         
}
//德飞莱的模块是2个595级联，段码和位码都是用折3根线控制，所以需要连续2个字节
void Send2Byte(unsigned char dat1,unsigned char dat2)
{    
   SendByte(dat1);
   SendByte(dat2);      
}
//锁存输出
void Out595(void)
{
        digitalWrite(latch,1);
        digitalWrite(latch,0);
}
// 主循环
void loop() {
  char serialtmp[16];
  static unsigned char second,minute,hour,weekday;
  static unsigned  long lastTime=0;
  //通过读取串口发来的信息，读取其中的时分秒的数值，并进行转换
  if (Serial.available()) {
      Serial.readBytes(serialtmp,16);
    hour= (serialtmp[8]-'0')*10+(serialtmp[9]-'0');
    minute= (serialtmp[10]-'0')*10+(serialtmp[11]-'0');
    second= (serialtmp[12]-'0')*10+(serialtmp[13]-'0');
  //德飞莱的串口软件有更新时间功能，自动调用电脑时间，一键更新，非常方便
  //德飞莱串口调试软件下载地址如下：http://doflye.net/viewthread.php?tid=4929
  }


  if (millis() - lastTime >= 1000) {
    lastTime = millis();
    second++;
  }

  if (second > 59) {
    minute++;
    second = 0; // 秒钟清零
  }

  // move forward one hour every 60 minutes
  if (minute > 59) {
    hour++;
    minute = 0; // 分钟清零
  }

  // move forward one weekday every 24 hours
  if (hour > 23) {
    weekday++;
    hour = 0; // 时钟清零
  }

  // reset weekdays on Saturday
  if (weekday > 7) {
    weekday = 1;
  }

  //分解数据到对应的数码管
  displayTemp[0]=dofly_DuanMa[hour/10];
  displayTemp[1]=dofly_DuanMa[hour%10];
  displayTemp[2]=0x40;
  displayTemp[3]=dofly_DuanMa[minute/10];
  displayTemp[4]=dofly_DuanMa[minute%10];
  displayTemp[5]=0x40;
  displayTemp[6]=dofly_DuanMa[second/10];
  displayTemp[7]=dofly_DuanMa[second%10];
  //定时扫描数码管
  static int i;
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 0) {
    previousMillis = currentMillis;   
    Send2Byte(dofly_WeiMa[i],displayTemp[i]);
    Out595();
    i++;
    if(i==8)
      i=0;
  }
}










