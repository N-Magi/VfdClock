#include "modeClock.h"

void ModeClock::exec(){

}

void ModeClock::createData(ushort *data18, ushort *data21){
  ushort num18[2], num21[2];
  for(int idx = 7; idx >= 0; idx--){
    
    num18[0] = 7 - idx;
    num18[1] = data18[idx];
    num21[0] = 7 - idx;
    num21[1] = data21[idx];

    md[idx] = MatrixData::generateMatrixData(num18,num21);
  }

  num18[0] = 0;
  num18[1] = 11;
  num21[0] = 0;
  num21[1] = 11;
  md[9] = MatrixData::generateMatrixData(num18,num21);

}