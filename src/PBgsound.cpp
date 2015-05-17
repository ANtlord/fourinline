#include "../header/PBgsound.h"

using namespace std;
PBgsound::PBgsound(char * path) : PSound::PSound()
{
    alcMakeContextCurrent(Context);
    if (alGetError()!=AL_NO_ERROR) {cout <<"ERROR_2"; exit(-1);}

    this->unloadfile(path);

    cout<<"result: "<<result<<endl;

    cout<<this->get_file_info();

    alGenSources(1, &Source);   // <-Генерация ресурса здесь
    this->read_stream();
    if (alGetError() != AL_NO_ERROR) {
        cout<<"\nError: "<<alutGetError()<<"\n";
        exit(-1);
    }
}

void PBgsound::Custom()
{
    //Так как фоновый звук, то параметры слушателя и источника звука
    ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };
    ALfloat SourceVel[3] = { 0.0, 0.0, 0.1 };

    ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

    alSourcef (this->Source, AL_PITCH,    1.0f     );
    alSourcef (this->Source, AL_GAIN,     0.3f     );
    alSourcefv(this->Source, AL_POSITION, SourcePos);
    alSourcefv(this->Source, AL_VELOCITY, SourceVel);
    alSourcei (this->Source, AL_LOOPING,  alLoop   );

    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);

    alSourcei(this->Source,AL_LOOPING,AL_FALSE);
}


PBgsound::~PBgsound()
{
    //dtor
}
