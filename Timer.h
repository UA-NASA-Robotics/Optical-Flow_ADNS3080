//*****************************************
//********TIMER.H file code****************
//*****************************************
#ifndef TIMER_h
#define TIMER_h
#include <stdbool.h>

 typedef struct{
        unsigned long timerInterval;
        unsigned long lastMillis;
    }timer_t;
    
bool timerDone(timer_t * t);
void setTimerInterval(timer_t * t, unsigned long interval);
void resetTimer(timer_t * t);
void globalTimerTracker( );
unsigned long millis(void);
//*****************************************
//**********    END OF H file  ************
//*****************************************

#endif