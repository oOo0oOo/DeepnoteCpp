#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>

constexpr double PI = 3.14159265;
constexpr int SAMPLERATE = 48000;

// The sine wave we are playing back
constexpr int FREQUENCY = 440;  // [Hz]
constexpr int FRAMEFREQ = SAMPLERATE / FREQUENCY;
constexpr float FRAMEFREQF = FRAMEFREQ / (2 * PI);

// Keeping track of "state" between calls to data_callback
int currentState = 0;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // Render the sine wave
    float* pOutputf = (float*)pOutput;
    for (int i = 0; i < frameCount; i++){
        pOutputf[i] = sin((i + currentState) / FRAMEFREQF);
    }
    currentState = (currentState + frameCount) % FRAMEFREQ;
}

int main()
{
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;   // Set to ma_format_unknown to use the device's native format.
    config.playback.channels = 1;               // Set to 0 to use the device's native channel count.
    config.sampleRate        = SAMPLERATE;      // Set to 0 to use the device's native sample rate.
    config.dataCallback      = data_callback;   // This function will be called when miniaudio needs more data.

    ma_device device;
    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        return -1;  // Failed to initialize the device.
    }

    ma_device_start(&device);     // The device is sleeping by default so you'll need to start it manually.

    std::cout << "Wavey Sound Generator\nHit enter to stop\n";
    std::cin.ignore();

    ma_device_uninit(&device);    // This will stop the device so no need to do that manually.
    return 0;
}