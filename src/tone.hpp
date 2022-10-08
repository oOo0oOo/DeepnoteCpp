// Tone class for cinematic intro
//
// Author: Oliver Dressler

#include <chrono>
#include <random>
#include <vector>

#include "constants.hpp"

float noteToFreq(float note) {
    return std::pow(2.0, (note - 69.0) / 12.0) *
           440.0;  // A4 (note 69) is at 440 Hz
};

class Tone {
    float targetFrequency;
    unsigned int randomDuration;
    unsigned int riseDuration;
    unsigned int holdDuration;
    unsigned long currentState;
    float currentFrequency;
    float deltaFrequency;

   public:
    Tone(const float t_targetFrequency, const unsigned int t_randomDuration,
         const unsigned int t_riseDuration, const unsigned int t_holdDuration) {
        targetFrequency = t_targetFrequency;
        randomDuration = t_randomDuration;
        riseDuration = t_riseDuration;
        holdDuration = t_holdDuration;
        currentState = 0;
        currentFrequency = 200.0 + (rand() % 200);
        deltaFrequency =
            (float)(targetFrequency - currentFrequency) / (riseDuration);
    };

    void render(float* pOutput, const ma_uint32 frameCount) {
        for (int i = 0; i < frameCount; i++) {
            if (currentState >= randomDuration &&
                currentState < randomDuration + riseDuration) {
                currentFrequency += deltaFrequency;
            };
            float freq = SAMPLERATE / (currentFrequency * 2 * PI);
            // double freq = SAMPLERATE / (targetFrequency * 2 * PI);

            pOutput[i] += sin(currentState / freq);
            currentState += 1;
        }
    };
};

class THX {
    int numTones;
    float numTonesf;
    std::vector<std::unique_ptr<Tone>> tones;

   public:
    THX(const int t_numTones) : numTones(t_numTones) {
        // Seed random (this feel very much like the wrong place...)
        auto t = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count();
        srand(t);

        // std::vector<float> notes = {12, 24, 36, 48};
        // std::for_each(notes.begin(), notes.end(), &noteToFreq);
        std::vector<float> notes = {100, 1000};

        // Create various tones
        numTonesf = (float)t_numTones;
        for (int i = 0; i < numTones; i++) {
            tones.push_back(std::make_unique<Tone>(notes[i % notes.size()], 0,
                                                   150000, 150000));
        }
    };

    void render(void* pOutput, const ma_uint32 frameCount) {
        float* pOutputf = (float*)pOutput;
        for (auto&& tone : tones) {
            tone->render(pOutputf, frameCount);
        };
        for (int i = 0; i < frameCount; i++) {
            pOutputf[i] /= numTonesf;
        };
    };
};

// Tone::Tone(float t_targetFrequency, unsigned int t_randomDuration,
//            unsigned int t_riseDuration, unsigned int t_holdDuration){};

// void Tone::render(float* pOutput, const ma_uint32 frameCount){};

// THX::THX(int t_numTones){};
// void THX::render(void* pOutput, const ma_uint32 frameCount){};