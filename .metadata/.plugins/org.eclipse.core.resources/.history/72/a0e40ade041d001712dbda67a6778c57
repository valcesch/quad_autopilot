#include "GYROACCVect.h"
#include "../libSENSDRIVE/mpu6050.h"
#include "../WAIT1.h"

#include <math.h>


/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 35 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 90 Hz - 110 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

* 200 Hz - 250 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/


/*

FIR filter designed with
http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 35 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 90 Hz - 110 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

* 200 Hz - 250 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/


#define SAMPLEFILTER_TAP_NUM 		9
#define SAMPLEFILTER_ACC_TAP_NUM 10

#define GYROACCVECT_ACCEL_G_AMPL	9.81

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
//		  2211,
//		  5079,
//		  8178,
//		  11122,
//		  12504,
//		  11122,
//		  8178,
//		  5079,
//		  2211
  2730,
  6992,
  8951,
  12721,
  15697,
  12721,
  8951,
  6992,
  2730
};

static int filter_acc_taps[SAMPLEFILTER_ACC_TAP_NUM] = {
  1264,
  3267,
  6082,
  8855,
  10589,
  10589,
  8855,
  6082,
  3267,
  1264
};

typedef struct {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
} SampleFilter;

typedef struct {
  int history[SAMPLEFILTER_ACC_TAP_NUM];
  unsigned int last_index;
} SampleFilter_acc;

void SampleFilter_init(SampleFilter* f);
void SampleFilter_put(SampleFilter* f, int input);
int SampleFilter_get(SampleFilter* f);

void SampleFilter_acc_init(SampleFilter_acc* f);
void SampleFilter_acc_put(SampleFilter_acc* f, int input);
int SampleFilter_acc_get(SampleFilter_acc* f);

#define GYROACCVECT_OFST_COMP_LENGTH		2000
#define GYROACCVECT_GYRO_OFST_X				0.0
#define GYROACCVECT_GYRO_OFST_Y				0.0
#define GYROACCVECT_GYRO_OFST_Z				0.0
#define GYROACCVECT_ACC_OFST_X				0.0
#define GYROACCVECT_ACC_OFST_Y				0.0
#define GYROACCVECT_ACC_OFST_Z				GYROACCVECT_ACCEL_G_AMPL
#define GYROACCVECT_GYRO_MAX_VALUE			2000.0
#define GYROACCVECT_ACCEL_MAX_VALUE			16.0
#define GYROACCVECT_INIT_GYRO_CALIB_TRESH_RATE	10.0

float gyro_ofst[3] = {0};
float accel_ofst[3] = {0};

MPU6050Values mpu_data;
SampleFilter filter_w_x;
SampleFilter filter_w_y;
SampleFilter filter_w_z;
SampleFilter filter_a_x;
SampleFilter filter_a_y;
SampleFilter filter_a_z;

int GYROACCVECT_Init(void)
{
	MPU6050_Init();
	WAIT1_Waitms(300);
	MPU6050_Init();	//" initialization required -> for the first time, the noise level is too important

	SampleFilter_init(&filter_w_x);
	SampleFilter_init(&filter_w_y);
	SampleFilter_init(&filter_w_z);

	SampleFilter_init(&filter_a_x);
	SampleFilter_init(&filter_a_y);
	SampleFilter_init(&filter_a_z);

	//Apply default offsets
	gyro_ofst[0] = GYROACCVECT_GYRO_OFST_X;
	gyro_ofst[1] = GYROACCVECT_GYRO_OFST_Y;
	gyro_ofst[2] = GYROACCVECT_GYRO_OFST_Z;

	accel_ofst[0] = GYROACCVECT_ACC_OFST_X;
	accel_ofst[1] = GYROACCVECT_ACC_OFST_Y;
	accel_ofst[2] = GYROACCVECT_ACC_OFST_Z;

	return 0;
}

int GYROACCVECT_CheckForStabilization(void){

	MPU6050_GetMeasurements(&mpu_data);
	if(fabs(mpu_data.gx) > GYROACCVECT_INIT_GYRO_CALIB_TRESH_RATE ||
			fabs(mpu_data.gy) > GYROACCVECT_INIT_GYRO_CALIB_TRESH_RATE ||
			fabs(mpu_data.gz) > GYROACCVECT_INIT_GYRO_CALIB_TRESH_RATE){

		//WAIT1_Waitms(GYROACCVECT_INIT_GYRO_CALIB_TRESH_SAMPL_DELAY);
		return FALSE;	//Is not stable
	}
	else{
		return TRUE;	//Is stable
	}
}

int GYROACCVECT_calibOffsets(void){

	static float ofst_temp_gyro[3] = {0, 0, 0};
	static float ofst_temp_accel[3] = {0, 0, 0};
	static int i = 0;
	float G[3] = {0, 0, 0}, A[3] = {0, 0, 0};

	if (i < GYROACCVECT_OFST_COMP_LENGTH && GYROACCVECT_GetVector(G, A) == 0){
		MPU6050_GetMeasurements(&mpu_data);

		ofst_temp_gyro[0] += G[0];
		ofst_temp_gyro[1] += G[1];
		ofst_temp_gyro[2] += G[2];

		ofst_temp_accel[0] += A[0];
		ofst_temp_accel[1] += A[1];
		ofst_temp_accel[2] += (A[2] + GYROACCVECT_ACCEL_G_AMPL);

		//WAIT1_Waitms(GYROACCVECT_SAMPL_DELAY);

		i++;
		return FALSE;	//Calibration not completed
	}
	else if(i == GYROACCVECT_OFST_COMP_LENGTH){

		gyro_ofst[0] = ofst_temp_gyro[0] / (float)GYROACCVECT_OFST_COMP_LENGTH;
		gyro_ofst[1] = ofst_temp_gyro[1] / (float)GYROACCVECT_OFST_COMP_LENGTH;
		gyro_ofst[2] = ofst_temp_gyro[2] / (float)GYROACCVECT_OFST_COMP_LENGTH;

		accel_ofst[0] = ofst_temp_accel[0] / (float)GYROACCVECT_OFST_COMP_LENGTH;
		accel_ofst[1] = ofst_temp_accel[1] / (float)GYROACCVECT_OFST_COMP_LENGTH;
		accel_ofst[2] = ofst_temp_accel[2] / (float)GYROACCVECT_OFST_COMP_LENGTH;

		return TRUE;	//Calibration completed
	}
}

int GYROACCVECT_NB_StartVectorAcquisition(void){

	return MPU6050_StartConversion();
}

int GYROACCVECT_NB_AskForVectorAcquisition(void){

	return MPU6050_AskForConversionResult();
}

int GYROACCVECT_NB_GetVector(float *G, float *A){

	//Raw data filtering:
	if(MPU6050_GetConversionResult(&mpu_data) == 0){

		G[0] = mpu_data.gx - gyro_ofst[0];
		G[1] = mpu_data.gy - gyro_ofst[1];
		G[2] = mpu_data.gz - gyro_ofst[2];

		A[0] = mpu_data.ax - accel_ofst[0];
		A[1] = mpu_data.ay - accel_ofst[1];
		A[2] = mpu_data.az - accel_ofst[2];

		return 0;
	}
	else{
		return 1;
	}
}

int GYROACCVECT_GetVector(float *G, float *A){

	//Raw data filtering:
	if(MPU6050_GetMeasurements(&mpu_data) == 0){

		GYROACCVECT_gyro_butterFilter_x(mpu_data.gx, &G[0]);
		GYROACCVECT_gyro_butterFilter_y(mpu_data.gy, &G[1]);
		GYROACCVECT_gyro_butterFilter_z(mpu_data.gz, &G[2]);

		//		G[0] = mpu_data.gx - gyro_ofst[0];
		//		G[1] = mpu_data.gy - gyro_ofst[1];
		//		G[2] = mpu_data.gz - gyro_ofst[2];

		GYROACCVECT_acc_butterFilter_x(mpu_data.ax, &A[0]);
		GYROACCVECT_acc_butterFilter_y(mpu_data.ay, &A[1]);
		GYROACCVECT_acc_butterFilter_z(mpu_data.az, &A[2]);

//		A[0] = mpu_data.ax - accel_ofst[0];
//		A[1] = mpu_data.ay - accel_ofst[1];
//		A[2] = mpu_data.az - accel_ofst[2];

		return 0;
	}
	else{
		return 1;
	}
}

void GYROACCVECT_gyro_butterFilter_x(float in, float *out){

	SampleFilter_put(&filter_w_x, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_w_x);

	*out = (float)data_tmp * 0.1;
}

void GYROACCVECT_gyro_butterFilter_y(float in, float *out){

	SampleFilter_put(&filter_w_y, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_w_y);

	*out = (float)data_tmp * 0.1;
}

void GYROACCVECT_gyro_butterFilter_z(float in, float *out){

	SampleFilter_put(&filter_w_z, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_w_z);

	*out = (float)data_tmp * 0.1;
}

void GYROACCVECT_acc_butterFilter_x(float in, float *out){

	SampleFilter_put(&filter_a_x, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_a_x);

	*out = (float)data_tmp * 0.1;
}

void GYROACCVECT_acc_butterFilter_y(float in, float *out){

	SampleFilter_put(&filter_a_y, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_a_y);

	*out = (float)data_tmp * 0.1;
}

void GYROACCVECT_acc_butterFilter_z(float in, float *out){

	SampleFilter_put(&filter_a_z, (int)(in * 10.0));

	int data_tmp = SampleFilter_get(&filter_a_z);

	*out = (float)data_tmp * 0.1;
}

void SampleFilter_init(SampleFilter* f) {
  int i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void SampleFilter_put(SampleFilter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == SAMPLEFILTER_TAP_NUM)
    f->last_index = 0;
}

int SampleFilter_get(SampleFilter* f) {
  long acc = 0;
  int index = f->last_index;
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[0];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[1];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[2];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[3];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[4];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[5];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[6];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[7];
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long)f->history[index] * filter_taps[8];
  return acc >> 16;	//16 ?
}

void SampleFilter_acc_init(SampleFilter_acc* f) {
  int i;
  for(i = 0; i < SAMPLEFILTER_ACC_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void SampleFilter_acc_put(SampleFilter_acc* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == SAMPLEFILTER_ACC_TAP_NUM)
    f->last_index = 0;
}

int SampleFilter_acc_get(SampleFilter_acc* f) {
  long acc = 0;
  int index = f->last_index;
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[0];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[1];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[2];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[3];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[4];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[5];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[6];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[7];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[8];
    index = index != 0 ? index-1 : SAMPLEFILTER_ACC_TAP_NUM-1;
    acc += (long)f->history[index] * filter_acc_taps[9];
  return acc >> 16;
}
