#include "7segmentdisplay.h"
#include "Arduino.h"
SevenSegmentDisplay::SevenSegmentDisplay(int _STCP,int _SHCP,int _DS){
  pinMode(_STCP,OUTPUT);
  pinMode(_SHCP,OUTPUT);
  pinMode(_DS,OUTPUT);
  ST_CP=_STCP;
  SH_CP=_SHCP;
  DS=_DS;
}
void SevenSegmentDisplay::write(int _number,int dly){
    int LED [10]{
      0xEF, //0    0xE7
      0x8C, //1
      0xDB, //2   0xD3
      0xDE, //3   0xD6
      0xBC, // 4  0xB4
      0x7E, // 5  0x76
      0x7F, //6
      0xEC, //7   0xE4
      0xFF, //8
      0xFE, //9   0xF6
    };
    if(_number>=9){
      _number=9;
    }else if(_number<=0){
      _number=0;
    }
    digitalWrite(ST_CP, LOW);
    delay(dly);
    shiftOut(DS, SH_CP, LSBFIRST, LED[_number]);
    digitalWrite(ST_CP, HIGH);
}
void SevenSegmentDisplay::close(){
    digitalWrite(ST_CP, LOW);
    delay(1000);
    shiftOut(DS, SH_CP, LSBFIRST, 0x00);
    digitalWrite(ST_CP, HIGH);
    delay(1000);
}
