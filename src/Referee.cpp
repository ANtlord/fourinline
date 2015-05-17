#include "../header/Referee.h"

Referee::Referee(const GameBoard& gameBoard) : MIN_STEPS_FOR_WIN(6),
    CHIPS_FOR_WIN(3), GAME_BOARD(gameBoard), MIN_VERTICAL_CHIPS(3)
{
    winner = none;
    //  Values of constants in real must be greater by one. But programm works
    //  asyncronical and when referee will check game, column in game board
    //  won't appended.
}

Referee::WinVals Referee::secondaryDiagonalCheck(unsigned char colPos)
{
    char curLine = GAME_BOARD.columns[colPos]->countFilledSlots();
    char points = 0;
    bool player = GameObject::SlotVals(GameStates::activePlayer);

    // Checking similar chips on secondary vector from to down.
    for (char i=-1; i >= -CHIPS_FOR_WIN; --i) {
        // Check coordinates of checking slots.
        if (colPos + i >= 0 && curLine - i >= 0 && colPos + i < GAME_BOARD.NUM_COLUMNS)
            if (GAME_BOARD.columns[colPos + i]->slots[curLine - i] == player)
                ++points;
            else
                i = -CHIPS_FOR_WIN + i;
        else
            i = -CHIPS_FOR_WIN + i;
    }

    // Checking similar chips on secondary vector from to up.
    for (char i = 1; i <= CHIPS_FOR_WIN; ++i) {
        // Check coordinates of checking slots.
        if (colPos + i >= 0 && curLine - i >= 0 && colPos + i < GAME_BOARD.NUM_COLUMNS)
            if (GAME_BOARD.columns[colPos + i]->slots[curLine - i] == player)
                ++points;
            else
                i = CHIPS_FOR_WIN + i;
        else
            i = CHIPS_FOR_WIN + i;
    }

    return (points == CHIPS_FOR_WIN) ? WinVals(player) : none;
}

Referee::WinVals Referee::mainDiagonalCheck(unsigned char colPos)
{
    char curLine = GAME_BOARD.columns[colPos]->countFilledSlots();
    char points = 0;
    bool player = GameObject::SlotVals(GameStates::activePlayer);

    for (char i=-1; i >= -CHIPS_FOR_WIN; --i) {
        if (colPos + i >= 0 && curLine + i >= 0 && colPos + i < GAME_BOARD.NUM_COLUMNS)
            if (GAME_BOARD.columns[colPos + i]->slots[curLine + i] == player)
                ++points;
            else
                i = -CHIPS_FOR_WIN + i;
        else
            i = -CHIPS_FOR_WIN + i;
    }

    for (char i = 1; i <= CHIPS_FOR_WIN; ++i) {
        if (colPos + i >= 0 && curLine + i >= 0 && colPos + i < GAME_BOARD.NUM_COLUMNS)
            if (GAME_BOARD.columns[colPos + i]->slots[curLine + i] == player)
                ++points;
            else
                i = CHIPS_FOR_WIN + i;
        else
            i = CHIPS_FOR_WIN + i;
    }

    return (points == CHIPS_FOR_WIN) ? WinVals(player) : none;
}

Referee::WinVals Referee::horizontalCheck(unsigned char colPos)
{
    char curLine = GAME_BOARD.columns[colPos]->countFilledSlots();
    unsigned char points = 0;

    const char LEFT_COL_POS = (colPos > CHIPS_FOR_WIN) ? (colPos - CHIPS_FOR_WIN) : 0;
    const char RIGHT_COL_POS = (colPos >= CHIPS_FOR_WIN) ?
        (GAME_BOARD.NUM_COLUMNS-1) : (colPos + CHIPS_FOR_WIN);

    bool player = GameObject::SlotVals(GameStates::activePlayer);

    // At this cycle, programm find chips of current player on left.
    if (colPos > 0)
        for(char i = colPos-1; i >= LEFT_COL_POS; --i){     // Checking cols on left.
            if (GAME_BOARD.columns[i]->slots[curLine] == player){
                ++points;
            }
            else
                i=LEFT_COL_POS-1;   // Break cycle.
        }
    // At this cycle, programm find chips of current player on right.
    if (colPos < GAME_BOARD.NUM_COLUMNS){
        for(char i = colPos+1; i <= RIGHT_COL_POS; ++i){    // Checking cols on right.
            if (GAME_BOARD.columns[i]->slots[curLine] == player){
                ++points;
            }
            else
                i=RIGHT_COL_POS+2;  // Break cycle.
        }
    }
    return (points == CHIPS_FOR_WIN) ? WinVals(player) : none;
}

Referee::WinVals Referee::verticalCheck(Column& col)
{
    unsigned char filledSlots = col.countFilledSlots();
    unsigned char needingSlots = filledSlots - CHIPS_FOR_WIN;
    bool player = GameStates::activePlayer;

    for (char i=(filledSlots-1); i>=needingSlots; --i) {
        if (col.slots[i] != GameObject::SlotVals(player)){  // If in check vector different chips.
            return none;    // Winner doesn't exists.
        }
    }
    return WinVals(player);
}

void Referee::checkGame(unsigned char colPos)
{
    unsigned char steps = GameStates::steps;
    if (steps > MIN_STEPS_FOR_WIN){
        if (GAME_BOARD.columns[colPos]->countFilledSlots() >= MIN_VERTICAL_CHIPS){
            winner = verticalCheck(*GAME_BOARD.columns[colPos]);
        }
        if (winner == none){
            winner = horizontalCheck(colPos);
        }
        if (winner == none){
            winner = mainDiagonalCheck(colPos);
        }
        if (winner == none){
            winner = secondaryDiagonalCheck(colPos);
        }
    }
}

Referee::~Referee(){

}
