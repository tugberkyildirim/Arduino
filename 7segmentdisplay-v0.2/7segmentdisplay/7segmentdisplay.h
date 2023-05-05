#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H
#include "Arduino.h"

class SevenSegmentDisplay{
  private:
  int ST_CP,SH_CP,DS;
  public:
  SevenSegmentDisplay(int STCP,int SHCP,int DS);
  void write(int number,int dly);
  void close();
};

#endif
