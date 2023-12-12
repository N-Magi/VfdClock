#include "matrixData.h"


MatrixData::MatrixData(){
    data = 0x00;
    dp18 = false;
    dp21 = false;
}

MatrixData::MatrixData(uint32_t data, bool dp18, bool dp21){
    this->data = data;
    this->dp18 = dp18;
    this->dp21 = dp21;
}

MatrixData MatrixData::generateMatrixData(ushort* num18, ushort* num21){
    
    uint talbeSize = sizeof(NUMBERTABLE);
    if(num18[1] >  talbeSize || num21[1] > talbeSize) return MatrixData();
    
    uint16_t packet18 = 0x0000;
    ushort digit18 = num18[0];
    ushort number18 = num18[1];
    packet18 |= (DIGITTABLE_18[digit18] & 0x1ff) << 7 | (NUMBERTABLE[number18] & 0x007f);

    uint16_t packet21 = 0x0000;
    ushort digit21 = num21[0];
    ushort number21 = num21[1];
    packet21 |= (DIGITTABLE_21[digit21] & 0x1fe) << 7 | (NUMBERTABLE[number21] & 0x007f)<< 1 | DIGITTABLE_21[digit21] & 0x01;

    return MatrixData( (packet18 << 16|packet21) , false, false);
}

MatrixData MatrixData::generateCustomMatrixData(ushort digit18, uint16_t matrix18,ushort digit21, uint16_t matrix21){
    uint16_t packet18 = 0x0000;
    //ushort digit18 = digit18;
    packet18 |= (DIGITTABLE_18[digit18] & 0x1ff) << 7 | (matrix18 & 0x007f);

    uint16_t packet21 = 0x0000;
    //ushort digit21 = digit18;
    packet21 |= (DIGITTABLE_21[digit21] & 0x1FE) << 7 | (matrix21& 0x007f) << 1 | DIGITTABLE_21[digit21] & 0x01;

    return MatrixData( (packet18 << 16|packet21) , false, false);

}
