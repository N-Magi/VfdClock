#include "board.h"

Board::Board()
{
}

void Board::commands(Cli_Terminal *term)
{
    // term->commands[0]
}

void Board::init()
{
    SPI.setTX(MOSI);
    SPI.setRX(MISO);
    SPI.setSCK(SCK);
    SPI.begin(false);
    pinMode(RCK, OUTPUT);
    pinMode(DP18, OUTPUT);
    pinMode(DP21, OUTPUT);

    pinMode(SW_ACCEPT, INPUT_PULLUP);
    pinMode(SW_BACK, INPUT_PULLUP);
    pinMode(SW_N, INPUT_PULLUP);
    pinMode(SW_P, INPUT_PULLUP);
}

void Board::setDiplsayData(MatrixData *md)
{
    displayData = md;
}

void Board::render()
{

    int displayDataLen = 9; // sizeof(*displayData) / sizeof(MatrixData);
    // Serial.println(displayDataLen);
    for (int idx = 0; idx < displayDataLen; idx++)
    {

        digitalWrite(DP18, 0);
        digitalWrite(DP21, 0);
        digitalWrite(RCK, 0);

        MatrixData matrixData = displayData[idx];
        //[MEMO] matrix data  |16bit for IV21|16bit for IV18|
        // send IV21 then IV18
        for (int cnt = 0; cnt <= 1; cnt++)
        {
            uint16_t datum = (matrixData.data >> (cnt * 16)) & 0xffff;
            // Serial.println(datum);
            SPI.transfer16(datum);
        }

        digitalWrite(RCK, 1);
        digitalWrite(RCK, 0);
        if (matrixData.dp18)
            digitalWrite(DP18, 1);
        if (matrixData.dp21)
            digitalWrite(DP21, 1);

        delayMicroseconds(1000);

    }
}

uint8_t Board::getBtnStat()
{

    uint8_t c_keyState = (~digitalRead(SW_ACCEPT) & 0x01) << 3 |
                         (~digitalRead(SW_BACK) & 0x01) << 2 |
                         (~digitalRead(SW_P) & 0x01) << 1 |
                         (~digitalRead(SW_N) & 0x01);
    uint8_t diff = c_keyState & ~p_keyState;

    p_keyState = c_keyState;
    c_keyState = (diff << 4) + c_keyState;

    return c_keyState;
}

Board::~Board()
{
    SPI.end();
}