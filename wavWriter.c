#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

#include "wavWriter.h"

typedef struct wavHeader {
   char chunkId[4];
   int32_t chunkSize;
   char format[4];

   char subchunk1ID[4];
   int32_t subchunk1Size;
   int16_t audioFormat;
   int16_t numChannels;
   int32_t sampleRate;
   int32_t byteRate;
   int16_t blockAlign;
   int16_t bitsPerSample;

   char subchunk2ID[4];
   int32_t subchunk2Size;
} WavHeader;

WavHeader* fillHeader(int durationInSeconds, int samplerate);
StereoSample* allocateSampleData(int durationInSeconds, int samplerate);

int generateZeroData(StereoSample* buffer, int frameSize);
int generateSinData(StereoSample* buffer, int frameSize, int samplerate, int frequency);
int generateRectData(StereoSample* buffer, int frameSize, int samplerate, int frequency);

#define SAMPLERATE 44100
#define NUMCHANNELS 2
#define DURATION_S 10
#define SUBCHUNK1SIZE 16 /*FOR PCM*/
#define BITS_PER_SAMPLE 16
#define AUDIO_FORMAT 1 /*FOR PCM*/


int writeToFile(SampleBuffer* buffer, char* fileName){
   FILE* writeBuffer;
   WavHeader* header;
   int frameSize;

   frameSize = buffer->size;
   header = fillHeader(frameSize / SAMPLERATE, SAMPLERATE);

   writeBuffer = fopen(fileName, "w");
   fwrite(header, sizeof(WavHeader), 1, writeBuffer);
   fwrite(buffer->data, sizeof(StereoSample), frameSize, writeBuffer);
   fclose(writeBuffer);
   
   free(header);
   freeBuffer(&buffer);
  
   return 1;
}


WavHeader* fillHeader(int durationInSeconds, int samplerate){
   WavHeader* header = (WavHeader*) malloc(sizeof(WavHeader));
   int32_t subchunk2size;
   memcpy(header->chunkId, "RIFF", 4 * sizeof(char));
   subchunk2size = (samplerate * durationInSeconds) * NUMCHANNELS * (BITS_PER_SAMPLE / 8);
   header->chunkSize = 4 + 8 + SUBCHUNK1SIZE + 8 + subchunk2size; 
   memcpy(header->format, "WAVE", 4 * sizeof(char));
   memcpy(header->subchunk1ID, "fmt ", 4 * sizeof(char));
   header->subchunk1Size = SUBCHUNK1SIZE;
   header->audioFormat = AUDIO_FORMAT;
   header->numChannels = NUMCHANNELS;
   header->sampleRate = samplerate;
   header->byteRate = samplerate * NUMCHANNELS * BITS_PER_SAMPLE / 8;
   header->blockAlign = NUMCHANNELS * BITS_PER_SAMPLE / 8;
   header->bitsPerSample = BITS_PER_SAMPLE;
   memcpy(header->subchunk2ID, "data", 4 * sizeof(char));
   header->subchunk2Size = subchunk2size;
   return header;
}

StereoSample* allocateSampleData(int durationInSeconds, int samplerate){ 
   StereoSample* buff;
   int frameLength;
   frameLength = durationInSeconds * samplerate;
   buff = (StereoSample*)malloc(sizeof(StereoSample) * frameLength);
   return buff;
}

int generateZeroData(StereoSample* buffer, int frameSize){
   int i;
   for(i = 0; i < frameSize; i++){
      buffer[i].left = 0;
      buffer[i].right = 0;
   }
   return 1;
}

/*int generateSinData(StereoSample* buffer, int frameSize, int samplerate, int frequency){
   int i;
   double phase, currentPhase;
   phase = 2 * M_PI / samplerate * frequency;
   currentPhase = 0;
   for(i = 0; i < frameSize; i++){
      double sinValue;
      currentPhase += phase;
      sinValue = sin(currentPhase); 
      buffer[i].left = (int16_t)((sinValue * pow(2, BITS_PER_SAMPLE) / 2 - 1) * 0.7);
      buffer[i].right = (int16_t)((sinValue * pow(2, BITS_PER_SAMPLE) / 2 - 1) * 0.7);
   }
   return 1;
}*/

