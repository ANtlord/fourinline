#pragma once
#ifndef PEVSOUND_H
#define PEVSOUND_H

#include "PSound.h"


class PEvsound : public PSound
{
    public:
        PEvsound(char * path);
        void Custom(const ALfloat &a, const ALfloat &b, const ALfloat &c, const ALfloat &d,  const ALfloat &e);
        void Down(ALfloat *a, ALfloat *b);
        ~PEvsound();
    protected:
    private:
};

#endif // PEVSOUND_H
