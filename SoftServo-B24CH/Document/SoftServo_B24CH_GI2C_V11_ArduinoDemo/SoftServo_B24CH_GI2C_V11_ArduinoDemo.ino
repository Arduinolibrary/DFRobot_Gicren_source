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

unsigned char Buf[61+1];
GI2CV11 SoftServo_B24CH(Buf,sizeof(Buf));

void setup()
{

}

void loop()
{
  unsigned char i;

  while(1)
  {
    for(i=13;i<13+24;i++)
      Buf[i]=50;
    while(SoftServo_B24CH.Write(1,13,24));
    delay(1000);
    
    for(i=13;i<13+24;i++)
      Buf[i]=200;
    while(SoftServo_B24CH.Write(1,13,24));
    delay(1000);
  }
} 
