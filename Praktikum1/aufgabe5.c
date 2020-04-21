#include <stdio.h> 
#include <stdlib.h> 

void quadrat(float*); 

int main() { 
  float seitenlaenge = 3.7;
  quadrat(&seitenlaenge);
  printf("%f",seitenlaenge);
} 

void quadrat(float *zahl) { 
  *zahl=(*zahl)*(*zahl);
}
