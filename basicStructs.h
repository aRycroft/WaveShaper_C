#include <inttypes.h>
#ifndef STRUCTS_H
#define STRUCTS_H 

typedef enum WFunction{SIN, SIN3, CHEB3, CHEB4, CHEB7, CHEB11} WFunction;

typedef struct stereosample{
   int16_t left;
   int16_t right;
} StereoSample;

typedef struct samplebuffer{
   StereoSample* data;
   int size;
} SampleBuffer;

SampleBuffer* allocateBuffer(int size);
void freeBuffer(SampleBuffer** buff);
#endif
