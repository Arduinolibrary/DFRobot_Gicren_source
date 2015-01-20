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
GI2CV11 ManShow_RC1(Buf,sizeof(Buf));

void setup() 
{ 

}

void loop() 
{ 
  unsigned char i;
  unsigned long int j;
  ManShow_RC1.Read(1,13,48);
  for(i=13;i<37;i++)
    Buf[i]=50;
  for(i=37;i<61;i++)
    Buf[i]=(i-36)*10;
  while(1)
  {
    for(j=0;j<2677114440;j++)
    {
      for(i=13;i<37;i++)
      {
        if((j+1)%(i-12)==0)
        {
          if(Buf[i]==50)
            Buf[i]=200;
          else if(Buf[i]==200)
            Buf[i]=50;
        }
      }
      delay(200);
      ManShow_RC1.Write(1,13,48);
    }
  }
}
