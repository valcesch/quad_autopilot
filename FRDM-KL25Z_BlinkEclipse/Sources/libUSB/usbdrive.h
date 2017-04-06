/*
 * usbdrive.h
 *
 *  Created on: 5 févr. 2017
 *      Author: Raphael
 */

#ifndef USBDRIVE_H_
#define USBDRIVE_H_

#include "../PE_Types.h"

void USBDRIVE_Init(void);
void USBDRIVE_SendBuffer(uint8_t *buf, uint8_t length);
int USBDRIVE_ReceiveBuffer(uint8_t *buf);
void USBDRIVE_flush();
void USBDRIVE_PrintDouble(double val);
uint8_t USBDRIVE_DataIsAvailable(void);

#endif /* USBDRIVE_H_ */
