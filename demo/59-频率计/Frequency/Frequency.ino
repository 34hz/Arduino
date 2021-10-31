/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 这个程序仅作为简单测试使用，使用标准方波输入
 更新程序请参考德飞莱论坛
*/
int divider[6] = {0, 1, 8, 64, 256, 1024};
int prescaler = 5;
double count = 0;
double middle = 0;
char x = 0;
ISR(TIMER1_OVF_vect)
{
    if (prescaler < 4)
    {
        prescaler++;
    }
}
void interrupt()
{
    if (!x)
    {
        count = TCNT1;
        TCNT1 = 0x000;
        TCCR1B = prescaler;
        attachInterrupt(0, interrupt, FALLING);
    }
    else
    {
        middle = TCNT1;
        attachInterrupt(0, interrupt, RISING);
    }
    x = ~x;
}
void setup()
{
    Serial.begin(57600);
    TIMSK1 = 0x01;
    TCCR1A = 0x00;
    attachInterrupt(0, interrupt, RISING);
}
void loop()
{
    Serial.print("Freq: ");
    Serial.print(16000000.0 / divider[prescaler] / count);
    Serial.print(" Hz\t\tDuty: ");
    Serial.print(middle / count * 100);
    Serial.print(" %\t\tPeriod: ");
    Serial.print(0.0000625 * divider[prescaler]*count);
    Serial.print(" ms\t\tH-time: ");
    Serial.print(0.0000625 * divider[prescaler]*middle);
    Serial.print(" ms\t\tL-time: ");
    Serial.print(0.0000625 * divider[prescaler]*(count - middle));
    Serial.println(" ms");
    if (prescaler > 1)
    {
        prescaler--;
        delay(200);
    }
    delay(100);
}
