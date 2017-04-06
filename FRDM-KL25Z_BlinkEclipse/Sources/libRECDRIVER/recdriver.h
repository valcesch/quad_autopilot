/*
 * recdriver.h
 *
 *  Created on: 5 févr. 2017
 *      Author: Raphael
 */

#ifndef RECDRIVER_H_
#define RECDRIVER_H_

#include <stdint.h>
#include "../PE_Types.h"

#define REC_YAW			0
#define REC_PITCH		3
#define REC_ROLL		2
#define REC_GAS			1
#define REC_AUX1		4
#define REC_AUX2		5
#define RECDRIVER_SAMPL_DELAY		20.0	//Measured for receiever

//RTC_1 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} RTC1_Dev;

RTC1_Dev rtc1Dev;

//EINT_1 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT1_Dev;

EINT1_Dev eint1Dev;

//EINT_2 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT2_Dev;

EINT2_Dev eint2Dev;

//EINT_3 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT3_Dev;

EINT3_Dev eint3Dev;

//EINT_4 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT4_Dev;

EINT4_Dev eint4Dev;

//EINT_5 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT5_Dev;

EINT5_Dev eint5Dev;

//EINT_6 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
} EINT6_Dev;

EINT6_Dev eint6Dev;

//RECH1 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH1_Dev;

RECH1_Dev rech1Dev;

//RECH2 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH2_Dev;

RECH2_Dev rech2Dev;

//RECH3 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH3_Dev;

RECH3_Dev rech3Dev;

//RECH4 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH4_Dev;

RECH4_Dev rech4Dev;

//RECH5 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH5_Dev;

RECH5_Dev rech5Dev;

//RECH6 global variable
typedef struct {
	uint16_t time_low;
	uint16_t time_high;
	uint16_t period;
	uint8_t time_low_updated;
	int8_t time_high_updated;
	int8_t period_updated;
	uint16_t value;
} RECH6_Dev;

RECH6_Dev rech6Dev;

void RECDRIVER_Init(int rec_calib_state);

void RECDRIVER_GetAllChannelValue(float *ch, int with_filter);

int RECDRIVER_calibOffsets(void);

void RECDRIVER_UpdateChannelPeriod_CH1(void);
void RECDRIVER_UpdateChannelPeriod_CH2(void);
void RECDRIVER_UpdateChannelPeriod_CH3(void);
void RECDRIVER_UpdateChannelPeriod_CH4(void);
void RECDRIVER_UpdateChannelPeriod_CH5(void);
void RECDRIVER_UpdateChannelPeriod_CH6(void);


#endif /* RECDRIVER_H_ */
