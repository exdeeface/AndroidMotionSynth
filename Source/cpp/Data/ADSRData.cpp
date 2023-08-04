#include "ADSRData.h"

void ADSRData::updateADSR(const float gainVal, const float attack, const float decay, const float sustain, const float release) {
    gain.setGainLinear(gainVal);
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    setParameters(adsrParameters);
}
