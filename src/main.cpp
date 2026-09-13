#include <iostream>
#include "miniaudio.h"
#include "decoder.h"

using std::cout;

int main()
{

       Decoder d("test.wav");
    cout << d.sampleRate() << " Hz, "
         << d.channels() << " ch, "
         << d.totalFrames() << " frames\n";
}