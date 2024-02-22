#ifndef SNDFX
#define SNDFX 1
#include <iostream>
#include <string>
#include <cassert>
#include <climits>
#include <cstdlib>
#include "sndfile.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

enum FormatType
{
    Int16,
    Float,
    IMA4,
    MSADPCM
};

class SoundFX
{
private:
    /* data */
    ALuint m_buffer, m_source;
    static ALCdevice *m_device;
    static ALCcontext *m_context;
    std::string m_filename;
    const char *FormatName(ALenum type);
    int InitAL(); // creates a device and context
    void CloseAL(void);

    void setupSource();
    void LoadSound();

public:
    void play(ALfloat volume = 1.0);
    SoundFX(std::string filename);
    ~SoundFX();
};

#endif