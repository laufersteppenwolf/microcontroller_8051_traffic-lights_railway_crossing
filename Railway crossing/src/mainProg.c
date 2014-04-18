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

// #define SENSOR_UP P1_1       from include
// #define SENSOR_DOWN P1_0     from include

#define BLINK_LED P2_7      // FIXME: Use the correct port
#define BLINK_TIMING 6

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
        P2 = counter;
#endif        
        if (P3_2 == 1) {
            counter++;
            sleep2 (100);
            while (P3_2 == 1) {};   //loop to count only once per click
        }
        if (P3_3 == 1 && counter != 0) {
            counter--;
            sleep2 (100);
            while (P3_3 == 1) {};   //loop to count only once per click
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
            P2_0 = 0;
            if (SENSOR_UP == 1) {
                P2_1 = 0;
            } else if (SENSOR_UP == 0) {
                P2_1 = 1;
            }
        }
        
    }
}



void red (int counter2) {
    P0 = 9;    // 00001001 bits
    P2_1 = 0;
    if ( SENSOR_DOWN == 1) {
        P2_0 = 0;
    } else if (SENSOR_DOWN == 0) {
        P2_0 = 1;
    }
    if (BLINK_LED == 0 && counter2 >= BLINK_TIMING ) {
        BLINK_LED = 1;
    } else if (BLINK_LED == 1 && counter2 >= BLINK_TIMING ){
        BLINK_LED = 0;
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
    P0 = (9 | 10);
    BLINK_LED = 0;                      // reset in case it was set
}