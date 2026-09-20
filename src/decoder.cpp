#include "decoder.h"
#include <stdexcept>

static constexpr ma_format kFormat = ma_format_f32;
static constexpr uint32_t kChannels = 2;
static constexpr uint32_t kSampleRate = 48000;

Decoder::Decoder(const std::filesystem::path &p)
{
    ma_decoder_config config = ma_decoder_config_init(kFormat, kChannels, kSampleRate);
    ma_result r = ma_decoder_init_file(p.string().c_str(), &config, &m_dec);
    if (r != MA_SUCCESS)
    {
        throw std::runtime_error("Couldnt initiate decoder!");
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

/*read(uint64_t frameIndex, uint64_t frameCount, void *pBuffer){

}
*/