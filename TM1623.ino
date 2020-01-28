#include "TM1623.h"

void setup() {
  Serial.begin(115200);
  init_seg(); // TO intiate TM1623
}


int cnt=0;


void loop() {
  
 print_ERROR();    // display erroe massage 
 
 for(uint8_t i =0; i < 7; i++)
 {
    Segment_clear(i);
    delay(1000);
    yield();
 }
 print_ERROR();
 delay(1000);
 Segment_clear();
 delay(1000);
 print_int(-123);
 delay(1000);
 Segment_clear();
 delay(1000);
 print_float( 123.12 , 3);
delay(2000);
 yield();

}
