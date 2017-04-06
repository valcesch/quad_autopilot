/*
*********************************************************************************************************
* CYCLIC REDUNDANCY CODE (CRC)
* DEFINITION OF THE CRC
*
* (c) Swiss Space Center 2015
*********************************************************************************************************
*
*
* Source file for CYCLIC REDUNDANCY CODE (CRC)
*
* Filename		: crc.c
* Version		: v0.1
* Created on	: 03 December 2015
* Contributors	: Benoit Denkinger
*
*********************************************************************************************************
*
* Description :
*
* This source file defines constants and functions for the CRC used in the I2C communication. It
* is taken from the ECSS-E-70-41A standard for CCSDS packets.
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												INCLUDE FILES
*********************************************************************************************************
*/

#include "crc.h"

/*
*********************************************************************************************************
*												LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												LOCAL DATA TYPES
*********************************************************************************************************
*/

unsigned int lookUpTable[256];

/*
*********************************************************************************************************
*												LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*												CRC_Init()
*
* Description 	: 	This function initiates the look-up table used by CRC_Optimized()
*
* Argument(s)	:	none.
*
* Return(s)		:	none.
*
* Caller(s)		: 	CDMS, EPS, COM, ADCS and PAYLOAD module.
*
* Note(s)		:	none.
*
*********************************************************************************************************
*/
void CRC_Init(void){

	unsigned int i, tmp = 0;

	for (i=0; i<256; i++) {

		tmp=0;

		if ((i & 1) != 0) {
			tmp = tmp ^ 0x1021;
		}

		if ((i & 2) != 0) {
			tmp=tmp ^ 0x2042;
		}

		if ((i & 4) != 0) {
			tmp=tmp ^ 0x4084;
		}

		if ((i & 8) != 0) {
			tmp=tmp ^ 0x8108;
		}

		if ((i & 16) != 0) {
			tmp=tmp ^ 0x1231;
		}

		if ((i & 32) != 0) {
			tmp=tmp ^ 0x2462;
		}

		if ((i & 64) != 0) {
			tmp=tmp ^ 0x48C4;
		}

		if ((i & 128) != 0) {
			tmp=tmp ^ 0x9188;
		}

		lookUpTable[i] = tmp;
	}

}

/*
*********************************************************************************************************
*												CRC_Serial()
*
* Description 	: 	The CRC_Optimized function generates the CRC for one byte in a serial fashion and
* 					returns the value of the new syndrome. It must be call recursively for each byte to
* 					send or for each byte received (except the last 2 bytes, which are the CRC bytes!).
*
* Argument(s)	:	data			8-bits data on which CRC is performed
* 					syndrome		syndrome's actual value
*
* Return(s)		:	syndrome		value of the new syndrome
*
* Caller(s)		: 	CDMS, EPS, COM, ADCS and PAYLOAD module.
*
* Note(s)		:
*
* 				(1)	Before calling this function for a new message, syndrome's value must be
* 					initialized to 0xFFFF!
*
*********************************************************************************************************
*/
unsigned int CRC_Serial(unsigned char data, unsigned int syndrome){

	unsigned char i;

	for (i=0; i<8; i++)
	{
		if ((data & 0x80) ^ ((syndrome & 0x8000) >> 8)) {
			syndrome = ((syndrome << 1) ^ 0x1021) & 0xFFFF;
		} else {
			syndrome = (syndrome << 1) & 0xFFFF;
		}

		data = data << 1;
	}

	return (syndrome);
}

/*
*********************************************************************************************************
*												CRC_Optimized()
*
* Description 	: 	The CRC_Optimized function generates the CRC for one byte and returns the value of
* 					the new syndrome. It must be call recursively for each byte to send or for each byte
* 					received (except the last 2 bytes, which are the CRC bytes!).
*
* Argument(s)	:	data			8-bits data on which CRC is performed
* 					syndrome		syndrome's actual value
*
* Return(s)		:	syndrome		value of the new syndrome
*
* Caller(s)		: 	CDMS, EPS, COM, ADCS and PAYLOAD module.
*
* Note(s)		:
*
*				(1)	Before calling this function for a new message, syndrome's value must be
* 					initialized to 0xFFFF!
*
* 				(2)	This function can be used instead of the CRC_Serial function.
*
* 				(3)	This function is approximately 10 times faster than the non-optimized CRC_Serial
* 					function.
*
*********************************************************************************************************
*/
unsigned int CRC_Optimized(unsigned char data, unsigned int syndrome){

	return (((syndrome << 8) & 0xFF00)^lookUpTable[(((syndrome >> 8)^data) & 0x00FF)]);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*												LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/
