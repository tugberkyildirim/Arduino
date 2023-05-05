/*
 * PIN 12 ST_CP  4
 * PIN 11 SH_CP 5
 * PIN 14 DS    6
 * POT A0
 * SevenSegmentDisplay display(ST_CP, SH_CP,DS);
 * display.write(number>=0 and number<=9),delay=500);
 *
 * github.com/tugberkyildirim
*/
#include "7segmentdisplay.h"
#define ST_CP 4
#define SH_CP 5
#define DS 6
#define POT A0

SevenSegmentDisplay display(ST_CP, SH_CP,DS);
void setup() {
  Serial.begin(9600);
}

void loop() {
  int pot=analogRead(POT);
  pot=map(pot,0,1023,0,10);
  Serial.println(pot);
  display.write(pot,500);
}
