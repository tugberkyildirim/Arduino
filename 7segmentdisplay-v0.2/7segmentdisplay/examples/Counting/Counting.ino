/*
 * PIN 12 ST_CP  4
 * PIN 11 SH_CP 5
 * PIN 14 DS    6
 * 
 * SevenSegmentDisplay display(ST_CP, SH_CP,DS);
 * display.write(number>=0 and number<=9),delay=500);
 * https://github.com/tugberkyildirim
*/
#include "7segmentdisplay.h"
#define ST_CP  4
#define SH_CP 5
#define DS    6

SevenSegmentDisplay display(ST_CP, SH_CP,DS);
void setup() {
  
}

void loop(){
  for(int i=0;i<10;i++){
    display.write(i,500);
    
  }
  delay(500);
}
