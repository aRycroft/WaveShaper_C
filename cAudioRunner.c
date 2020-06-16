#include "wavWriter.h"
#include "waveShaper.h"
void test(void);

int main(void){
   test();
   return 0;
}

void test(void){
   writeToFile(generateSinWave(CHEB11, 10, 44100, 1000, 16), "Sin.wav");
}
