#include "mpu6050.h"

float MPU6050_ConvertGyro(int16_t value);
float MPU6050_ConvertAccel(int16_t value);

//I2C_1 global variable
typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent;
  volatile uint8_t isReceived;
} I2CC1_Desc;

I2CC1_Desc deviceI2cc1;

uint8_t data_buf[14] = {0};

void MPU6050_Init(void){

	deviceI2cc1.handle = CI2C1_Init(&deviceI2cc1);

	deviceI2cc1.isSent = FALSE;

	uint8_t conf_buf[2] = {CONFIG, CONFIG_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t smprt_conf_buf[2] = {SMPRT_DIV, SMPRT_DIV_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, smprt_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t gyro_conf_buf[2] = {GYRO_CONFIG, GYRO_CONFIG_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, gyro_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t accel_conf_buf[2] = {ACCEL_CONFIG, ACCEL_CONFIG_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, accel_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t fifo_conf_buf[2] = {FIFO_EN, FIFO_EN_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, fifo_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t int_conf_buf[2] = {INT_PIN_CFG, INT_PIN_CFG_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, int_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t int_enable_buf[2] = {INT_ENABLE, INT_ENABLE_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, int_enable_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t usr_ctrl_conf_buf[2] = {USER_CTRL, USER_CTRL_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, usr_ctrl_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	uint8_t pwr_mgmt_1_conf_buf[2] = {PWR_MGMT_1, PWR_MGMT_1_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, pwr_mgmt_1_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}	//LDD_I2C_SEND_STOP
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;
	uint8_t pwr_mgmt_2_conf_buf[2] = {PWR_MGMT_2, PWR_MGMT_2_VAL};
	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, pwr_mgmt_2_conf_buf, 2, LDD_I2C_SEND_STOP)!=ERR_OK) {}
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;
}


int MPU6050_StartConversion(void){

	uint8_t conf = ACCEL_XOUT_H;

	deviceI2cc1.isSent = FALSE;
	deviceI2cc1.isReceived = FALSE;

	while(CI2C1_MasterSendBlock(deviceI2cc1.handle, &conf, 1, LDD_I2C_SEND_STOP)!=ERR_OK);
	while(deviceI2cc1.isSent != TRUE);
	deviceI2cc1.isSent = FALSE;

	return 0;
}

int MPU6050_AskForConversionResult(void){

	return CI2C1_MasterReceiveBlock(deviceI2cc1.handle, data_buf, 14, LDD_I2C_SEND_STOP);
}

int MPU6050_GetConversionResult(MPU6050Values *res){

	if(deviceI2cc1.isReceived == TRUE){

		deviceI2cc1.isReceived = FALSE;

		int16_t data;
		data = (data_buf[0] << 8) | data_buf[1];
		res->ax = MPU6050_ConvertAccel(data);
		data = (data_buf[2] << 8) | data_buf[3];
		res->ay = MPU6050_ConvertAccel(data);
		data = (data_buf[4] << 8) | data_buf[5];
		res->az = MPU6050_ConvertAccel(data);
		data = (data_buf[8] << 8) | data_buf[9];
		res->gx = MPU6050_ConvertGyro(data);
		data = (data_buf[10] << 8) | data_buf[11];
		res->gy = MPU6050_ConvertGyro(data);
		data = (data_buf[12] << 8) | data_buf[13];
		res->gz = MPU6050_ConvertGyro(data);

		return 0;
	}
	else{
		return 1;
	}
}

int MPU6050_GetMeasurements(MPU6050Values *res){

  //uint8_t data_buf[14] = {0};
  int16_t data;
  uint8_t conf = ACCEL_XOUT_H;

  deviceI2cc1.isSent = FALSE;
  deviceI2cc1.isReceived = FALSE;

  //Careful -> blocking solution -> add timeout

  while(CI2C1_MasterSendBlock(deviceI2cc1.handle, &conf, 1, LDD_I2C_SEND_STOP)!=ERR_OK);
  while(deviceI2cc1.isSent != TRUE);
  deviceI2cc1.isSent = FALSE;

  while(CI2C1_MasterReceiveBlock(deviceI2cc1.handle, data_buf, 14, LDD_I2C_SEND_STOP)!=ERR_OK);
  while(deviceI2cc1.isReceived != TRUE);
  deviceI2cc1.isReceived = FALSE;

  data = (data_buf[0] << 8) | data_buf[1];
  res->ax = MPU6050_ConvertAccel(data);
  data = (data_buf[2] << 8) | data_buf[3];
  res->ay = MPU6050_ConvertAccel(data);
  data = (data_buf[4] << 8) | data_buf[5];
  res->az = MPU6050_ConvertAccel(data);
  data = (data_buf[8] << 8) | data_buf[9];
  res->gx = MPU6050_ConvertGyro(data);
  data = (data_buf[10] << 8) | data_buf[11];
  res->gy = MPU6050_ConvertGyro(data);
  data = (data_buf[12] << 8) | data_buf[13];
  res->gz = MPU6050_ConvertGyro(data);

  return 0;
}

float MPU6050_ConvertGyro(int16_t value) {

  return (float)value * GYRO_SENSITIVITY_FS_SEL;
}

float MPU6050_ConvertAccel(int16_t value) {

  return (float)value * ACCEL_SENSITIVITY_FS_SEL;
}
