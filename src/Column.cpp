#include "../header/Column.h"

Column::Column(const wxPoint &point, const wxSize &size) : NUM_SLOTS(6),
               GameObject(point, size)
{
    for(short i=0; i<NUM_SLOTS; ++i){
        slots[i] = none;
    }
}

void Column::draw(){
    glColor3f(1.0f,1.0f,1.0f);
    this->drawChips();

    for(short i=0; i<NUM_SLOTS; ++i){   // Programm draws slots in column.
        short blockHeight = size.GetHeight() / NUM_SLOTS;   // Get height of slot.

        // This arrays have coordinates of column's slot & coordinates of texture.
        GLfloat texCoords[4] = {0.0f, 0.5f, 1.0f, 0.5f};
//        GLfloat texCoords[4] = {-1.0f, 0., 1.0f, 0.5f};
        GLfloat quadCoords[5] = {(GLfloat)position.x, (GLfloat)position.x + size.GetWidth(),
                                (GLfloat)blockHeight * i + position.y,
                                (GLfloat)blockHeight * i + position.y + blockHeight, 0.0f};
        GraphicManager::drawTexturedQuad(quadCoords, texCoords);
    }
}

void Column::drawChips(){
    short blockHeight = size.GetHeight() / NUM_SLOTS;   // Get height of slot.
    for(short i=0; i < NUM_SLOTS; ++i){
        if (slots[i] != none){  // To draw game chips, where
            Chip chip(wxPoint(position.x, i * blockHeight));
            chip.draw(Chip::ChipColor(slots[i]));
        }
        else
            i=NUM_SLOTS;    // Break cycle.
    }
}

void Column::append(){
    for (unsigned char i=0; i<NUM_SLOTS; ++i){  // Get all filled slots.
        if (slots[i] == none){ // Where find clear slot, than fill it.
            slots[i] = SlotVals(GameStates::activePlayer);
            GameStates::activePlayer = !GameStates::activePlayer;
            i=NUM_SLOTS;    // Break cycle.
        }
    }
}

int Column::countFilledSlots(){
    for (unsigned char i=0; i<NUM_SLOTS; ++i){
        if (slots[i] == none)
            return i;
    }
    return NUM_SLOTS;
}

bool Column::isFull(){
    return countFilledSlots() == NUM_SLOTS;
}

Column::~Column(){

}
