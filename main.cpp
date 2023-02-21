#include <iostream>
#include <Windows.h>
#include <vector>
#include "portaudio.h"

const double SAMPLE_RATE = 44100.0;
const int FRAMES_PER_BUFFER = 64;
const float M_PI = 3.14159265;

struct Note {
    double frequency;
    bool isPlaying;
    float phase;
};

std::vector<Note> notes;

static int paCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;

    float* out = (float*)outputBuffer;

    for (unsigned int i = 0; i < framesPerBuffer; i++) {

        float sample = 0.0f;
        for (Note& note : notes) {
            if (note.isPlaying) {
                note.phase += note.frequency * (1 << 24) / SAMPLE_RATE;
                sample += sin(2.0 * M_PI * note.phase / (1 << 24));
            }
        }

        for (int channel = 0; channel < 2; channel++) {
            *out++ = sample;
        }

    }

    return paContinue;
}

int main() {

    PaStream* stream;
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError) {
        std::cout << "PortAudio Error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, paCallback, NULL);
    if (err != paNoError) {
        std::cout << "PortAudio Error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return -1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cout << "PortAudio Error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    notes = {
        {261.61, false},        // 0 C
        {277.18, false},        // 1 C#
        {293.63, false},        // 2 D
        {311.13, false},        // 3 D#
        {329.63, false},        // 4 E
        {349.23, false},        // 5 F
        {369.23, false},        // 6 F#
        {392.00, false},        // 7 G
        {415.30, false},        // 8 G#
        {440.00, false},        // 9 A
        {466.16, false},        //10 A#
        {493.88, false},        //11 B
        {523.25, false}         //12 C#
    };

    bool cKeyDown = false, fKeyDown = false, vKeyDown = false, gKeyDown = false, bKeyDown = false, nKeyDown = false, jKeyDown = false, mKeyDown = false,
        kKeyDown = false, commaKeyDown = false, lKeyDown = false, periodKeyDown = false, slashKeyDown = false;
    std::cout << "Press esc to quit\n";
    std::wcout << std::endl <<
        "|   |   | |   |   |   |   | |   | |   |   |   |" << std::endl <<
        "|   | F | | G |   |   | J | | K | | L |   |   |" << std::endl <<
        "|   |___| |___|   |   |___| |___| |___|   |   |__" << std::endl <<
        "|     |     |     |     |     |     |     |     |" << std::endl <<
        "|  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |" << std::endl <<
        "|_____|_____|_____|_____|_____|_____|_____|_____|" << std::endl << std::endl;

    while (true) {
        Sleep(100);

        //C
        if (GetAsyncKeyState('C') & 0x8000) {
            if (!cKeyDown) {
                notes[0].isPlaying = true;
                cKeyDown = true;
            }
        }
        else if (cKeyDown) {
            notes[0].isPlaying = false;

            cKeyDown = false;
        }

        //C#
        if (GetAsyncKeyState('F') & 0x8000) {
            if (!fKeyDown) {
                notes[1].isPlaying = true;

                fKeyDown = true;
            }
        }
        else if (fKeyDown) {
            notes[1].isPlaying = false;
            fKeyDown = false;
        }

        //D
        if (GetAsyncKeyState('V') & 0x8000) {
            if (!vKeyDown) {
                notes[2].isPlaying = true;
                vKeyDown = true;
            }
        }
        else if (vKeyDown) {
            notes[2].isPlaying = false;
            vKeyDown = false;
        }

        //D#
        if (GetAsyncKeyState('G') & 0x8000) {
            if (!gKeyDown) {
                notes[3].isPlaying = true;
                gKeyDown = true;
            }
        }
        else if (gKeyDown) {
            notes[3].isPlaying = false;
            gKeyDown = false;
        }

        //E
        if (GetAsyncKeyState('B') & 0x8000) {
            if (!bKeyDown) {
                notes[4].isPlaying = true;
                bKeyDown = true;
            }
        }
        else if (bKeyDown) {
            notes[4].isPlaying = false;
            bKeyDown = false;
        }

        //F
        if (GetAsyncKeyState('N') & 0x8000) {
            if (!nKeyDown) {
                notes[5].isPlaying = true;
                nKeyDown = true;
            }
        }
        else if (nKeyDown) {
            notes[5].isPlaying = false;
            nKeyDown = false;
        }

        //F#
        if (GetAsyncKeyState('J') & 0x8000) {
            if (!jKeyDown) {
                notes[6].isPlaying = true;
                jKeyDown = true;
            }
        }
        else if (jKeyDown) {
            notes[6].isPlaying = false;
            jKeyDown = false;
        }

        //G
        if (GetAsyncKeyState('M') & 0x8000) {
            if (!mKeyDown) {
                notes[7].isPlaying = true;
                mKeyDown = true;
            }
        }
        else if (mKeyDown) {
            notes[7].isPlaying = false;
            mKeyDown = false;
        }

        //G#
        if (GetAsyncKeyState('K') & 0x8000) {
            if (!kKeyDown) {
                notes[8].isPlaying = true;
                kKeyDown = true;
            }
        }
        else if (kKeyDown) {
            notes[8].isPlaying = false;
            kKeyDown = false;
        }

        //A
        if (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) {
            if (!commaKeyDown) {
                notes[9].isPlaying = true;
                commaKeyDown = true;
            }
        }
        else if (commaKeyDown) {
            notes[9].isPlaying = false;
            commaKeyDown = false;
        }

        //A#
        if (GetAsyncKeyState('L') & 0x8000) {
            if (!lKeyDown) {
                notes[10].isPlaying = true;
                lKeyDown = true;
            }
        }
        else if (lKeyDown) {
            notes[10].isPlaying = false;
            lKeyDown = false;
        }

        //B
        if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) {
            if (!periodKeyDown) {
                notes[11].isPlaying = true;
                periodKeyDown = true;
            }
        }
        else if (periodKeyDown) {
            notes[11].isPlaying = false;
            periodKeyDown = false;
        }

        //C^2
        if (GetAsyncKeyState(VK_OEM_2) & 0x8000) {
            if (!slashKeyDown) {
                notes[12].isPlaying = true;
                slashKeyDown = true;
            }
        }
        else if (slashKeyDown) {
            notes[12].isPlaying = false;
            slashKeyDown = false;
        }

        //break from loop
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
//bottom of play loop  
    }

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cout << "PortAudio Error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cout << "PortAudio Error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }
    Pa_Terminate();

    return 0;
}