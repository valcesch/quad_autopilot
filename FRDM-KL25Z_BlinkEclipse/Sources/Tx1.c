/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Tx1.c
**     Project     : flightcontroller
**     Processor   : MKL25Z128VLK4
**     Component   : RingBuffer
**     Version     : Component 01.048, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-27, 20:59, # CodeGen: 19
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : Tx1
**          Buffer Size                                    : 64
**     Contents    :
**         Clear           - void Tx1_Clear(void);
**         Put             - uint8_t Tx1_Put(Tx1_ElementType elem);
**         Putn            - uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof);
**         Get             - uint8_t Tx1_Get(Tx1_ElementType *elemP);
**         Peek            - uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP);
**         Compare         - uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP,...
**         Delete          - uint8_t Tx1_Delete(void);
**         NofElements     - Tx1_BufSizeType Tx1_NofElements(void);
**         NofFreeElements - Tx1_BufSizeType Tx1_NofFreeElements(void);
**         Deinit          - void Tx1_Deinit(void);
**         Init            - void Tx1_Init(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2014-2015, all rights reserved.
**     Web: http://www.mcuoneclipse.com
**     This an open source software of an embedded component for Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file Tx1.c
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup Tx1_module Tx1 module documentation
**  @{
*/         

/* MODULE Tx1. */

#include "Tx1.h"

#if Tx1_CONFIG_REENTRANT
  #define Tx1_DEFINE_CRITICAL() CS1_CriticalVariable()
  #define Tx1_ENTER_CRITICAL()  CS1_EnterCritical()
  #define Tx1_EXIT_CRITICAL()   CS1_ExitCritical()
#else
  #define Tx1_DEFINE_CRITICAL() /* nothing */
  #define Tx1_ENTER_CRITICAL()  /* nothing */
  #define Tx1_EXIT_CRITICAL()   /* nothing */
#endif
static Tx1_ElementType Tx1_buffer[Tx1_CONFIG_BUF_SIZE]; /* ring buffer */
static Tx1_BufSizeType Tx1_inIdx;  /* input index */
static Tx1_BufSizeType Tx1_outIdx; /* output index */
static Tx1_BufSizeType Tx1_inSize; /* size data in buffer */
/*
** ===================================================================
**     Method      :  Tx1_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Put(Tx1_ElementType elem)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==Tx1_CONFIG_BUF_SIZE) {
    res = ERR_TXFULL;
  } else {
    Tx1_buffer[Tx1_inIdx] = elem;
    Tx1_inIdx++;
    if (Tx1_inIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_inIdx = 0;
    }
    Tx1_inSize++;
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Tx1_Putn (component RingBuffer)
**     Description :
**         Put a number new element into the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elem            - Pointer to new elements to be put into
**                           the buffer
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Putn(Tx1_ElementType *elem, Tx1_BufSizeType nof)
{
  uint8_t res = ERR_OK;

  while(nof>0) {
    res = Tx1_Put(*elem);
    if (res!=ERR_OK) {
      break;
    }
    elem++; nof--;
  }
  return res;
}

/*
** ===================================================================
**     Method      :  Tx1_Get (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Get(Tx1_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    *elemP = Tx1_buffer[Tx1_outIdx];
    Tx1_inSize--;
    Tx1_outIdx++;
    if (Tx1_outIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_outIdx = 0;
    }
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Tx1_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
Tx1_BufSizeType Tx1_NofElements(void)
{
  return Tx1_inSize;
}

/*
** ===================================================================
**     Method      :  Tx1_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
Tx1_BufSizeType Tx1_NofFreeElements(void)
{
  return (Tx1_BufSizeType)(Tx1_CONFIG_BUF_SIZE-Tx1_inSize);
}

/*
** ===================================================================
**     Method      :  Tx1_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Tx1_Init(void)
{
  Tx1_inIdx = 0;
  Tx1_outIdx = 0;
  Tx1_inSize = 0;
}

/*
** ===================================================================
**     Method      :  Tx1_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Tx1_Clear(void)
{
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  Tx1_Init();
  Tx1_EXIT_CRITICAL();
}

/*
** ===================================================================
**     Method      :  Tx1_Peek (component RingBuffer)
**     Description :
**         Returns an element of the buffer without removiing it.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Peek(Tx1_BufSizeType index, Tx1_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  int idx; /* index inside ring buffer */
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (index>=Tx1_CONFIG_BUF_SIZE) {
    res = ERR_OVERFLOW; /* asking for an element outside of ring buffer size */
  } else if (index<Tx1_inSize) {
    idx = (Tx1_outIdx+index)%Tx1_CONFIG_BUF_SIZE;
    *elemP = Tx1_buffer[idx];
  } else { /* asking for an element which does not exist */
    res = ERR_RXEMPTY;
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  Tx1_Compare (component RingBuffer)
**     Description :
**         Compares the elements in the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to elements to compare with
**         nof             - number of elements to compare
**     Returns     :
**         ---             - zero if elements are the same, -1 otherwise
** ===================================================================
*/
uint8_t Tx1_Compare(Tx1_BufSizeType index, Tx1_ElementType *elemP, Tx1_BufSizeType nof)
{
  uint8_t cmpResult = 0;
  uint8_t res;
  Tx1_ElementType val;

  while(nof>0) {
    res = Tx1_Peek(index, &val);
    if (res!=ERR_OK) { /* general failure? */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    if (val!=*elemP) { /* mismatch */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    elemP++; index++; nof--;
  }

  return cmpResult;
}

/*
** ===================================================================
**     Method      :  Tx1_Deinit (component RingBuffer)
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void Tx1_Deinit(void)
{
  ** Function is implemented as macro in the header file
}
*/
/*
** ===================================================================
**     Method      :  Tx1_Delete (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t Tx1_Delete(void)
{
  uint8_t res = ERR_OK;
  Tx1_DEFINE_CRITICAL();

  Tx1_ENTER_CRITICAL();
  if (Tx1_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    Tx1_inSize--;
    Tx1_outIdx++;
    if (Tx1_outIdx==Tx1_CONFIG_BUF_SIZE) {
      Tx1_outIdx = 0;
    }
  }
  Tx1_EXIT_CRITICAL();
  return res;
}

/* END Tx1. */

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