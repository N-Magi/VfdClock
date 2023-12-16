#pragma once

#include <SPI.h>
#include "config.h"
#include "matrixData.h"
#include "CliTerminal.h"

#define SPEAKER 14

//display configuration
#define DP18 7
#define DP21 8
#define SRCLR 21
#define RCK 20
#define LED 6

#define SW_ACCEPT 10
#define SW_BACK 11
#define SW_P 12
#define SW_N 13

//ADC configuration
#define V18 1
#define V21 0

class Board {
    public:
        Board();
        void render();
        void init();
        
        MatrixData* getDisplayData();
        void setDiplsayData(MatrixData* displayData);
        uint8_t getBtnStat();

        void commands(Cli_Terminal *term);

        ~Board();
    private:
        MatrixData *displayData;
        uint8_t p_keyState;
};


