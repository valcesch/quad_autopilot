/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : EInt4.h
**     Project     : flightcontroller
**     Processor   : MKL25Z128VLK4
**     Component   : ExtInt_LDD
**     Version     : Component 02.156, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-27, 20:35, # CodeGen: 17
**     Abstract    :
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**          Component name                                 : EInt4
**          Pin                                            : PTD2/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO
**          Pin signal                                     : 
**          Generate interrupt on                          : both edges
**          Interrupt                                      : INT_PORTD
**          Interrupt priority                             : medium priority
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**          Threshold level                                : 0
**     Contents    :
**         Init - LDD_TDeviceData* EInt4_Init(LDD_TUserData *UserDataPtr);
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
** @file EInt4.h
** @version 01.02
** @brief
**         This component, "ExtInt_LDD", provide a low level API 
**         for unified access of external interrupts handling
**         across various device designs.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup EInt4_module EInt4 module documentation
**  @{
*/         

#ifndef __EInt4_H
#define __EInt4_H

/* MODULE EInt4. */

#include "Cpu.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "GPIO_PDD.h"
#include "PORT_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define EInt4_PRPH_BASE_ADDRESS  0x400FF0C0U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define EInt4_Init_METHOD_ENABLED      /*!< Init method of the component EInt4 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define EInt4_OnInterrupt_EVENT_ENABLED /*!< OnInterrupt event of the component EInt4 is enabled (generated) */

/* Definition of implementation constants */
#define EInt4_PIN_INDEX 0x02U          /*!< Index of the used pin from the port */
#define EInt4_PIN_MASK 0x04U           /*!< Mask of the used pin from the port */

/*
** ===================================================================
**     Method      :  EInt4_Init (component ExtInt_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* EInt4_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  EInt4_Interrupt (component ExtInt_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {FreeRTOS RTOS Adapter} ISR function prototype */
void EInt4_Interrupt(void);

/* END EInt4. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __EInt4_H */
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
