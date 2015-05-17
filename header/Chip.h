#ifndef CHIP_H
#define CHIP_H

#include "GameObject.h"
#include "GameStates.h"

class Chip : public GameObject {
    public:
        Chip(const wxPoint &point = wxPoint(0,0),
             const wxSize &size = wxSize(100, 100));
        ~Chip();
        enum ChipColor : bool {green=false, red=true};
        bool animate();
        void draw(ChipColor color);
        void initTaking(GameObject &col);


    protected:


    private:
        short finishLine;
        bool animating;
        GameObject * parent;
};
#endif
