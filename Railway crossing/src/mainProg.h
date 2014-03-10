#include <at89c5131.h> 

void sleep1 (int seconds);
void sleep2 (int milliseconds);

#define SENSOR_UP P1_1
#define SENSOR_DOWN P1_0


void init (void) {
    P0 = 0;              // All lights off
    P2_0 = 0;
    P2_1 = 0;
    P0 = 20;     // Green ligts  (00010100 bits)
}

void orange (void) {
    P0 = 10;        // 00001010 bits
}
void red (void) {
    P0 = 9;    // 00001001 bits
    P2_1 = 0;
    if ( SENSOR_DOWN == 1) {
        P2_0 = 0;
    } else if (SENSOR_DOWN == 0) {
        P2_0 = 1;
    }
}

void orangeRed (void) {
    P0 = (9 | 10);
}

void green (void) {
    P0 = 20;
}