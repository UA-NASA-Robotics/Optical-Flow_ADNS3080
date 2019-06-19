//*****************************************
//********TIMER.C file code****************
//*****************************************
#include "Timer.h"
#define abs(x) ((x) > 0 ? (x) : -(x))
 
unsigned long globalTime;

unsigned long millis(void)
{
    return globalTime;
}

bool timerDone(timer_t * t)
{
    if(abs(millis() - t->lastMillis)> t->timerInterval)
    {
        t->lastMillis=millis();
        return true;
    }
    else
    {
        return false;
    }
}

void setTimerInterval(timer_t * t, unsigned long interval)
{
    t->timerInterval= interval;
}

void resetTimer(timer_t * t)
{
    t->lastMillis=millis();
}
//Call this function in your timer interrupt that fires at 1ms
void globalTimerTracker( )
{
    globalTime++;
}

//*****************************************
//**********    END OF C file  ************
//*****************************************
