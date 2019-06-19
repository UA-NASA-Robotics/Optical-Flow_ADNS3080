/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33EP512GP504
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "mcc_generated_files/system.h"
#include "Timer.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/spi1.h"
#include "main.h"

uint8_t data = 0x50;

    /*Data Variables */
int totalX = 0; int totalY = 0;
int convert_from_twos(uint8_t byte);

/*
            Main application
 */

struct MB burstReceive;
uint8_t dx, dy;

int main(void)
{
    //Initialize Timer
    TMR1_Start();
    timer_t Timer1;
    
    MOSI_TRIS = 0; //MOSI as output
    MISO_TRIS = 1; //MISO as input
    TRISAbits.TRISA2 = 0;
    RESET_TRIS = 0;//Reset Pin as Output
    NCS_TRIS = 0;//Enable Pin as output
    
    //Init System
    SYSTEM_Initialize();
    
    ANSELA = 0x00;
    
    NCS = 1;  //Set NCS High
    RESET = 1;  //Set Pin Reset High to activate
    
    //Wait at least 35ms
    resetTimer(&Timer1);
    setTimerInterval(&Timer1, 10);
    while(!timerDone(&Timer1));
    
    //Reset Variables
    totalX = totalY = 0;
    int xIn = 0, yIn = 0, i = 0;
    long avgX = 0, avgY = 0;
    dx = dy = 0;
    
    RESET = 0;//Set Pin Reset Low according to datasheet
    
    ANSELA = 0x00;
    
    //Wait for sensor to wake back up
    resetTimer(&Timer1);
    setTimerInterval(&Timer1, 70);
    while(!timerDone(&Timer1));
    
    NCS = 0; //Set NCS Low
    
    SPI1_Transmit(ADNS3080_CONFIG_BITS | 0x80); //Config Address
    SPI1_Transmit(0x19); //Config settings
    
    //Wait for at least 1ms before starting
    resetTimer(&Timer1);
    setTimerInterval(&Timer1, 25);
    while(!timerDone(&Timer1));
    
    NCS = 1;

    //Get natural offset
    for (i = 0; i < 20; i++)
    {
        NCS = 0;
        SPI1_Motion(&data, &dx, &dy);
        NCS = 1;
        avgX += dx;
        avgY += dy;
    }
    avgX = avgX/i;
    avgY = avgY/i;
    
    while (true)
    {   
        dx = dy = 1;
               
        NCS = 0;  
        SPI1_Motion(&data, &dx, &dy);
        NCS = 1;

        //Accumulate totals
        totalX = totalX + convert_from_twos(dx - avgX);
        totalY = totalY + convert_from_twos(dy - avgY);
        if(totalX != 0)
        {
            xIn = totalX/1600;
        }
        if(totalY != 0)
        {
            yIn = totalY/1600;
        }
        
        NCS = 0;
        SPI1_Transmit(dx);
        for(i = 0; i<750;i++);
        SPI1_Transmit(dy);
        for(i = 0; i<750;i++);
        NCS = 1;
        
        for(i = 0; i<20000;i++);
    }
    return 1; 
}

int convert_from_twos(uint8_t x)
{
  if(x > 127)
  {
    return 0xff00 + x;
  }
  else
  {
    return x;
  }
}

/**
 End of File
*/

