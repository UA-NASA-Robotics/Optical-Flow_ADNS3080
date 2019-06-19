/* 
 * File:   main.cpp
 * Author: Scott Grisso
 *
 * Created on February 9, 2019, 12:40 PM
 */

#include <cstdlib>
#include <stdlib.h>
#include "main.h"
using namespace std;

#define X_CAN_SEND_ADD;
#define X_CAN_REC_ADD;
#define Y_CAN_SEND_ADD;
#define Y_CAN_REC_ADD;

#define X_SPI_SEND_ADD;
#define X_SPI_REC_ADD;
#define Y_SPI_SEND_ADD;
#define Y_SPI_REC_ADD;

#define WAIT_TIME; 
#define RESET_CALL;

//Distance Variables
int totalX = 0;
int totalY = 0;

/*
 *  Timer 2 Interrupt
 *  IN: N/A
 *  OUT: N/A
 *      On trigger, send current movement data to CAN bus
 */
void _ISR _T2Interrupt()
{
    if(!sendData(totalX, X_SPI_SEND_ADD))
        throw error;
    if(!sendData(totalY, Y_SPI_SEND_ADD))
        throw error; 
        
    _T2IF = 0;
}

/*
 * Main Loop 
 * IN: N/A
 * OUT: N/A
 *      Main Data Acquisition Loop
 */
int main() {
    /*-----Initialization Block-----*/
    /*Data Variables */
    int sumX = 0;      int sumY = 0;
    
    /*Get in data from CAN*/
    //int listenCommand = 0;
    
    /*Serial Select Pin*/
    PORTAbits.RA0 = 1;
    PORTAbits.RA0 = 0;
    PORTAbits.RA0 = 1;

    //Reset the Reset Flag
    bool resetFlag = false; 
    
    /*Timer 1 (for ms_delay)*/
    T1CON = 0x8030;
    /*Timer 2 (for interrupt)*/
    _T2IP = 4;      //Default Priority level
    TMR1 = 0;       //Clear Timer 2
    PR1 = 24999;    //Set the Period Register
    T2CON = 0x8020; //Enable internal clock at 1:64 pre-scaler
    _T2IF = 0;      //Clear interrupt
    _T2IE = 1;      //Enable interrupt
    
    /*SPI init*/
    SPI1Init();
    
    /*-----END-----*/
    
    /*-----Main Loop-----*/
    while(1)
    {
        /*Listen for Reset Call*/
        //listenCommand = listenForCommand();
        //if(listenCommand == RESET_CALL)
        //{
        //    totalX = totalY = 0;
        //    listenCommand = 0;
        //}
        
        /*Communicate to ADNS3080*/
            //Call to ADNS3080 Placeholder
            /*Receive data for X and Y coordinates*/
            /*If we get invalid data, throw an error*/
        try
        {
            PORTAbits.RA0 = 0;
            sumX = readSPI();
            //if(Sum_X != VALID)
            //    throw error;
            sumY = readSPI();
            //if(Sum_Y != VALID)
            //    throw error;
            totalX = totalX + sumX;
            totalY = totalY + sumY;

        }
        catch(error e)
        {
            //DISPLAY error e
        }
    }
    return 0;
}

/*
 * sendData
 * IN: int Total //Data to send
 *     int Address //Where to send to 
 * OUT: bool //Success or failure to send
 */
bool sendData(int total, int address)
{
    //Send data over CAN bus to Master Card
    
    return true;
}

/*
 * receiveData
 * IN: int Address //Where to listen to 
 * OUT: int //Data received
 */
int receiveData(int address)
{
    /*SPI*/ 
    int Data;
    /*Call for Data*/
    PORTAbits.RA0 = 0;          //Set SS low to transmit
    readSPI1();
    readSPI1();
    
    return Data;
}

/*
 * listenForCommand
 * IN: N/A
 * OUT: int //Command received
 */
int listenForCommand()
{
    int Command;
    //Check if there is a waiting command
    //PROBABLY SOME OTHER WAY TO DO THIS, BUT WILL KEEP THIS A PSEUDO PLACEHOLDER
    return Command;
}

void ms_delay(int N)
{
    long j;
    for(j = 0; j < N; j++)
    {
        TMR1 = 0;
        while(TMR1 < 63)
        {}
    }
}

void SPI1Init()
{
    SPI1CON1 = 0x0120;
    SPI1STAT = 0x8000;
} //SPI1Init

unsigned char writeSPI1(unsigned char j)
{
    while(SPI1STATbits.SPITBF);
    SPI1BUF = j;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}// writeSPI1