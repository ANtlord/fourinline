#pragma once
#include "PSound.h"
#ifndef PBGSOUND_H
#define PBGSOUND_H

class PBgsound : public PSound
{
    public:
        PBgsound(char * path);
        ~PBgsound();
        void Custom(); //настройка воспроизвдения
    protected:
    private:
};

#endif // PBGSOUND_H
