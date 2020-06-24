/*
  ==============================================================================

    tunings.h
    Created: 18 Jun 2020 2:38:07pm
    Author:  Sebastian

  ==============================================================================
*/

#ifndef TUNINGS_H_
#define TUNINGS_H_
#include "stdint.h"
#define NUM_TUNINGS 63

extern float centsDeviation[12];
extern const float tuningPresets[NUM_TUNINGS][12];
extern uint32_t currentTuning;
extern uint8_t keyCenter;
extern const char tuningNames[NUM_TUNINGS][13];


#endif /* TUNINGS_H_ */
