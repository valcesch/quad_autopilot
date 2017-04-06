/*
 * optoe300.c
 *
 *  Created on: 4 févr. 2017
 *      Author: Raphael
 */

#include "optoe300.h"
#include "../PWM1.h"
#include "../PWM2.h"
#include "../PWM3.h"
#include "../PWM4.h"

#define OPTOE300_TIMER_RESOLUTION	65536.0
#define OPTOE300_MOT_MIN_PERIOD		OPTOE300_TIMER_RESOLUTION * 0.05 + OPTOE300_TIMER_RESOLUTION * 0.025 //(7.5%) 4915.2
#define OPTOE300_MOT_MAX_PERIOD		(OPTOE300_MOT_MIN_PERIOD + OPTOE300_TIMER_RESOLUTION * 0.025) + 23000 //(10%) 6553.6
#define OPTOE300_MOT_FL				0
#define OPTOE300_MOT_FR				1
#define OPTOE300_MOT_BR				2
#define OPTOE300_MOT_BL				3

uint16_t OPTOE300_ComputePWMRatio(float duty);

//Init PWM pins with minimum period (5% duty)
void OPTOE300_Init(){

	pwm1Dev.handle = PWM1_Init(&pwm1Dev);
	pwm2Dev.handle = PWM2_Init(&pwm2Dev);
	pwm3Dev.handle = PWM3_Init(&pwm3Dev);
	pwm4Dev.handle = PWM4_Init(&pwm4Dev);
}

//Input -> table, motor speed (0-1%)
void OPTOE300_SetSpeed(float *cmd){

	pwm1Dev.timer_period = OPTOE300_ComputePWMRatio(cmd[OPTOE300_MOT_FR]);
	pwm2Dev.timer_period = OPTOE300_ComputePWMRatio(cmd[OPTOE300_MOT_FL]);
	pwm3Dev.timer_period = OPTOE300_ComputePWMRatio(cmd[OPTOE300_MOT_BR]);
	pwm4Dev.timer_period = OPTOE300_ComputePWMRatio(cmd[OPTOE300_MOT_BL]);
}

//Update PWM period
void OPTOE300_UpdateDutyRatio_PWM1(void){

	PWM1_SetRatio16(&pwm1Dev, pwm1Dev.timer_period);

	//Should return error
}

void OPTOE300_UpdateDutyRatio_PWM2(void){

	PWM2_SetRatio16(&pwm2Dev, pwm2Dev.timer_period);

	//Should return error
}

void OPTOE300_UpdateDutyRatio_PWM3(void){

	PWM3_SetRatio16(&pwm3Dev, pwm3Dev.timer_period);

	//Should return error
}

void OPTOE300_UpdateDutyRatio_PWM4(void){

	PWM4_SetRatio16(&pwm4Dev, pwm4Dev.timer_period);

	//Should return error
}

uint16_t OPTOE300_ComputePWMRatio(float duty) {

	return (uint16_t)OPTOE300_TIMER_RESOLUTION - (uint16_t) ((OPTOE300_MOT_MAX_PERIOD - OPTOE300_MOT_MIN_PERIOD) * duty + OPTOE300_MOT_MIN_PERIOD + 22000);
}


