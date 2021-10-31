/* 
 按键防抖动
 
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 在一些情况下，由于按键的机械特性，按下或者释放的时候电平不能理解停止在
 理论电平值，而是需要一定时间的振荡后停止，这些抖动虽然实际很短，对于单
 片机来说这个抖动会被认为是按键的实际作用，这个不是我们需要的，所以需要
 通过延时程序跳过抖动区，从而正确的执行按键动作，德飞莱论坛对于这个部分
 内容有讲解，可以去查看，也可以参考LY-51S的视频教程来了解这个内容。
 视频链接地址：http://www.youku.com/playlist_show/id_18512367.html
 独立按键视频：http://v.youku.com/v_show/id_XNDc3MjkwMTUy.html?f=18512367
 
 硬件连接：
 * led连接的13脚，默认开发板上有这个硬件连接
 * 按钮一端连接到+5V，另外一段连接到Pin2，
 * 10K 电阻连接pin2和GND之间
 * 德飞莱增强版上面有这个按键KEY_H，直接用1根杜邦线
 * 连接到Pin2引脚
 如果使用LY-51S独立模块开发板，参考以下链接：
 http://doflye.net/viewthread.php?tid=5296&extra=
 官方硬件和软件参考地址：
 http://www.arduino.cc/en/Tutorial/Debounce
 */

// 引脚定义
const int buttonPin = 2;    // 按键位置
const int ledPin = 13;      // led位置

// 定义变量
int ledState = HIGH;         // 当前led状态
int buttonState;             // 读取的当前按键状态
int lastButtonState = LOW;   // 上次读取的按键状态

// 使用长整型变量
long lastDebounceTime = 0;  // 上次按键触发时间
long debounceDelay = 50;    // 去抖时间，根据实际情况调整

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // 初始化led的状态
  digitalWrite(ledPin, ledState);
}

void loop() {
  // 读取按键状态赋值到一个变量
  int reading = digitalRead(buttonPin);
 

  // 如果按键状态变化，不过是由于抖动还是按键按下造成的
  // 下面的程序都需要进行这一步处理
  if (reading != lastButtonState) {
    // 复位去抖时间，就是把当前时间保存下来
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 等过了去抖时间，再次去检测按键的状态
    if (reading != buttonState) {
      buttonState = reading;

      // 如果按键仍然保持上次的状态，我们认为这个按键按下是真实有效的
	  // 每次按下按键需要改变当前的led状态，比如上次是熄灭，现在需要
	  // 点亮，反之亦然。
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  
  // 把led的最终结果输出到对应的引脚
  digitalWrite(ledPin, ledState);

  // 保存当前值，一边下一个循环检测的时候使用
  lastButtonState = reading;
}

