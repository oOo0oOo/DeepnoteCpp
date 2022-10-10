#pragma once

constexpr double PI = 3.14159265;
constexpr int SAMPLERATE = 48000;
constexpr int LUTSIZE = 48000;

// If BASEFREQ = 36 Hz = D1 uses the following tones:
// D1, D2, A2, D3, A3, D4, A4, D5, A5, D6, F#5 (I prefer F#5 to F#6)
constexpr float BASEFREQ = 36.0;  // [Hz]
constexpr float CHORD[] = {BASEFREQ,          1.001 * BASEFREQ,  2 * BASEFREQ,
                           2 * BASEFREQ,      3 * BASEFREQ,      4 * BASEFREQ,
                           6 * BASEFREQ,      8 * BASEFREQ,      12 * BASEFREQ,
                           16 * BASEFREQ,     20.25 * BASEFREQ,  24 * BASEFREQ,
                           24.001 * BASEFREQ, 23.999 * BASEFREQ, 32 * BASEFREQ};

// The 4 Phases: Random, Glide, Hold, Fade out
constexpr int DURATIONS[4] = {50000, 350000, 350000, 30000};  // [SAMPLES]

constexpr int TIMELINE[4] = {
    DURATIONS[0], DURATIONS[0] + DURATIONS[1],
    DURATIONS[0] + DURATIONS[1] + DURATIONS[2],
    DURATIONS[0] + DURATIONS[1] + DURATIONS[2] + DURATIONS[3]};