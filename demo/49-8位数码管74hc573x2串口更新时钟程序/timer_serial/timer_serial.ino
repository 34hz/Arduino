/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 时钟，使用德飞莱串口调试程序直接更新时间，74hc573x2
 
 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/thread-5299-1-1.html
 
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
int ledCount=8;
long previousMillis = 0; 
int keyPin = 13;
int ledPins[] = { 
  2, 3, 4, 5, 6, 7,10,11 };   // 对应的8位数据引脚LY-51S独立模块开发板上接J3，0脚接D0以此类推
int latchA = 8;//位码锁存控制端LY-51S独立模块开发板上接J2 A端
int latchB = 9;//段码锁存控制端LY-51S独立模块开发板上接J2 B端
unsigned char displayTemp[8];

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin


void setup() {
  // 循环设置，把对应的端口都设置成输出
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
    pinMode(latchA, OUTPUT); 
    pinMode(latchB, OUTPUT); 
    pinMode(keyPin, INPUT);
    Serial.begin(9600);
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
  char serialtmp[16];
  static unsigned char second,minute,hour,weekday;
  static unsigned  long lastTime=0;
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
    second = 0; // reset seconds to zero
  }

  // move forward one hour every 60 minutes
  if (minute > 59) {
    hour++;
    minute = 0; // reset minutes to zero
  }

  // move forward one weekday every 24 hours
  if (hour > 23) {
    weekday++;
    hour = 0; // reset hours to zero
  }

  // reset weekdays on Saturday
  if (weekday > 7) {
    weekday = 1;
  }


  displayTemp[0]=dofly_DuanMa[hour/10];
  displayTemp[1]=dofly_DuanMa[hour%10];
  displayTemp[2]=0x40;
  displayTemp[3]=dofly_DuanMa[minute/10];
  displayTemp[4]=dofly_DuanMa[minute%10];
  displayTemp[5]=0x40;
  displayTemp[6]=dofly_DuanMa[second/10];
  displayTemp[7]=dofly_DuanMa[second%10];

  static int i;
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 0) {
    previousMillis = currentMillis;   

    deal(0);//清空段码，不显示，不然会造成”鬼影“
    digitalWrite(latchB,1);
    digitalWrite(latchB,0);
    deal(dofly_WeiMa[i]);//读取对应的段码值
    digitalWrite(latchA,1);
    digitalWrite(latchA,0);
    deal(displayTemp[i]);//读取对应的段码值
    digitalWrite(latchB,1);
    digitalWrite(latchB,0);
    i++;
    if(i==8)
      i=0;
  }
}










