#include "decoder.h"
#include <stdexcept>

Decoder::Decoder(const std::filesystem::path &p)
{
    ma_result r = ma_decoder_init_file(p.string().c_str(), nullptr, &m_dec);
    if (r != MA_SUCCESS)
    {
        throw std::runtime_error("Couldnt initiate decoder!\n");
    }
}

Decoder::~Decoder()
{
    ma_decoder_uninit(&m_dec);
}

uint32_t Decoder::sampleRate() const
{
    return m_dec.outputSampleRate;
}

uint32_t Decoder::channels() const
{
    return m_dec.outputChannels;
}

uint64_t Decoder::totalFrames()
{
    ma_uint64 len = 0;
    ma_result r = ma_decoder_get_length_in_pcm_frames(&m_dec, &len);

    if (r != MA_SUCCESS)
    {
        throw std::runtime_error("could not get length");
    }
    return len;
}
