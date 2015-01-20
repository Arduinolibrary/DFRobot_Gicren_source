#include "GI2C_V11.h"
#include <Wire.h>

#define PotentiometerA A0

unsigned char Buf[31+1];
GI2CV11 Booster_BxxV2A5(Buf,sizeof(Buf));

void setup() 
{ 
}

void loop() 
{ 
  Booster_BxxV2A5.Read(1,1,31);
  while(1)
  {
    Buf[25]=(unsigned long int)250*analogRead(PotentiometerA)/1024;
    Booster_BxxV2A5.Write(1,25,1);
    delay(50);
  }
}
