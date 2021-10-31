/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 利用A0输入的模拟量，经过换算得到电压值显示到数码管
 
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
const int analogInPin = A0;
int latch = 8;
int srclk = 9;
int ser = 10;

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
  char displayTemp[8];//显示缓冲区

  int sensorValue = analogRead(analogInPin);      
  //读取的模拟量换算成实际电压值，这里精确到小数点后2位，所以是500，在5后面加小数点，就是5.00  
  int voltage = map(sensorValue, 0, 1023, 0, 500);
  //清屏，8位数码管都不显示
  for(int i=0;i<8;i++)
   displayTemp[i]=0;
  //电压值反映到数码管
  displayTemp[0]=dofly_DuanMa[voltage/100%10]|0x80;//这里最后是加小数点，共阳和共阴是相反的。
  displayTemp[1]=dofly_DuanMa[voltage/10%10];
  //动态扫描显示，数码管部分不能被中断，否则会闪烁，如果不了解这里，可以看德飞莱LY-51S的视频
  //视频链接点击这里：http://v.youku.com/v_show/id_XNDc2ODE1OTQw.html?f=18512367
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










