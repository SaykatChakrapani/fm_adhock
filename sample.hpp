#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <cstdint>

class Sample
{
    public:
        Sample(uint8_t *data, unsigned channels, unsigned bitsPerChannel);
        float GetMonoValue() const;
    protected:
        float value;
};

#endif // SAMPLE_HPP
