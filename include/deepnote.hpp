// Deepnote interpretation in C++
//
// Author: Oliver Dressler
#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include "constants.hpp"
#include "miniaudio.h"

static float loudnessNormalization(float frequency);

class Tone {
    float targetFrequency;
    unsigned long currentFrame;
    float currentFrequency;
    float deltaFrequency;
    float phaseIndex;

   public:
    Tone(const float t_targetFrequency);
    void render(float* pOutput, const ma_uint32 frameCount,
                const float (&lut)[LUTSIZE]);
};

class DeepNote {
    int numTones;
    float numTonesf;
    std::vector<std::unique_ptr<Tone>> tones;
    float lut[LUTSIZE];

   public:
    DeepNote(const int t_numTones);
    void render(void* pOutput, const ma_uint32 frameCount);
};