//*********************** Copyright Gicren Robotics and Electronics ***********************
//*File Name    : G485_V11.cpp
//*Author       : Gicren Team (www.gicren.com)
//*Version      : V0001
//*Data         : 11/01/2013
//*Description  : This file provides all the G485_V11 firmware functions
//*****************************************************************************************

#include <Arduino.h>
#include "G485_V11.h"

//------------------------------------------------------------
//Constructor
//------------------------------------------------------------
G485V11::G485V11(unsigned char *BufAddr,unsigned char Num)
{  
  this->BufStartAddr=BufAddr;
  this->BufSize=Num;
  this->Delay=10;
}

//--------------------- Write Registers ----------------------
//SSA     : System Slave Address
//RegAddr : The start address of user registers to be written
//Num     : The number of bytes to be written
//------------------------------------------------------------
unsigned char G485V11::Write(unsigned char SSA,unsigned char RegAddr,unsigned char Num)
{
  unsigned char i,temp,check=0;
  
  if(((unsigned int)RegAddr+(unsigned int)Num)>this->BufSize)  
    return 0xff;
    
  Serial.write(0xff);
  Serial.write(0xff);
  
  temp=(SSA<<1)+G485_WRITE;
  Serial.write(temp);
  check+=temp;
  
  Serial.write(Num+2);
  check+=(Num+2);
  
  Serial.write(RegAddr);
  check+=RegAddr;
  
  for(i=RegAddr;i<(RegAddr+Num);i++)
  {
    temp=*(this->BufStartAddr+(i%this->BufSize));
    Serial.write(temp);
    check+=temp;
  }
  
  Serial.write(~check);
  
  return 0;
}

//---------------------- Read Registers ----------------------
//SSA     : System Slave Address
//RegAddr : The start address of user registers to be read
//Num     : The number of bytes to be read
//------------------------------------------------------------
unsigned char G485V11::Read(unsigned char SSA,unsigned char RegAddr,unsigned char Num)
{
  unsigned char i,temp,count=0,check=0;
  
  if(((unsigned int)RegAddr+(unsigned int)Num)>this->BufSize)  
    return 0xff;
  
  while(Serial.available())
    Serial.read();
      
  Serial.write(0xff);
  Serial.write(0xff);
  
  temp=(SSA<<1)+G485_READ;
  Serial.write(temp);
  check+=temp;
  
  Serial.write(0x03);
  check+=0x03;
  
  Serial.write(RegAddr);
  check+=RegAddr;
  
  Serial.write(Num);
  check+=Num;
  
  Serial.write(~check);
  
  delay(100);
  
  while(count!=Serial.available())
  {
    count=Serial.available();
    delay(this->Delay);
  }
  
  if(count==(Num+6))
  {
    Serial.read();
    Serial.read();
    Serial.read();
    temp=Serial.read();
    Serial.read();
    check=0;
    check+=((G485_SMA<<1)+G485_READ);
    check+=temp;
    check+=RegAddr;
    for(i=RegAddr;i<(RegAddr+Num);i++)
    {
      temp=Serial.read();
      *(this->BufStartAddr+(i%this->BufSize))=temp;
      check+=temp;
    }
    temp=~Serial.read();
    if(check==temp)
      return 0;
    else
      return 0xff;
  }
  else
  {
    while(Serial.available())
      Serial.read();
    return 0xff;
  }
}

//------------------------ Send SPID -------------------------
//SSA     : System Slave Address
//PID     : SPID Value
//------------------------------------------------------------
void G485V11::SendSPID(unsigned char SSA,unsigned char PID)
{
  unsigned char temp,check=0;
  
  Serial.write(0xff);
  Serial.write(0xff);
  
  temp=(SSA<<1)+G485_WRITE;
  Serial.write(temp);
  check+=temp;
  
  Serial.write(0x02);
  check+=0x02;
  
  Serial.write(PID);
  check+=PID;
  
  Serial.write(~check);
}

//---------------------- Get Error Word ----------------------
//SSA     : System Slave Address
//------------------------------------------------------------
unsigned int G485V11::GetError(unsigned char SSA)
{
  unsigned char temp,count=0,check=0;
  unsigned int error;
  
  while(Serial.available())
    Serial.read();
    
  Serial.write(0xff);
  Serial.write(0xff);
  
  temp=(SSA<<1)+G485_READ;
  Serial.write(temp);
  check+=temp;
  
  Serial.write(0x02);
  check+=0x02;
  
  Serial.write(G485_EPID);
  check+=G485_EPID;
  
  Serial.write(~check);
  
  delay(100);
  
  while(count!=Serial.available())
  {
    count=Serial.available();
    delay(this->Delay);
  }
  
  if(count==8)
  {
    Serial.read();
    Serial.read();
    Serial.read();
    temp=Serial.read();
    Serial.read();
    check=0;
    check+=((G485_SMA<<1)+G485_READ);
    check+=temp;
    check+=G485_EPID;
    
    temp=Serial.read();
    check+=temp;
    error=temp;
    error<<=8;
    temp=Serial.read();
    check+=temp;
    error+=temp;
    
    temp=~Serial.read();
    if(check==temp)
      return error;
    else
      return 0xffff;
  }
  else
  {
    while(Serial.available())
      Serial.read();
    return 0xffff;
  }
}

//*********************** Copyright Gicren Robotics and Electronics ***********************
