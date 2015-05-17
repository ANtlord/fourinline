#ifndef COLUMN_H
#define COLUMN_H

#include "GameObject.h"
#include "Chip.h"

class Column : public GameObject {
    public:
        friend class Referee;
        Column(const wxPoint &point = wxPoint(0,0),
               const wxSize &size = wxSize(100, 100));
        ~Column();
        bool isFull();
        int countFilledSlots();
        void append();
        void draw();


    protected:


    private:
        static GLuint texture;
        const unsigned char NUM_SLOTS;
        SlotVals slots[6];
        void drawChips();

};

#endif
