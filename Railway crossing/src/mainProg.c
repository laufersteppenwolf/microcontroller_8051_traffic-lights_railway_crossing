/************************************************************************************
* Main program for Railway crossing                                                 *
*                                                                                   *
*                                                                                   *
* Author: Stefan Zimmer                                                             *
************************************************************************************/

#include <at89c5131.h> 
#include <mainProg.h>

// #define RIDE_DEBUGGER
// #define DEBUG

#define GONG_SWITCH     P1_2
#define SENSOR_UP       P1_1
#define SENSOR_DOWN     P1_0

#define SENSOR_1        P3_2
#define SENSOR_2        P3_3

#define GONG            P2_0
#define BLINK_LED       P2_1
#define BLINK_TIMING    6

#define BARRIER_DOWN    P2_6
#define BARRIER_UP      P2_7

#define TL_OUT          P2_5

#define RED             P2_4
#define ORANGE          P1_7
#define GREEN           P2_2

void main (void) {
unsigned int    counter,        \
                counter2,       \
                orangeCounter,  \
                greenCounter;
unsigned char   isOrange,       \
                isRed,          \
                isOrangeRed,    \
                wasSet;

    init();
    isOrange = 0;
    isRed = 0;
    counter = 0;
    counter2 = 0;
    wasSet = 0;

#ifdef RIDE_DEBUGGER
P3 = 0;
#endif

    while (1) { 
#ifdef DEBUG
    P0 = counter
#endif    
        if (SENSOR_1 == 1) {                                // Count up if an axle is detected
            counter++;
            sleep2 (100);
            while (SENSOR_1 == 1) {};                       //loop to count only once per click
        }
        if (SENSOR_2 == 1 && counter != 0) {                // Count down if an axle is detected
            counter--;
            sleep2 (100);
            while (SENSOR_2 == 1) {};                       //loop to count only once per click
        }
        if (counter != 0) {
        wasSet = 1;
            if ((isOrange == 1 || isRed == 1) && orangeCounter == 40) {
                sleep2(100);
                counter2++;                                 // Count up to control the blink interval
                red(counter2);                              // Turn on RED and tell the function the value of the 2nd counter
                if (counter2 >= BLINK_TIMING) counter2 = 0; // Reset counter if max value is reached
                    isOrange = 0;
                    isRed = 1;                              // We're red now, no longer orange
            } else if (isOrange == 0) {
                orange();                                   // Turn on ORANGE
                sleep2(100);
                    orangeCounter = 1;                      // Start counting up
                    isOrange = 1;            
                
            } else if (isOrange == 1 && orangeCounter <= 39) {
                sleep2(100);
                orangeCounter++;                            // Increase orangeCounter
                
            }


        }
        if (counter == 0 && wasSet == 1) {
             if (isOrangeRed == 1 && greenCounter == 40) {
                sleep2(100);
                green();                                    // Turn on GREEN
                    isOrangeRed = 0;                        // We're green now
                    greenCounter = 0;                       // Reset counters
                    orangeCounter = 0;
             
            }else if (isRed == 1) {
                orangeRed();                                // Turn on ORANGE and RED
                sleep2(100);
                    greenCounter = 1;                       // Start counting until green
                    isOrangeRed = 1;                        // We're orange/red now
                    isRed = 0;
            
            } else if (isOrangeRed == 1 && greenCounter <= 39) {
                sleep2(100);
                greenCounter++;                             // Increase greenCounter
            }
        }
        if (counter == 0) {                                 // If there are no axles detected, keep the barrier lifted
            BARRIER_DOWN = 0;
            if (SENSOR_UP == 1) {                           // If the barrier is already up, stop the motor
                BARRIER_UP = 0;
            } else if (SENSOR_UP == 0) {                    // Keep the motor running until the barrier is up
                BARRIER_UP = 1;
            }
        }
        
    }
}



void red (int counter2) {
    RED = 1;
    ORANGE = 0;
    GREEN = 0;
    TL_OUT = 1;                                             // Tell the 2nd uC the barrier is down
    BARRIER_UP = 0;                                         // Do not lift the barrier
    if ( SENSOR_DOWN == 1) {                                // Lower the barrier if it isn't already down
        BARRIER_DOWN = 0;
    } else if (SENSOR_DOWN == 0) {
        BARRIER_DOWN = 1;
    }
    if (BLINK_LED == 0 && counter2 >= BLINK_TIMING ) {      // Let the LEDs blink in the given interval
        BLINK_LED = 1;
        if (GONG_SWITCH == 1) {                             // Do not play the gong ifwe don't want to, it's annoying :D
        GONG = 1;
        } else {
        GONG = 0;
        }
    } else if (BLINK_LED == 1 && counter2 >= BLINK_TIMING ){
        BLINK_LED = 0;
        GONG = 0;
    }
}

void sleep1 (int seconds){
unsigned int i, c1, c2;                                     // 16-Bit-variables for 1-second-pause
for (i=seconds;i!=0;i--)                                    // input-based pause
    for (c1=0x01E6;c1!=0;c1--)                              // 1-second-pause
        for (c2=0x00FF;c2!=0;c2--);
}

void sleep2 (int milliseconds) {
unsigned int i, c1;                                         // 16-Bit-variable for 1-millisecond-pause
for (i=milliseconds;i!=0;i--)                               // input-based pause
    for (c1=0x00C8;c1!=0;c1--);                             // 1-millisecond-pause
}

void orangeRed (void) {
    RED = 1;
    ORANGE = 1;
    GREEN = 0;
    BLINK_LED = 0;                                          // reset in case it was set
    TL_OUT = 0;                                             // We can use this TL-lane again as the barriers are lifting
}

void init (void) {
    P0 = 0;                                                 // All lights off
    P2 = 0;
    green();                                                // Turn on GREEN
    TL_OUT = 0;                                             // Reset in case it was set
}

void orange (void) {
    RED = 0;
    ORANGE = 1;
    GREEN = 0;
}

void green (void) {
    RED = 0;
    ORANGE = 0;
    GREEN = 1;
}