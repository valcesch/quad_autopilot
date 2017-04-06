/* ###################################################################
**     Filename    : Events.h
**     Project     : uart2
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-12-04, 10:15, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "FreeRTOS.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "FRTOS1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "CI2C1.h"
#include "EInt1.h"
#include "EInt2.h"
#include "EInt3.h"
#include "EInt4.h"
#include "EInt5.h"
#include "EInt6.h"
#include "EInt7.h"
#include "PWM1.h"
#include "TU1.h"
#include "PWM2.h"
#include "PWM3.h"
#include "PWM4.h"
#include "FC1.h"
#include "TU3.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "USB0.h"
#include "CLS1.h"
#include "CS1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "XF1.h"

#ifdef __cplusplus
extern "C" {
#endif 

void Cpu_OnNMIINT(void);


void CI2C1_OnMasterBlockSent(LDD_TUserData *UserDataPtr);

void CI2C1_OnMasterBlockReceived(LDD_TUserData *UserDataPtr);

void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);

void FRTOS1_vApplicationTickHook(void);

void FRTOS1_vApplicationIdleHook(void);

void FRTOS1_vApplicationMallocFailedHook(void);

void Cpu_OnSupervisorCall(void);

void Cpu_OnPendableService(void);

void EInt1_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt2_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt3_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt4_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt5_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt6_OnInterrupt(LDD_TUserData *UserDataPtr);
void EInt7_OnInterrupt(LDD_TUserData *UserDataPtr);

void PWM1_OnEnd(LDD_TUserData *UserDataPtr);
void PWM2_OnEnd(LDD_TUserData *UserDataPtr);
void PWM3_OnEnd(LDD_TUserData *UserDataPtr);
void PWM4_OnEnd(LDD_TUserData *UserDataPtr);


/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
