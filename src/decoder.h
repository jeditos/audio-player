#pragma once
#include <filesystem>
#include "miniaudio.h"

class Decoder
{
public:
    Decoder(const std::filesystem::path &p);

    Decoder(const Decoder &) = delete;
    Decoder &operator=(const Decoder &) = delete;

    uint32_t sampleRate() const;
    uint32_t channels() const;
    uint64_t totalFrames();

    ~Decoder();

private:
    ma_decoder m_dec;
};