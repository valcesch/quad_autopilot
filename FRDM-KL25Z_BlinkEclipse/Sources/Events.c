#include "Cpu.h"
#include "Events.h"
#include "libSENSDRIVE/mpu6050.h"
#include "libMOTDRIVE/optoe300.h"
#include "libRECDRIVER/recdriver.h"

#ifdef __cplusplus
extern "C" {
#endif 

//I2C_1 global variable
typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent;
  volatile uint8_t isReceived;
} I2CC1_Desc;

void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

void CI2C1_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
	/* Write your code here ... */
	I2CC1_Desc *ptr = (I2CC1_Desc*)UserDataPtr;

	ptr->isSent = TRUE; /* set flag so sender knows we have finished */
}

void CI2C1_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
	/* Write your code here ... */
	I2CC1_Desc *ptr = (I2CC1_Desc*)UserDataPtr;

	ptr->isReceived = TRUE; /* set flag so sender knows we have finished */
}

void PWM4_OnEnd(LDD_TUserData *UserDataPtr)
{
	OPTOE300_UpdateDutyRatio_PWM4();
}

void PWM3_OnEnd(LDD_TUserData *UserDataPtr)
{
	OPTOE300_UpdateDutyRatio_PWM3();
}

void PWM2_OnEnd(LDD_TUserData *UserDataPtr)
{
	OPTOE300_UpdateDutyRatio_PWM2();
}

void PWM1_OnEnd(LDD_TUserData *UserDataPtr)
{
	OPTOE300_UpdateDutyRatio_PWM1();
}

void EInt7_OnInterrupt(LDD_TUserData *UserDataPtr)
{

}

void EInt6_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH6();
}

void EInt5_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH5();
}

void EInt4_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH4();
}

void EInt3_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH3();
}

void EInt2_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH2();
}

void EInt1_OnInterrupt(LDD_TUserData *UserDataPtr)
{
	RECDRIVER_UpdateChannelPeriod_CH1();
}

void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

void FRTOS1_vApplicationTickHook(void)
{
  /* Called for every RTOS tick. */
  /* Write your code here ... */
}

void FRTOS1_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  /* Write your code here ... */
}

void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

void Cpu_OnSupervisorCall(void)
{
  vPortSVCHandler();
}

void Cpu_OnPendableService(void)
{
  vPortPendSVHandler();
}
/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif
