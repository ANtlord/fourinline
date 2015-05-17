#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GraphicManager.h"
class GameObject {
    public:
        GameObject(const wxPoint &point = wxPoint(0,0),
                   const wxSize &size = wxSize(100, 100));
        ~GameObject();
        wxPoint position;
        wxSize size;
        enum SlotVals : char {none = -1 , greenChip=0, redChip=1};
        virtual void append(){};            // This methods may be in Column.
        virtual int countFilledSlots(){};   // They need for Chip.

    protected:


    private:


};

#endif
