// Deepnote interpretation in C++
//
// Author: Oliver Dressler
#include "deepnote.hpp"

#include <cmath>

#include "constants.hpp"
#include "miniaudio.h"

// Relationship between energy and loudness.
// According to EBUR 128, page 5, (2):
// https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-4-201510-I!!PDF-E.pdf
// For our purposes energy correlates with frequency.
// Gain for 20 Hz will be set to 1.0, all higher frequency will be < 1.0
// 12.3193 = loudness @ 20 Hz
static float loudnessNormalization(float frequency) {
    frequency = std::clamp(frequency, 20.0f, 2000.0f);
    return 12.3193 / (-0.691 + 4.34294 * std::log(frequency));
};

Tone::Tone(const float t_targetFrequency) {
    targetFrequency = t_targetFrequency;
    currentFrame = 0;
    currentFrequency = 200.0 + (float)(rand() % 200);
    deltaFrequency = (targetFrequency - currentFrequency) / (float)DURATIONS[1];
    phaseIndex = static_cast<float>(rand() % LUTSIZE);
};

void Tone::render(float* pOutput, const ma_uint32 frameCount,
                  const float (&lut)[LUTSIZE]) {
    for (int i = 0; i < frameCount; i++) {
        currentFrame += 1;
        if (currentFrame < TIMELINE[0]) {
        } else if (currentFrame < TIMELINE[1]) {
            currentFrequency += deltaFrequency;
        } else if (currentFrame < TIMELINE[2]) {
        } else if (currentFrame < TIMELINE[3]) {
        } else {
            continue;
        }

        int luti = int(phaseIndex);
        float fract = phaseIndex - luti;
        float interpolate = (lut[luti] + fract * lut[luti + 1]) / (1 + fract);

        // Fade out
        if (currentFrame > TIMELINE[2]) {
            interpolate *=
                1 - (currentFrame - TIMELINE[2]) / (float)DURATIONS[3];
        };
        pOutput[i] += interpolate * loudnessNormalization(currentFrequency);

        phaseIndex += LUTSIZE * currentFrequency / (float)SAMPLERATE;
        phaseIndex = std::fmod(phaseIndex, LUTSIZE);
    }
};

DeepNote::DeepNote(const int t_numTones) : numTones(t_numTones) {
    // Create all separate tones
    numTonesf = (float)t_numTones;
    for (int i = 0; i < numTones; i++) {
        tones.push_back(std::make_unique<Tone>(CHORD[i % std::size(CHORD)]));
    }

    // Create waveform LUT (blend of sine, triangle and square)
    int l2 = LUTSIZE / 2;
    int l4 = LUTSIZE / 4;
    for (int i = 0; i < LUTSIZE; i++) {
        float sine = std::sin(PI * i / (float)l2);
        float triangle = 2.0 * ((std::abs((i % l2) - l4) / (float)l4) - 0.5);
        // float square = i > l2 ? -1 : 1;
        lut[i] = std::clamp(0.9 * sine + 0.1 * triangle, -1.0, 1.0);
    }
};

void DeepNote::render(void* pOutput, const ma_uint32 frameCount) {
    float* pOutputf = (float*)pOutput;
    for (auto&& tone : tones) {
        tone->render(pOutputf, frameCount, lut);
    };
    for (int i = 0; i < frameCount; i++) {
        pOutputf[i] /= numTonesf;
    };
};