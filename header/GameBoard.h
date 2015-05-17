#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Column.h"
#include <wx/gdicmn.h>
#include <iostream>

class GameBoard : public GameObject {
    public:
        GameBoard(const wxPoint &point = wxPoint(0,0),
                  const wxSize &size = wxSize(100, 100));
        ~GameBoard();

        void draw();
        Column* getColumn(unsigned char i);
        const unsigned char NUM_COLUMNS;
        Column **columns;
    protected:


    private:
};

#endif
