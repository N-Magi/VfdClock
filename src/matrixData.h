#pragma once

#include <Arduino.h>

//DCEGBFA IV18
//DCEGBFA IV21
static uint8_t NUMBERTABLE []
{
    0b1110111,//0
    0b0100100,//1
    0b1011101,//2
    0b1101101,//3
    0b0101110,//4
    0b1101011,//5
    0b1111011,//6
    0b0100111,//7
    0b1111111,//8
    0b1101111,//9
    0b0001000,//- 10
    0b0000000//none 11

};
//913587642
static uint16_t DIGITTABLE_18 []
{
    0b010000000,
    0b000000001,
    0b001000000,
    0b000000010,
    0b000100000,
    0b000000100,
    0b000001000,
    0b000010000,
    0b100000000,

};

//35798642[]1
static uint16_t DIGITTABLE_21 []
{
    0b000000001,
    0b000000010,
    0b100000000,
    0b000000100,
    0b010000000,
    0b000001000,
    0b001000000,
    0b000010000,
    0b000100000,

};


enum specificData{
    dot18 = 10,
    dot21 = 11,
};

class MatrixData{
    public:
        
        uint32_t data;
        bool dp18;
        bool dp21;

        MatrixData();
        MatrixData(uint32_t data, bool dp18, bool dp21);

        static MatrixData generateMatrixData(ushort* num18,ushort* num21);
        static MatrixData generateCustomMatrixData(ushort digit18, uint16_t matrix18,ushort num21, uint16_t matrix21);
};
