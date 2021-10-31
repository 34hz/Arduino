/*
 
 播放一首音乐
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 如果使用LY-51S独立模块开发板，参考以下链接：
 http://www.doflye.net/viewthread.php?tid=5297&extra=
 官方硬件和软件参考地址：
 http://arduino.cc/en/Tutorial/Tone
 
 */
 #include "pitches.h"

// 乐曲中的音符
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// 音符持续时间: 4 = 四分音符, 8 = 八分音符 等等:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {
  // 顺序加载乐曲中的音符
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // 用1S为基准计算音符持续时间
    //比如 四分音符 = 1000 / 4, 八分音符 = 1000/8, 等等
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // 设置一个最小的时间间隔来区分音符
	// 一般正常音符的1.3倍效果较好
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // 停止播放音乐
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
