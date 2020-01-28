#include "TM1623.h"

/*send the volue to print Number*/
byte NUM_FOUNT[] = {
  //ABCDEFGH
  0b10110111,  //0 0xB7          A
  0b00000011,  //1 0x06         ---
  0b11010110,  //2 0xD6       C|   |G
  0b11000111,  //3 0xC7         -B-
  0b01100011,  //4 0x63       D|   |H
  0b11100101,  //5 0xE5         -F-     (Dot)E
  0b11110101,  //6 0xF5
  0b10000011,  //7 0x83
  0b11110111,  //8 0xF7
  0b11100111   //9 0xE7

};


void init_seg() {
  pinMode(STB, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT);
  setCommand(0x03);   //Displya mode setting
  setCommand(0x44);   //Data setting command(fixed addr)
  setCommand(0x8F);   // Display control command
}
//===========================================================
/* set the command for write data to segment*/

void setCommand(uint8_t cmd)
{
  digitalWrite(STB, HIGH);
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, cmd);
  digitalWrite(STB, HIGH);
}

//==================================================
/*display number in 7 seg*/

void  Display7seg(uint8_t pos, byte data)
{
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, 0xC0 + (pos << 1));
  shiftOut(DIO, CLK, MSBFIRST, data);
  digitalWrite(STB, HIGH);
}
////===================================================
/* print the integer value*/

void print_int(int data)
{
  uint8_t  cnt = 0;
  if (data < 0) {
    data = -data;
    Display7seg(5, 0x40);
  }
  if (data == 0) Display7seg(cnt, NUM_FOUNT[data % 10]);
  while (data)
  {
    Display7seg(cnt, NUM_FOUNT[data % 10]);
    data /= 10;
    cnt++;
  }
}

//========================================================
/*print float data in segment*/

/* pass the argument of float number and decimal point position*/

void print_float( float f, uint8_t dp_pos)
{
  uint8_t f_cnt = 0;
  uint8_t pos = dp_pos;
  while (pos) {
    f *= 10;
    pos--;
  }
  int data = (int)f ;
  Serial.println("FLOAT:" + String(data));
  while (data)
  {
    if (f_cnt == dp_pos)
    {
      Display7seg(f_cnt, NUM_FOUNT[data % 10] | 0x08);
    }
    else
    {
      Display7seg(f_cnt, NUM_FOUNT[data % 10]);
    }
    f_cnt++;
    data /= 10;
  }
}

//=======================================================
/* print ERROR massage*/

void print_ERROR()
{
  Display7seg(0, 0x50); //r
  Display7seg(1, 0x55); //o
  Display7seg(2, 0x50); //r
  Display7seg(3, 0x50); //r
  Display7seg(4, 0xF4); //E

}

//=========================================================
/*clear the all segment */

void Segment_clear()
{
  Display7seg(0, 0x00);
  Display7seg(1, 0x00);
  Display7seg(2, 0x00);
  Display7seg(3, 0x00); 
  Display7seg(4, 0x00); 
  Display7seg(5, 0x00); 
  Display7seg(6, 0x00); 
}
//========================================================
/*clear one  segment */

void Segment_clear(uint8_t i)
{
  Display7seg(i, 0x00);
}

//===========================================================
