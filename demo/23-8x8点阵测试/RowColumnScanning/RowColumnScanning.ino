/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 8x8点阵行列扫描
 

 
 行是阳极
 列是阴极
 ---------
 
 8x8点阵引脚定义
 * 数字引脚2-13
 * 模拟引脚2-5作为数字引脚16-19
 电位器引脚定义
 * 中心抽头连接到模拟信号0和1脚
 * 另外2端连接+5V和GND
 
 原版应用请参考这里
 http://www.arduino.cc/en/Tutorial/RowColumnScanning
 
 */


// 行引脚对应的数组
const int row[8] = {
  2,7,19,5,13,18,12,16 };

// 列引脚对应的数组
const int col[8] = {
  6,11,10,3,17,4,8,9  };

// 点阵对应的数组
int pixels[8][8];           

// 光标位置
int x = 5;
int y = 5;

void setup() {
  // 初始化I/O口作为输出
  // 循环设置所有需要的引脚
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // 初始化输出引脚
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // 把对应的引脚引脚置高，确保点亮LED
    digitalWrite(col[thisPin], HIGH);    
  }

  // 初始化矩阵像素，8行8列
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // 读入模拟输入值
  readSensors();

  // 绘制屏幕
  refreshScreen();
}

void readSensors() {
  // 关闭最后1个像素位置
  pixels[x][y] = HIGH;
  // 读取X和Y的电位器值
  x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
  y = map(analogRead(A1), 0, 1023, 0, 7);
  // 下次刷新屏幕时候拉低电平，以便点亮led
  pixels[x][y] = LOW;

}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}
