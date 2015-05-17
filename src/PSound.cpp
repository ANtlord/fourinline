#include "../header/PSound.h"
#include <wx/string.h>
#include <wx/msgdlg.h>

using namespace std;

ALCdevice * PSound::Device=NULL;
ALCcontext * PSound::Context=NULL;

PSound::PSound() : BLOCK_SIZE(3340032)
{
    defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    Device = alcOpenDevice(defaultDeviceName); //открываем устройство
    if (Device != NULL) Context=alcCreateContext(Device, NULL); //Если устройство открылось создаем контекст

    this->vorbisInfo = NULL;
    this->file = NULL;
    this->vorbisComment = NULL;
    oggStream = new OggVorbis_File;
}


size_t ReadOgg(void *ptr, size_t size, size_t nmemb, void *datasource)
{
  istream *File = reinterpret_cast<istream*>(datasource);
  File->read((char *)ptr, size * nmemb);
  return File->gcount();
}

int SeekOgg(void *datasource, ogg_int64_t offset, int whence)
{
  istream *File = reinterpret_cast<istream*>(datasource);
  ios_base::seekdir Dir;
  File->clear();
  switch (whence)
  {
    case SEEK_SET: Dir = ios::beg;  break;
    case SEEK_CUR: Dir = ios::cur;  break;
    case SEEK_END: Dir = ios::end;  break;
    default: return -1;
  }
  File->seekg((streamoff)offset, Dir);
  return (File->fail() ? -1 : 0);
}

long TellOgg(void *datasource)
{
  istream *File = reinterpret_cast<istream*>(datasource);
  return File->tellg();
}

int CloseOgg(void *datasource)
{
  return 0;
}

void PSound::unloadfile(char *path)
{

//     Структура с функциями обратного вызова.
    ov_callbacks  cb;

//     Заполняем структуру cb
    cb.close_func  = CloseOgg;
    cb.read_func  = ReadOgg;
    cb.seek_func  = SeekOgg;
    cb.tell_func  = TellOgg;

//    this->file = fopen(path, "rb");
//    get_file_size();

//    string filename =
    OggFile.open(path, ios_base::in | ios_base::binary);
    if (ov_open_callbacks(&OggFile, this->oggStream, NULL, -1, cb) < 0)
    {
//         Если ошибка, то открываемый файл не является OGG
        exit(-1);
    }

//    try {
//ov_callbacks a;
//if (ov_open_callbacks(this->file, this->oggStream, NULL, -1, a) < 0)

//        this->result = ov_open(this->file, this->oggStream, NULL, 0);
//    } catch (bad_alloc&) {
//        cout<<"123";
//    }

    cout<<"File size: "<<this->file_size<<endl;
    this->PCM_file_size = ov_pcm_total(this->oggStream, -1)*4;
    cout <<"Stream's size: "<<PCM_file_size<<endl<<endl;
}


void PSound::get_file_size(){
    fseek(this->file, 0, SEEK_END);
    this->file_size = ftell(this->file);
    fseek(this->file, 0, SEEK_SET);
}

char *PSound::get_file_info(){
    this->vorbisInfo = ov_info(this->oggStream, -1);
    this->vorbisComment = ov_comment(this->oggStream, -1);

    if(vorbisInfo->channels == 1){
        this->format = AL_FORMAT_MONO16;
        return "AL_FORMAT_MONO16\n";
    }
    else{
        this->format = AL_FORMAT_STEREO16;
        return "AL_FORMAT_STEREO16\n";
    }
}

void PSound::read_stream(){

    bool p = false;
    int size=0, section;
    char* data = new char[this->BLOCK_SIZE];

    while(size<BLOCK_SIZE && p != true){
        this->result = ov_read(this->oggStream, data+size, BLOCK_SIZE-size, 0, 2, 1, & section);
        if (this->result < 0){
            p=true;
        }
        else if (this->result == 0)
            p=true;
        else{
            size+=this->result;
        }
    }

    this->Buffer.push_back(NULL);
    alGenBuffers(1, &this->Buffer.back());

    alBufferData(this->Buffer.back(), this->format, data, size, vorbisInfo->rate);
    if (alGetError() != AL_NO_ERROR) {cout<<"\nError: "<<alutGetError()<<"\n"; exit(-1);}
    alSourceQueueBuffers( this->Source, 1, &this->Buffer.back() );
    delete[] data;
}

void PSound::Play()
{
    alSourcePlay(this->Source);
    for(int i=0; i<(this->PCM_file_size / this->BLOCK_SIZE); ++i)
        this->read_stream();
}

void PSound::Pause()
{
    alSourcePause(this->Source);
}

void PSound::Stop()
{
    alSourceStop(this->Source);
}

PSound::~PSound()
{
    alDeleteSources(1, &this->Source);
    for(int i=0; i<this->Buffer.size(); ++i){
        alDeleteBuffers(1, &this->Buffer[i]);
    }
    ov_clear(this->oggStream);
    delete oggStream;
}

