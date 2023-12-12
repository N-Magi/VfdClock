#include "RX8900.h"

void RX8900::setup(){
  delay(100);
  Wire.begin();

  init(); 
};

bool RX8900::getVL(){
  byte flag = readByte(Flag_Register_reg);
  bool vlflag = ((flag >> 1) & 0x01 > 1);
  return vlflag;
}

void RX8900::init(){
  writeByte(Extension_Register_reg,0x08);//set WEEK ALARM , 1Hz to FOUT
  writeByte(Flag_Register_reg,     0x00);//reset all flag
  reset();
};

void RX8900::reset(){
  writeByte(Control_Register_reg,(readByte(Control_Register_reg) | 0b00000001));
};

TimeData RX8900::getTime(){
  TimeData time;
  time.year = convFromBCD(readByte(YEAR_reg));
  time.month = convFromBCD(readByte(MONTH_reg));
  time.day = convFromBCD(readByte(DAY_reg));
  time.hour = convFromBCD(readByte(HOUR_reg));
  time.min = convFromBCD(readByte(MIN_reg));
  time.sec = convFromBCD(readByte(SEC_reg));
  return time;
}

void RX8900::setTime(TimeData time){
  writeByte(YEAR_reg,convToBCD(time.year));
  writeByte(MONTH_reg, convToBCD(time.month));
  writeByte(DAY_reg, convToBCD(time.day));
  writeByte(HOUR_reg, convToBCD(time.hour));
  writeByte(MIN_reg, convToBCD(time.min));
  writeByte(SEC_reg, convToBCD(time.sec));
}

byte RX8900::convFromBCD(byte data ){
  byte MSB = data >> 4;
  byte LSB = data & 0x0f;
  uint8_t result  = MSB * 10 + LSB;
  return result;
}

byte RX8900::convToBCD(byte data ){
  byte MSB = (data / 10);
  byte LSB = (data % 10);
  return (MSB << 4 | LSB);
}

void RX8900::readRegister(void)
{
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(SEC_reg);//set 0x00(SEC)Register address
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, Control_Register_reg); //set 0x0F(Control Register)Register address
  SEC = Wire.read();                //0x00
  MIN = Wire.read();                //0x01
  HOUR = Wire.read();               //0x02
  WEEK = Wire.read();               //0x03
  DAY = Wire.read();                //0x04
  MONTH = Wire.read();              //0x05
  YEAR = Wire.read();               //0x06
  RAM = Wire.read();                //0x07
  MIN_Alarm = Wire.read();          //0x08
  HOUR_Alarm = Wire.read();         //0x09
  WEEK_DAY_Alarm = Wire.read();     //0x0A
  Timer_Counter_0 = Wire.read();    //0x0B
  Timer_Counter_1 = Wire.read();    //0x0C
  Extension_Register = Wire.read(); //0x0D
  Flag_Register = Wire.read();      //0x0E
  Control_Register = Wire.read();   //0x0F
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(TEMP_reg);             //set TEMP_reg 0x17
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, 2);//Backup_Function_reg ～ TEMP_reg
  TEMP = Wire.read();               //0x17
  Backup_Function = Wire.read();    //0x18
};

byte RX8900::readByte(byte reg)
{
  byte data = 0;
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(RX8900A_ADRS, 1);
  data = Wire.read();      //RECEIVE 1BYTE
  return data;
}

void RX8900::writeByte(byte reg, byte data)
{
  Wire.beginTransmission(RX8900A_ADRS);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
};
