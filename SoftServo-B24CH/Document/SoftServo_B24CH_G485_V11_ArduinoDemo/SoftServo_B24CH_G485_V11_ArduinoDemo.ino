/*
Initialize the serial port,and then send the sync bytes. 
It's unnecessary to send the sync bytes if the baud rate is not higher 
than 28800bps or it is allowed to discard the first instruction packet.

Author: Gicren Team (www.gicren.com)

Date  : 08/29/2014
*/

#include "G485_V11.h"

unsigned char Buf[61+1];
G485V11 SoftServo_B24CH(Buf,sizeof(Buf));

void setup()
{
  Serial.begin(115200);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void loop()
{
  unsigned char i;
  unsigned char temp;

  while(1)
  {
    for(i=13;i<13+24;i++)
      Buf[i]=50;
    SoftServo_B24CH.Write(1,13,24);
    delay(1000);
    
    for(i=13;i<13+24;i++)
      Buf[i]=200;
    SoftServo_B24CH.Write(1,13,24);
    delay(1000);
  }
} 
