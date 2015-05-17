#pragma once
#ifndef PSOUND_H
#define PSOUND_H
#include <al.h>
#include <alc.h>
//#include <AL/alext.h>
#include <AL/alut.h>
#include <efx.h>

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include <vector>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;


class PSound
{
    public:
        PSound();
        void Play();
        void Pause();
        void Stop();
        virtual ~PSound();

        vorbis_info *vorbisInfo;
        vorbis_comment *vorbisComment;
    protected:
        const ALCchar * defaultDeviceName;  //для определения устровйства по умолчанию
        // эти поля общие для всех классов, потому что все объекты звуков должны использовать только одно устройство
        static ALCdevice * Device;          //для устройства
        static ALCcontext * Context;        //для контекста устройства

        ALuint Source;          //Ресурс буфера
        std::vector<ALuint> Buffer; //

        ALboolean alLoop;       //для параметра способа воспроизвдения (петли)

        //поля для воспроизвдения потока
        OggVorbis_File * oggStream;
        ifstream OggFile;
        int result; //параметр возвращающий в дальнейшем количество считанных байт их потока. Если вернет отрицательное, то ошибка потока, если 0, то поток закончился
        FILE *file;
        ALenum format;     // internal format
        int file_size;
        int PCM_file_size; // размер файла распакованного в поток потока

        void unloadfile(char * path);
        void get_file_size();
        char *get_file_info();
        void read_stream();
    private:
        const int BLOCK_SIZE; //этот параметр должен настраиваться в настройках приложения, но так как это модуль, конечным пользователем которого является программист, настройка в конструкторе
};
#endif // PSOUND_H
