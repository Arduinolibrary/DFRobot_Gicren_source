/*
Note  : In Arduino Wire library, the buffer-length of I2C is defined as 32. 
It is not allowed to send more than 32 bytes at a time, but you can replace 
"#define TWI_BUFFER_LENGTH 32" with "#define TWI_BUFFER_LENGTH 101" in twi.h 
and replace "#define BUFFER_LENGTH 32" with "#define BUFFER_LENGTH 101" in 
Wire.h to remove the constraint. After all above operations, please restart
Arduino IDE.

Author: Gicren Team (www.gicren.com)

Date  : 08/29/2014
*/

#include "GI2C_V11.h"
#include <Wire.h>

#define ButtonA        2
#define ButtonB        3
#define PositionA      50
#define PositionB      200
#define Potentiometer  A0

unsigned char Buf[61+1];
GI2CV11 ManShow_RC1(Buf,sizeof(Buf));

void setup() 
{ 
  pinMode(ButtonA,INPUT_PULLUP);
  pinMode(ButtonB,INPUT_PULLUP);
}

void loop() 
{ 
  ManShow_RC1.Read(1,13,48);
  while(1)
  {
    Buf[37]=(unsigned long int)250*analogRead(Potentiometer)/1024;
    if(Buf[37]==0)
    {
      Buf[37]=1;
    }
    if((digitalRead(ButtonA)==LOW) && (digitalRead(ButtonB)==HIGH))
    {
      Buf[13]=PositionA;
      ManShow_RC1.Write(1,13,48);
    }
    else if((digitalRead(ButtonA)==HIGH) && (digitalRead(ButtonB)==LOW))
    {
      Buf[13]=PositionB;
      ManShow_RC1.Write(1,13,48);
    }
    delay(20);
  }
}
