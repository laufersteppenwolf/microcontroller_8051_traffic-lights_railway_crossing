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

#define SENSOR_UP P1_1
#define SENSOR_DOWN P1_0

#define SENSOR_1        P3_2
#define SENSOR_2        P3_3

#define GONG            P2_0
#define BLINK_LED       P2_1
#define BLINK_TIMING    6

#define BARRIER_DOWN    P2_6
#define BARRIER_UP      P2_7

#define RED             P2_4
#define ORANGE          P2_3
#define GREEN           P2_2

void main (void) {
unsigned int \
                counter, \
                counter2, \
                orangeCounter, \
                greenCounter;
unsigned char \
                isOrange, \
                isRed, \
                isOrangeRed, \
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
        if (SENSOR_1 == 1) {
            counter++;
            sleep2 (100);
            while (SENSOR_1 == 1) {};   //loop to count only once per click
        }
        if (SENSOR_2 == 1 && counter != 0) {
            counter--;
            sleep2 (100);
            while (SENSOR_2 == 1) {};   //loop to count only once per click
        }
        if (counter != 0) {
        wasSet = 1;
            if ((isOrange == 1 || isRed == 1) && orangeCounter == 40) {
                sleep2(100);
                counter2++;
                red(counter2);
                if (counter2 >= BLINK_TIMING) counter2 = 0;
                    isOrange = 0;
                    isRed = 1; 
            } else if (isOrange == 0) {
                orange();
                sleep2(100);
                    orangeCounter = 1;
                    isOrange = 1;            
                
            } else if (isOrange == 1 && orangeCounter <= 39) {
                sleep2(100);
                orangeCounter++;
                
            }


        }
        if (counter == 0 && wasSet == 1) {
             if (isOrangeRed == 1 && greenCounter == 40) {
                sleep2(100);
                green();        //break;
                    isOrangeRed = 0;
                    greenCounter = 0;
                    orangeCounter = 0;
             
            }else if (isRed == 1) {
                orangeRed();
                sleep2(100);
                    greenCounter = 1;
                    isOrangeRed = 1;
                    isRed = 0;
            
            } else if (isOrangeRed == 1 && greenCounter <= 39) {
                sleep2(100);
                greenCounter++;
            }
        }
        if (counter == 0) {
            BARRIER_DOWN = 0;
            if (SENSOR_UP == 1) {
                BARRIER_UP = 0;
            } else if (SENSOR_UP == 0) {
                BARRIER_UP = 1;
            }
        }
        
    }
}



void red (int counter2) {
    RED = 1;
    ORANGE = 0;
    GREEN = 0;
    BARRIER_UP = 0;
    if ( SENSOR_DOWN == 1) {
        BARRIER_DOWN = 0;
    } else if (SENSOR_DOWN == 0) {
        BARRIER_DOWN = 1;
    }
    if (BLINK_LED == 0 && counter2 >= BLINK_TIMING ) {
        BLINK_LED = 1;
        GONG = 1;
    } else if (BLINK_LED == 1 && counter2 >= BLINK_TIMING ){
        BLINK_LED = 0;
        GONG = 0;
    }
}

void sleep1 (int seconds){
unsigned int i;                         // 16-Bit-variable for time input
unsigned int c1,c2;                     // 16-Bit-variables for 1-second-pause
for (i=seconds;i!=0;i--)                // input-based pause
    for (c1=0x01E6;c1!=0;c1--)          // 1-second-pause
        for (c2=0x00FF;c2!=0;c2--);
}

void sleep2 (int milliseconds) {
unsigned int i;                         // 16-Bit-variable for time input
unsigned int c1   ;                     // 16-Bit-variable for 1-millisecond-pause
for (i=milliseconds;i!=0;i--)          // input-based pause
    for (c1=0x00C8;c1!=0;c1--);          // 1-millisecond-pause
}

void orangeRed (void) {
    RED = 1;
    ORANGE = 1;
    GREEN = 0;
    BLINK_LED = 0;                      // reset in case it was set
}

void init (void) {
    P0 = 0;              // All lights off
    P2 = 0;
    green();            // Green ligts  (00010100 bits)
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