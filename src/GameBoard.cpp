#include "../header/GameBoard.h"

GameBoard::GameBoard(const wxPoint &point, const wxSize &size) : NUM_COLUMNS(7),
                     GameObject(point, size)
{
    columns = new Column*[NUM_COLUMNS]; // Creates all columns, but doesn't draw.
    for (char i=0; i<NUM_COLUMNS; ++i){
        short width = this->size.GetWidth() / NUM_COLUMNS;
        short height = this->size.GetHeight();
        columns[i] = new Column(wxPoint(i * width, position.y), wxSize(width, height));
    }
}

void GameBoard::draw()
{
    if (glIsEnabled(GL_TEXTURE_2D) == false){
        glEnable(GL_TEXTURE_2D);
    }
    if (glIsEnabled(GL_DEPTH_TEST) == true){
        glDisable(GL_DEPTH_TEST);
    }
    if (glIsEnabled(GL_BLEND) == false){
        glEnable(GL_BLEND);
    }

    for (char i=0; i<NUM_COLUMNS; ++i){
        short width = this->size.GetWidth() / NUM_COLUMNS;
        short height = this->size.GetHeight();
        columns[i]->draw();
    }

}

Column* GameBoard::getColumn(unsigned char i) {
    return this->columns[i];
}

GameBoard::~GameBoard(){
    delete [] columns;
}
