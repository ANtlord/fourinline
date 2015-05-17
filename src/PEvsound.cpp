#include "../header/PEvsound.h"
using namespace std;


PEvsound::PEvsound(char * path) : PSound::PSound()
{
    alcMakeContextCurrent(Context);
    if (alGetError()!=AL_NO_ERROR) {cout <<"ERROR_2"; exit(-1);}

    this->unloadfile(path);

    cout<<"result: "<<result<<endl;

    cout<<"Sound's format: "<<this->get_file_info();

    alGenSources(1, &Source);   // <- Generate source here
    this->read_stream();        // <- read first segment of unpacked file
    if (alGetError() != AL_NO_ERROR) {
        cout<<"\nError: "<<alutGetError()<<"\n"; exit(-1);
    }

}

void PEvsound::Custom(const ALfloat &a, const ALfloat &b, const ALfloat &c, const ALfloat &d,  const ALfloat &e){
    // a - SourcePos
    // b - SourceVel
    // c - ListenerPos
    // d - ListenerVel
//     e - ListenerOri
    alSourcef (this->Source, AL_PITCH,    1.0f     );
    alSourcef (this->Source, AL_GAIN,     0.3f     );
    alSourcefv(this->Source, AL_POSITION, &a);
    alSourcefv(this->Source, AL_VELOCITY, &b);
    alSourcei (this->Source, AL_LOOPING,  alLoop   );

    alListenerfv(AL_POSITION,    &c);
    alListenerfv(AL_VELOCITY,    &d);
    alListenerfv(AL_ORIENTATION, &e);

    alSourcei(this->Source,AL_LOOPING,AL_FALSE);
}

void PEvsound::Down(ALfloat *a, ALfloat *b){

}

PEvsound::~PEvsound()
{
    //dtor
}
