/*
 * usbdrive.c
 *
 *  Created on: 5 févr. 2017
 *      Author: Raphael
 */

#include "usbdrive.h"
//#include "../WAIT1.h"
#include "../USB1.h"
#include "../Tx1.h"
#include "../Rx1.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

static double PRECISION = 0.00000000000001;

char * dtoa(char *s, double n);

void USBDRIVE_Init(void){

}

uint8_t USBDRIVE_DataIsAvailable(void){

	return CDC1_GetCharsInRxBuf();
}

int USBDRIVE_ReceiveBuffer(uint8_t *buf){

    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      //WAIT1_Waitms(10);
    }

	int i;
	if (CDC1_GetCharsInRxBuf()!=0) {
		i = 0;
		while(i < sizeof(in_buffer)-1 && CDC1_GetChar(&in_buffer[i])==ERR_OK)
		{
			buf[i] = in_buffer[i];
			i++;
		}
		in_buffer[i] = '\0';
	}

	return i;
}

void USBDRIVE_SendBuffer(uint8_t *buf, uint8_t length){

	while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
		/* device not enumerated */
		//WAIT1_Waitms(10);
	}

	CDC1_SendBlock((unsigned char*)buf, length);
}

void USBDRIVE_flush(){

	CDC1_ClearRxBuffer();
}

void USBDRIVE_PrintDouble(double val){

	char s[32];

	USBDRIVE_SendBuffer((uint8_t *)dtoa(s, val), 10);

	(void)CDC1_SendString((unsigned char*)"\t");
}

///Special functions

char * dtoa(char *s, double n) {

	//From http://stackoverflow.com/questions/2302969/how-to-implement-char-ftoafloat-num-without-sprintf-library-function-i
	// handle special cases
	if (isnan(n)) {
		strcpy(s, "nan");
	} else if (isinf(n)) {
		strcpy(s, "inf");
	} else if (n == 0.0) {
		strcpy(s, "0");
	} else {
		int digit, m, m1;
		char *c = s;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp) {
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);
			m1 = m;
			m = 0;
		}
		if (m < 1.0) {
			m = 0;
		}
		// convert the number
		while (n > PRECISION || m >= 0) {
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		if (useExp) {
			// convert the exponent
			int i, j;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			} else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m-1; i<j; i++, j--) {
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}
		*(c) = '\0';
	}
	return s;
}
