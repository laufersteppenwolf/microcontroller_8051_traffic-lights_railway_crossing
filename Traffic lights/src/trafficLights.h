#include <at89c5131.h> 

/**** declarations ****/
void init (void);
void orangeRed (unsigned char lane);
void green (unsigned char lane);
void orange (unsigned char lane);
void error (void);
void allRed (void);
void foot (unsigned char lane, unsigned char green);

struct footb sleep (int seconds, struct footb *test);

