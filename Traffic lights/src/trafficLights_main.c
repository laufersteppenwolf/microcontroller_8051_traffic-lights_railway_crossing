/************************************************************************************
* Main program for traffic lights                                                   *
*                                                                                   *
* P0    red                                                                         *
* P1    orange                                                                      *
* P2    green                                                                       *
* P3    misc                                                                        *
*                                                                                   *
* If P3_7 == 1, block lane 1, as the railway crossing is closed                     *
* If (P3_0 == 1 && P3_1 == 1), pushbutton3 = 1                                      *
*                                                                                   *
*                                                                                   *
* Author: Stefan Zimmer                                                             *
************************************************************************************/

#include <at89c5131.h> 

#define DEBUGGER

#define LANE1 1
#define LANE2 2
#define LANE3 3
#define LANE4 4

#define RAILWAY_INPUT P3_7


/**** declarations ****/
void init (void);
void orangeRed (unsigned char lane);
void green (unsigned char lane);
void orange (unsigned char lane);
void error (void);
void allRed (void);
void sleep (int seconds);

/**** main program ****/
void main (void) 
{
unsigned char lane;
P0 = 0;         // make sure everything's off
P1 = 0;         // make sure everything's off
P2 = 0;         // make sure everything's off
P3_3 = 0;       // make sure everything's off
P3_4 = 0;       // make sure everything's off
P3_5 = 0;       // make sure everything's off
P3_6 = 0;       // make sure everything's off

#ifndef DEBUGGER
sleep (2);
#endif

init();

#ifndef DEBUGGER
sleep (2);
#endif


    while (1)       // loop main prog
    {   //lane = 2;
        lane++;
        orangeRed(lane);
        sleep (1);  // 4
        green(lane);
        sleep (1);  // 20
        orange(lane);
        sleep (1);  // 4
        allRed ();
        sleep (1);  // 4
        if (lane == 4 && RAILWAY_INPUT == 0) {
            lane = 0;
        } else if (lane == 4 && RAILWAY_INPUT == 1) {
            lane = 1;
        }  
    }
}

void init(void) {   // make sure everything's red

    P0 = 0xFF;
    P3_3 = 1;
    P3_4 = 1;
    P3_5 = 1;
    P3_6 = 1;
}

void orangeRed (unsigned char lane) {

switch (lane) {
    case LANE2:    
        P1_2 = 1;
        P1_3 = 1;
        break;
    case LANE3:
        P1_4 = 1;
        P1_5 = 1;
        break;
    case LANE4:
        P1_6 = 1;
        P1_7 = 1;
        break;
    case LANE1:
        P1_0 = 1;
        P1_1 = 1;
        break;
    default:
        error();
        break;
    }
}

void green (unsigned char lane) {

switch (lane) {
    case LANE2:    
        P0_2 = 0;   // turn off red and orange
        P0_3 = 0;
        P1_2 = 0;
        P1_3 = 0;
        P2_2 = 1;   // turn on green
        P2_3 = 1;
        break;
    case LANE3:
        P0_4 = 0;   // turn off red and orange
        P0_5 = 0;
        P1_4 = 0;
        P1_5 = 0;
        P2_4 = 1;   // turn on green
        P2_5 = 1;
        break;
    case LANE4:
        P0_6 = 0;   // turn off red and orange
        P0_7 = 0;
        P1_6 = 0;
        P1_7 = 0;
        P2_6 = 1;   // turn on green
        P2_7 = 1;
        break;
    case LANE1:
        P0_0 = 0;   // turn off red and orange
        P0_1 = 0;
        P1_0 = 0;
        P1_1 = 0;
        P2_0 = 1;   // turn on green
        P2_1 = 1;
        break;
    default:
        error();
        break;
    }
}

void orange (unsigned char lane) {

switch (lane) {
    case LANE2:    
        P2_2 = 0;   // turn off green
        P2_3 = 0;
        P1_2 = 1;   // turn on orange
        P1_3 = 1;
        break;
    case LANE3:
        P2_4 = 0;   // turn off green
        P2_5 = 0;
        P1_4 = 1;   // turn on orange
        P1_5 = 1;
        break;
    case LANE4:
        P2_6 = 0;   // turn off green
        P2_7 = 0;
        P1_6 = 1;   // turn on orange
        P1_7 = 1;
        break;
    case LANE1:
        P2_0 = 0;   // turn off green
        P2_1 = 0;
        P1_0 = 1;   // turn on orange
        P1_1 = 1;
        break;
    default:
        error();
        break;
    }
}

void allRed (void) {
P0 = 0xFF;
}

void error (void) {
while (1) {
    P0 = 0;
    P1 = 0;
    P2 = 0;
    sleep(1);
    P0 = 255;
    P1 = 255;
    P2 = 255;
    sleep(1);
}
}

void sleep (int seconds)
{
unsigned int i;                         // 16-Bit-variable for time input
unsigned int c1,c2;                     // 16-Bit-variables for 1-second-pause
for (i=seconds;i!=0;i--)                // input-based pause
    for (c1=0x01E7;c1!=0;c1--)          // 1-second-pause
        for (c2=0x00FF;c2!=0;c2--);
}