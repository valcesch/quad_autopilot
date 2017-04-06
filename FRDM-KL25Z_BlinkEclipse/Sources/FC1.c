/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : FC1.c
**     Project     : flightcontroller
**     Processor   : MKL25Z128VLK4
**     Component   : FreeCntr_LDD
**     Version     : Component 01.005, Driver 01.01, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-27, 20:59, # CodeGen: 19
**     Abstract    :
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
**     Settings    :
**          Component name                                 : FC1
**          Module name                                    : TPM2
**          Counter                                        : TPM2_CNT
**          Counter direction                              : Up
**          Counter frequency                              : Auto select
**          Mode                                           : Free-running
**            Overrun period                               : 87.381333 ms
**            Interrupt service/event                      : Disabled
**          Value type                                     : Optimal
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnInterrupt                                : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**          Referenced components                          : 
**            Linked TimerUnit                             : TU3
**     Contents    :
**         Init            - LDD_TDeviceData* FC1_Init(LDD_TUserData *UserDataPtr);
**         Deinit          - void FC1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue - FC1_TValueType FC1_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);
**         ResetCounter    - LDD_TError FC1_ResetCounter(LDD_TUserData *DeviceDataPtr);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file FC1.c
** @version 01.01
** @brief
**          This device "FreeCntr_LDD" implements Free Running Counter
**          This FreeCntr component provides a high level API for unified
**          hardware access to various timer devices using the TimerUnit
**          component.
*/         
/*!
**  @addtogroup FC1_module FC1 module documentation
**  @{
*/         

/* MODULE FC1. */

#include "FC1.h"
#include "FreeRTOS.h" /* FreeRTOS interface */

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct {
  LDD_TDeviceData *LinkedDeviceDataPtr;
  bool EnUser;                         /* Enable/Disable device */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} FC1_TDeviceData;

typedef FC1_TDeviceData *FC1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {FreeRTOS RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static FC1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;

/*
** ===================================================================
**     Method      :  FC1_Init (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* FC1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  FC1_TDeviceData *DeviceDataPrv;
  /* {FreeRTOS RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->EnUser = TRUE;        /* Set the flag "device enabled" */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_FC1_ID,DeviceDataPrv);
  DeviceDataPrv->LinkedDeviceDataPtr = TU3_Init((LDD_TUserData *)NULL);
  if (DeviceDataPrv->LinkedDeviceDataPtr == NULL) { /* Is initialization of TimerUnit unsuccessful? */
    /* Unregistration of the device structure */
    PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_FC1_ID);
    /* Deallocation of the device structure */
    /* {FreeRTOS RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
    return NULL;                       /* If so, then the FreeCntr initialization is also unsuccessful */
  }
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  FC1_Deinit (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void FC1_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  FC1_TDeviceData *DeviceDataPrv = (FC1_TDeviceData *)DeviceDataPtr;

  TU3_Deinit(DeviceDataPrv->LinkedDeviceDataPtr);
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_FC1_ID);
  /* Deallocation of the device structure */
  /* {FreeRTOS RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
}

/*
** ===================================================================
**     Method      :  FC1_GetCounterValue (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
FC1_TValueType FC1_GetCounterValue(LDD_TDeviceData *DeviceDataPtr)
{
  FC1_TDeviceData *DeviceDataPrv = (FC1_TDeviceData *)DeviceDataPtr;

  return TU3_GetCounterValue(DeviceDataPrv->LinkedDeviceDataPtr);
}

/*
** ===================================================================
**     Method      :  FC1_ResetCounter (component FreeCntr_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError FC1_ResetCounter(LDD_TUserData *DeviceDataPtr)
{
  FC1_TDeviceData *DeviceDataPrv = (FC1_TDeviceData *)DeviceDataPtr;

  return TU3_ResetCounter(DeviceDataPrv->LinkedDeviceDataPtr); /* Reset counter register */
}

/* END FC1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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