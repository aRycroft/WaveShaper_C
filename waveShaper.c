#include <math.h>
#include "waveShaper.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

SampleBuffer* generateSinWave(WFunction shape, int duration, int samplerate, int frequency, int bitsPerSample){
   SampleBuffer* buff;
   double phase, currentPhase;
   int i;
   buff = allocateBuffer(duration * samplerate);
   phase = 2 * M_PI / samplerate * frequency;
   currentPhase = 0;
   for(i = 0; i < duration * samplerate; i++){
      double sinValue;
      currentPhase += phase;
      sinValue = sin(currentPhase);
      switch(shape){
      	case SIN3:
         	sinValue = sinValue * sinValue * sinValue;
      	break;
         case CHEB3:
            sinValue = 4 * pow(sinValue, 3) - 3 * sinValue;
         break;
         case CHEB4:
            sinValue = 8 * pow(sinValue, 4) - 8 * pow(sinValue, 2) + 1;
         break;
         case CHEB11:
            sinValue = 0.2 * (2 * pow(sinValue, 2) - 1) + 
                       + sinValue;
         break;
         default:
         break;
      }

      buff->data[i].left = sinValue * pow(2, bitsPerSample) / 2 - 1;
      buff->data[i].right = sinValue * pow(2, bitsPerSample) / 2 - 1;
   }
   return buff;
}
