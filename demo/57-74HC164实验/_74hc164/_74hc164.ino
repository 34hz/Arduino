/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

 74hc164 
 
 
 使用独立模块开发板LY-51S连接详情：
 
 http://www.doflye.net/thread-5409-1-1.html
 */
 
 //定义段码，这里是共阳段码，如果是共阴只需要在程序中把读到的值按位取反即可
const unsigned char dofly_DuanMa[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
int CLK = 2;
int DAT = 3;//A or B

void setup() {
// 循环设置，把对应的端口都设置成输出

    pinMode(CLK, OUTPUT); 
    pinMode(DAT, OUTPUT); 
    Serial.begin(9600); 
  
}

void SendByte(unsigned char dat)
{    
  static unsigned char i; 
        
   for(i=0;i<8;i++)
        {
         digitalWrite(CLK,0);
         digitalWrite(DAT,bitRead(dat,7-i));//高位先输出。这里也可以用arduino自带的函数操作，主用于595，164类型的输出，自查帮助文件。
         digitalWrite(CLK,1);
         }
         
}
// 主循环
void loop() {
  // 循环显示0-9数字
  for(int i=0;i<8;i++){
    
     SendByte(dofly_DuanMa[i]);
     delay(1000);          //调节延时，2个数字之间的停留间隔
  }
  }




