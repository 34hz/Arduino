/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 4x4矩阵键盘，可以使用LY-51S上面的键盘，也可以使用单独的薄膜键盘

 使用独立模块开发板LY-51S连接详情：
 http://www.doflye.net/viewthread.php?tid=5304&extra=

 */
const int numRows = 4;//定义4行
const int numCols = 4;//定义4列
const int debounceTime = 20;//去抖动时间长度

const char keymap[numRows][numCols]= {//键值，可以按需要更改

  { '1','2','3','+' },

  {'4','5','6','-'  },

  {'7','8','9','X'  },

  {'*','0','#','/'  }
};
const int rowPins[numRows] = {7,6,5,4};//设置硬件对应的引脚
const int colPins[numCols] = {11,10,9,8};
//初始化功能
void setup(){
Serial.begin(9600);
for(int row = 0; row < numRows; row++){
   pinMode(rowPins[row],INPUT);
   digitalWrite(rowPins[row],HIGH);

}
for(int column = 0;column < numCols; column++){
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH);
 }
}
//主循环
void loop() {
    // 添加其他的程序，循环运行
    char key = getkey();
    if(key !=0){
      Serial.print("Got key ");//串口打印键值
      Serial.println(key);
    }
  }
//读取键值程序
char getkey(){
    char key = 0;
    for(int column = 0;column < numCols; column++){
      digitalWrite(colPins[column],LOW);
      for(int row = 0 ;row < numRows; row++){
        if(digitalRead(rowPins[row]) == LOW){ //是否有按键按下
          delay(debounceTime);
          while(digitalRead(rowPins[row]) == LOW)  //等待按键释放
            ;
          key = keymap[row][column];   
        }
      }
      digitalWrite(colPins[column],HIGH); //De-active the current column
    }
    return key;
  }

