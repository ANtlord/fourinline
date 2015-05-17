#include "../header/Chip.h"

Chip::Chip(const wxPoint &point, const wxSize &size) : GameObject(point, size)
{
    parent = NULL;  // This field will be column, in which game chip will be set.
}

void Chip::draw(ChipColor color){
    // This arrays have coordinates of game chip & coordinates of texture.
    GLfloat quadCoords[5] = {(GLfloat)position.x, (GLfloat)position.x+size.GetWidth(),
                             (GLfloat)position.y, (GLfloat)position.y+size.GetHeight(), -1.0f};

    GLfloat texCoords[4];
    texCoords[2] = 0.5;
    texCoords[3] = 0.0;
    if (color == red){
        texCoords[0] = 0.0;
        texCoords[1] = 0.5;
    }
    else {
        texCoords[0] = 0.5;
        texCoords[1] = 1;
    }
    GraphicManager::drawTexturedQuad(quadCoords, texCoords);
}

void Chip::initTaking(GameObject &col){
    animating = true;
    parent = &col;  // Makes link between column and gamechip.

    // "finishLine" is point of animate's end.
    finishLine = parent->countFilledSlots() * size.GetHeight();
}

bool Chip::animate(){
    if (animating == true) {
        if (this->position.y <= this->finishLine){
            animating = false;
            parent->append();
            return animating;
        }
        else {
            this->position.y -= 10; // Moves gamechip.
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

            this->draw(ChipColor(GameStates::activePlayer));
            return animating;
        }
    }
}

Chip::~Chip(){
    delete parent;
}
