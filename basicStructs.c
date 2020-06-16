#include "basicStructs.h"
#include <stdlib.h>

SampleBuffer* allocateBuffer(int size){
   SampleBuffer* buff;
   buff = (SampleBuffer*) malloc(sizeof(buff));
   buff->data = (StereoSample*) malloc(sizeof(StereoSample) * size);
   buff->size = size;
   return buff;
}

void freeBuffer(SampleBuffer** buff){
   SampleBuffer* temp;
   temp = *buff;
   free(temp->data);
   free(temp);
   *buff = NULL;
}
