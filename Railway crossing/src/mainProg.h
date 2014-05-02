#include <at89c5131.h> 

void sleep1 (int seconds);
void sleep2 (int milliseconds);

#define SENSOR_UP P1_1
#define SENSOR_DOWN P1_0

void red (int counter2);
void orangeRed (void);


void init (void) {
    P0 = 0;              // All lights off
    P2 = 0;
    P0 = 20;     // Green ligts  (00010100 bits)
}

void orange (void) {
    P0 = 10;        // 00001010 bits
}

void green (void) {
    P0 = 20;
}