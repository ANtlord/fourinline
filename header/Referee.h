#ifndef REFEREE_H
#define REFEREE_H

#include <iostream>
#include "GameBoard.h"

class Referee {
    public:
        Referee(const GameBoard& gameBoard);
        ~Referee();
        enum WinVals : char {none = -1, greenPlayer = 0, redPlayer = 1};
        void checkGame(unsigned char colPos);
        WinVals winner;


    protected:


    private:
        const GameBoard GAME_BOARD;
        WinVals verticalCheck(Column& col);
        WinVals horizontalCheck(unsigned char colPos);
        WinVals mainDiagonalCheck(unsigned char colPos);
        WinVals secondaryDiagonalCheck(unsigned char colPos);
        const char MIN_STEPS_FOR_WIN;
//        union {
            char const CHIPS_FOR_WIN;
            char const MIN_VERTICAL_CHIPS;
//        };

};

#endif
