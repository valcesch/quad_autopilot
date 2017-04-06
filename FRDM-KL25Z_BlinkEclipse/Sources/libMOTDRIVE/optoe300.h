/*
 * optoe300.h
 *
 *  Created on: 4 févr. 2017
 *      Author: Raphael
 */

#ifndef OPTOE300_H_
#define OPTOE300_H_

#include <stdint.h>
#include "../PE_Types.h"

#define MOT_AVD	0
#define MOT_AVG	1
#define MOT_ARD	2
#define MOT_ARG	3

//PWM_1 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
	uint16_t timer_period;
} PWM1_Dev;

PWM1_Dev pwm1Dev;

//PWM_2 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
	uint16_t timer_period;
} PWM2_Dev;

PWM2_Dev pwm2Dev;

//PWM_3 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
	uint16_t timer_period;
} PWM3_Dev;

PWM3_Dev pwm3Dev;

//PWM_4 global variable
typedef struct {
	LDD_TDeviceData *handle; /* LDD device handle */
	uint16_t timer_period;
} PWM4_Dev;

PWM4_Dev pwm4Dev;

void OPTOE300_Init();
void OPTOE300_SetSpeed(float *cmd);
void OPTOE300_UpdateDutyRatio_PWM1(void);
void OPTOE300_UpdateDutyRatio_PWM2(void);
void OPTOE300_UpdateDutyRatio_PWM3(void);
void OPTOE300_UpdateDutyRatio_PWM4(void);

#endif /* OPTOE300_H_ */
