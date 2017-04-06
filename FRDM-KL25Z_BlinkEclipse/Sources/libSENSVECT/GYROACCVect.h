#ifndef GYROACCVECT_H_
#define GYROACCVECT_H_

#define GYROACCVECT_SAMPL_DELAY							(uint16_t)2
#define GYROACCVECT_INIT_GYRO_CALIB_TRESH_SAMPL_DELAY	(uint16_t)100

int GYROACCVECT_Init(void);
int GYROACCVECT_CheckForStabilization(void);
int GYROACCVECT_calibOffsets(void);
int GYROACCVECT_GetVector(float *G, float *A);
int GYROACCVECT_NB_StartVectorAcquisition(void);
int GYROACCVECT_NB_AskForVectorAcquisition(void);
int GYROACCVECT_NB_GetVector(float *G, float *A);

void GYROACCVECT_gyro_butterFilter_x(float in, float *out);
void GYROACCVECT_gyro_butterFilter_y(float in, float *out);
void GYROACCVECT_gyro_butterFilter_z(float in, float *out);

void GYROACCVECT_acc_butterFilter_x(float in, float *out);
void GYROACCVECT_acc_butterFilter_y(float in, float *out);
void GYROACCVECT_acc_butterFilter_z(float in, float *out);

#endif
