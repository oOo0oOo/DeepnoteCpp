#define MINIAUDIO_IMPLEMENTATION

#include <chrono>
#include <iostream>
#include <random>

#include "constants.hpp"
#include "deepnote.hpp"
#include "miniaudio.h"

int main() {
    // Seed random generator
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch())
                 .count();
    srand(t);

    static DeepNote deepnote(30);

    auto callback = [](ma_device* pDevice, void* pOutput, const void* pInput,
                       ma_uint32 frameCount) {
        deepnote.render(pOutput, frameCount);
    };

    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format = ma_format_f32;
    config.playback.channels = 1;
    config.sampleRate = SAMPLERATE;
    config.dataCallback = callback;

    ma_device device;
    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        return -1;
    };

    ma_device_start(&device);

    std::cout << "Realtime deep note generator\nHit enter to stop\n";
    std::cin.ignore();

    ma_device_uninit(&device);
    return 0;
}