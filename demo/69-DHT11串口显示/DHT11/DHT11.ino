/*
http://shop34791330.taobao.com/ //德飞莱旗舰店
http://qixingchong.tmall.com/   //七星虫旗舰店
http://www.doflye.net //德飞莱技术论坛
http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块

不使用库文件的DHT11 这个程序移植别人的，近期会做修改

详情点击链接
http://www.doflye.net/thread-5402-1-1.html
*/
#define DHT11_PIN 0
int Led=8;
int Buzzer=7;

byte read_dht11_dat()
{
  byte i = 0;
  byte result = 0;
  for(i=0;i<8;i++)
  {
    while(!(PINC&_BV(DHT11_PIN)));
    delayMicroseconds(30);
    if(PINC&_BV(DHT11_PIN))
      result|=(1<<(7-i));
    while((PINC&_BV(DHT11_PIN)));
  }
  return result;
}
void setup()
{
  DDRC|=_BV(DHT11_PIN);
  PORTC|=_BV(DHT11_PIN);
  pinMode(Led,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop()
{
  byte dht11_dat[5];
  byte dht11_in;
  byte i;
  PORTC &= ~_BV(DHT11_PIN);
  delay(18);
  PORTC|=_BV(DHT11_PIN);
  delayMicroseconds(40);
  DDRC &= ~_BV(DHT11_PIN);
  delayMicroseconds(40);
  dht11_in = PINC & _BV(DHT11_PIN);
  if(dht11_in)
  {
    Serial.println("dht11 start condition 1 not met");
    return;
  }

  delayMicroseconds(80);
  dht11_in=PINC & _BV(DHT11_PIN);
  if(!dht11_in)

  {
    Serial.println("dht11 start condition 2 not met");
    return;
  }

  delayMicroseconds(80);
  for(i=0;i<5;i++)
    dht11_dat[i]=read_dht11_dat();
  DDRC|=_BV(DHT11_PIN);
  PORTC|=_BV(DHT11_PIN);
  byte dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];
  if(dht11_dat[4]!=dht11_check_sum)
  {
    Serial.println("DHT11 checksum error");
  }

  Serial.print("Current humdity= ");
  Serial.print(dht11_dat[0],DEC);
  Serial.print(".");
  Serial.print(dht11_dat[1],DEC);
  Serial.print("%");
  Serial.print("temperature = ");
  Serial.print(dht11_dat[2],DEC);
  Serial.print(".");
  Serial.print(dht11_dat[3],DEC);
  Serial.println("C");
  if(dht11_dat[0]==25)
    digitalWrite(Led,HIGH);
  else
    digitalWrite(Led,LOW);
  if(dht11_dat[0]==28)
    digitalWrite(Buzzer,LOW);
  else
    digitalWrite(Buzzer,HIGH);
  delay(2000);
}



