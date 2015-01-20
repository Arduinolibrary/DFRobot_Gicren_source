//*********************** Copyright Gicren Robotics and Electronics ***********************
//* File Name    : G485_V11.h
//* Author       : Gicren Team (www.gicren.com)
//* Version      : V0001
//* Data         : 11/01/2013
//* Description  : This file contains all the functions prototypes for the G485_V11 library
//*****************************************************************************************

#ifndef _G485_V11_H
#define _G485_V11_H

#define G485_HPID     0x7f  //Handshake , Get the check byte of last instruction from slave device
#define G485_EPID     0x7e  //Get the Error Word
#define G485_SPID_FC  0x7d  //Factory settings
#define G485_SPID_EE  0x7c  //Update the bytes stored in EEPROM
#define G485_SPID_RS  0x7b  //Restart
#define G485_SPID_EC  0x7a  //Clear the Error Word
#define G485_SPID_CE  0x79  //Enable the immediate write mode
#define G485_SPID_AE  0x78  //Enable the non immediate write mode
#define G485_SPID_AC  0x77  //Action with data from non immediate write mode
#define G485_SPID_DC  0x76  //Control transmission
#define G485_SPID_DM  0x75  //Bulk transmission
#define G485_SPID_BB  0x74  //Disable the Baud Rate auto detection

#define G485_WRITE    0x00  //Write Bit
#define G485_READ     0x01  //Read Bit

#define G485_SMA      127   //System Master address

class G485V11
{
  private:
    unsigned char *BufStartAddr;
    unsigned char BufSize;
    unsigned char Delay;
    
  public:
    G485V11(unsigned char *BufAddr,unsigned char Num);
    unsigned char Write(unsigned char SSA,unsigned char RegAddr,unsigned char Num);
    unsigned char Read(unsigned char SSA,unsigned char RegAddr,unsigned char Num);
    void SendSPID(unsigned char SSA,unsigned char PID);
    unsigned int GetError(unsigned char SSA);
};

#endif

//*********************** Copyright Gicren Robotics and Electronics ***********************
