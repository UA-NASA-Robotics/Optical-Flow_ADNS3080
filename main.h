/* 
 * File:   main.h
 * Author: Scott
 *
 * Created on February 9, 2019, 1:19 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define MOSI_TRIS TRISAbits.TRISA9
#define MISO_TRIS TRISAbits.TRISA4
#define RESET_TRIS TRISAbits.TRISA1
#define NCS_TRIS TRISAbits.TRISA1

#define NCS LATBbits.LATB0
#define RESET LATAbits.LATA1

/*Registers*/
#define ADNS3080_PRODUCT_ID     0x00  //Reset: 0x00
#define ADNS3080_PIXEL_SUM      0x06
#define ADNS3080_CONFIG_BITS    0x0A
#define ADNS3080_MOTION_CLEAR   0x12
#define ADNS3080_FRAME_CAPTURE  0x13
#define ADNS3080_PIXEL_BURST    0x40
#define ADNS3080_MOTION_BURST   0x50

/*Motion_Burst registers (Recieved In Order)*/
#define ADNS3080_MOTION         0x02  //Reset: 0x00
#define ADNS3080_DX             0x03  //Reset: 0x00
#define ADNS3080_DY             0x04  //Reset: 0x00
#define ADNS3080_SQUAL          0x05  //Reset: 0x00
#define ADNS3080_SHUTTER_UPPER  0x0f  //Reset: 0x00
#define ADNS3080_SHUTTER_LOWER  0x0e  //Reset: 0x85
#define ADNS3080_MAX_PIXELS     0x07  //Reset: 0x00

/*Hardware Config*/
#define X_PIXELS       30
#define Y_PIXELS       30
#define PID_VALUE      0x0B  //Product ID


#endif	/* MAIN_H */

