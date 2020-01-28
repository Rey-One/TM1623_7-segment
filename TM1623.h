#ifndef __My_TM1623_H__
#define __My_TM1623_H__

#include "Arduino.h"


/*nodemcu ESP2866 pin */
#define STB D5  //gpio 5
#define CLK D3  // gpio 4
#define DIO D6  // gpio 2

/* define function */

void setCommand(uint8_t );  // set commond 
void init_seg(void);        
void Reset(void);           // reset commond 
void print_int(int );       // display integer on 7 segment
void print_float( float ,uint8_t );    // display float value
void print_ERROR();                      // display ERROR massage
void Display7seg(uint8_t , byte );         // dispaly value on 7 segment 
void Segment_clear(void);                // claer one segment 
void Segment_clear(uint8_t);             // claer all segment 

#endif
