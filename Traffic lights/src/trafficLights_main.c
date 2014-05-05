/************************************************************************************
* Main program for traffic lights                                                   *
*                                                                                   *
* P0    red                                                                         *
* P1    orange                                                                      *
* P2    green                                                                       *
* P3    misc                                                                        *
*                                                                                   *
* If P3_7 == 1, block lane 1, as the railway crossing is closed                     *
* If (P3_0 == 1 && P3_1 == 1), pushbutton4 = 1                                      *
*                                                                                   *
*                                                                                   *
* Author: Stefan Zimmer                                                             *
************************************************************************************/

#include <at89c5131.h> 
#include <trafficLights.h>

// #define DEBUGGER

//#define IGNORE_RAILWAY
//#define IGNORE_WALKER_INPUT

#define LANE1 2
#define LANE2 3
#define LANE3 4
#define LANE4 1

#define FOOT1 P3_3
#define FOOT2 P3_4
#define FOOT3 P3_5
#define FOOT4 P3_6

#define RAILWAY_INPUT P3_7

struct footb 
{   char *w1;
    char *w2;
    char *w3;
    char *w4;
};

struct footb get_pb(struct footb *test);

/**** main program ****/
void main (void) 
{
struct footb *test = {0, 0, 0, 0} ;

unsigned char lane;
P0 = 0;         // make sure everything's off
P1 = 0;         // make sure everything's off
P2 = 0;         // make sure everything's off

#ifndef DEBUGGER
*test = sleep (2, &test);
#endif

init();
*test = get_pb(&test);

FOOT1 = 0;
FOOT2 = 0;
FOOT3 = 0;
FOOT4 = 0;

#ifndef DEBUGGER
*test = sleep (2, &test);
#endif

#ifdef IGNORE_RAILWAY
RAILWAY_INPUT = 0;
#endif

    while (1)               // loop main prog
    {   

#ifdef IGNORE_WALKER_INPUT
        *test->w1 = 1;
        *test->w2 = 1;
        *test->w3 = 1;
        *test->w4 = 1;
#endif    
        lane++;
        *test = sleep (1, &test);
        orangeRed(lane);
        *test = sleep (1, &test);   // 4
        green(lane);
        *test = sleep (1, &test);   // 20
        orange(lane);
        *test = sleep (1, &test);   // 4
        allRed ();
        *test = sleep (1, &test);   // 4 
        if ( ( lane == 1 && *test->w1 == 1) || ( lane == 2 && *test->w2 == 1) || ( lane == 3 && *test->w3 == 1) || ( lane == 4 && *test->w4 == 1) ) {
            foot (lane, 1);
            *test = sleep (1, &test);   // 4
            foot (lane, 0);
            *test = sleep (1, &test);
            if (lane == 1) *test->w1 = 0;
            else if (lane == 2) *test->w2 = 0;
            else if (lane == 3) *test->w3 = 0;
            else if (lane == 4) *test->w4 = 0; 
            }
        if (lane == 4 && RAILWAY_INPUT == 0) {
            lane = 0;
        } else if (lane == 4 && RAILWAY_INPUT == 1) {   
            lane = 1;
        }  
    }
}

struct footb get_pb(struct footb *test) // get pushbuttons
{   
    if (P3_0 == 1 && P3_1 == 0) *test->w1 = 1;
    if (P3_1 == 1 && P3_0 == 0) *test->w2 = 1;
    if (P3_2 == 1) *test->w3 = 1;
    if (P3_0 == 1 && P3_1 == 1) *test->w4 = 1;
    return *test;
}


void init(void)    // make sure everything's red
{
    P0 = 0xFF;
    P3_3 = 0;
    P3_4 = 0;
    P3_5 = 0;
    P3_6 = 0;
}

void orangeRed (unsigned char lane) 
{
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

void green (unsigned char lane) 
{
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

void orange (unsigned char lane) 
{
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

void foot (unsigned char lane, unsigned char green)
{
    switch (lane) {
        case LANE2: 
            if ( green == 1) FOOT2 = 1;
            else FOOT2 = 0;
            break;
        case LANE3:
            if ( green == 1) FOOT3 = 1;
            else FOOT3 = 0;            
            break;
        case LANE4:
            if ( green == 1) FOOT4 = 1;
            else FOOT4 = 0;            
            break;
        case LANE1:
            if ( green == 1) FOOT1 = 1;
            else FOOT1 = 0;            
            break;
        default:
            error();
            break;
    }
}

void allRed (void) 
{
    P0 = 0xFF;
    P1 = 0;
}

void error (void) 
{
    while (1) {
        P0 = 0;
        P1 = 0;
        P2 = 0;
        sleep(1, 0);
        P0 = 255;
        P1 = 255;
        P2 = 255;
        sleep(1, 0);
    }
}

struct footb sleep (int seconds, struct footb *test) 
{
    unsigned int i;                         // 16-Bit-variable for time input
    unsigned int c1,c2;                     // 16-Bit-variables for 1-second-pause
    for (i=seconds;i!=0;i--)                // input-based pause
        for (c1=0x01E7;c1!=0;c1--){          // 1-second-pause
            for (c2=0x00FF;c2!=0;c2--);
            get_pb(&test);
        }
    return *test;
}