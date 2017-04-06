#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>
#include "../PE_Types.h"
#include "../CI2C1.h"

#define MPU6050_ACCEL_G_AMPL		9.81f

#define GYRO_SENSITIVITY_FS_SEL      	0.00763358778625954198473282442748f		//(float)1.0/(float)131.0 		//deg/s/LSB
//#define GYRO_SENSITIVITY_FS_SEL        (float)1.0/(float)65.5
//#define GYRO_SENSITIVITY_FS_SEL      (float)1.0/(float)32.8
//#define GYRO_SENSITIVITY_FS_SEL      (float)1.0/(float)16.4



#define ACCEL_SENSITIVITY_FS_SEL      0.0005987548828125f//(float)MPU6050_ACCEL_G_AMPL/(float)16384		//deg/s/LSB
//#define ACCEL_SENSITIVITY_FS_SEL      (float)MPU6050_ACCEL_G_AMPL/(float)8192
//#define ACCEL_SENSITIVITY_FS_SEL      (float)MPU6050_ACCEL_G_AMPL/(float)4096
//#define ACCEL_SENSITIVITY_FS_SEL      (float)MPU6050_ACCEL_G_AMPL/(float)2048
  
 
#define MPU6050_ADDR            0x68  // Device address
//#define MPU6050_ADDR            0x69  // Device address

//Registers addresses:
#define SELF_TEST_X         13
#define SELF_TEST_Y         14
#define SELF_TEST_Z         15
#define SELF_TEST_A         16

#define SMPRT_DIV           25
#define CONFIG              26
#define GYRO_CONFIG         27
#define ACCEL_CONFIG        28

#define MOT_THR             31

#define FIFO_EN             35

#define I2C_MST_CTRL        36
#define I2C_SLV0_ADDR 		37
#define I2C_SLV0_REG		38	
#define I2C_SLV0_CTRL		39
#define I2C_SLV1_ADDR		40
#define I2C_SLV1_REG 		41	
#define I2C_SLV1_CTRL 		42
#define I2C_SLV2_ADDR		43
#define I2C_SLV2_REG		44	
#define I2C_SLV2_CTRL 		45
#define I2C_SLV3_ADDR		46
#define I2C_SLV3_REG 		47
#define I2C_SLV3_CTRL		48
#define I2C_SLV4_ADDR		49
#define I2C_SLV4_REG		50
#define I2C_SLV4_DO			51
#define I2C_SLV4_CTRL		52
#define I2C_SLV4_DI 		53
#define I2C_MST_STATUS 		54

#define INT_PIN_CFG			55
#define INT_ENABLE			56
#define INT_STATUS			58

#define ACCEL_XOUT_H		59
#define ACCEL_XOUT_L 		60
#define ACCEL_YOUT_H		61
#define ACCEL_YOUT_L		62
#define ACCEL_ZOUT_H 		63
#define ACCEL_ZOUT_L		64
#define TEMP_OUT_H			65
#define TEMP_OUT_L			66
#define GYRO_XOUT_H			67
#define GYRO_XOUT_L 		68
#define GYRO_YOUT_H 		69	
#define GYRO_YOUT_L			70
#define GYRO_ZOUT_H			71
#define GYRO_ZOUT_L 		72


#define I2C_SLV0_DO 		99
#define I2C_SLV1_DO 		100
#define I2C_SLV2_DO			101
#define I2C_SLV3_DO			102
#define I2C_MST_DELAY_CTRL	103

#define SIGNAL_PATH_RESET	104

#define MOT_DETECT_CTRL		105

#define USER_CTRL 			106
	
#define PWR_MGMT_1			107
#define PWR_MGMT_2			108

#define FIFO_COUNTH 		114
#define FIFO_COUNTL			115
#define FIFO_R_W 			116

#define WHO_AM_I			117



//Registers values:
#define SMPRT_DIV_VAL       0	//Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)

#define EXT_SYNC_SET		(0 << 3)
#define DLPF_CFG			(1 << 0)
#define CONFIG_VAL			(EXT_SYNC_SET|DLPF_CFG)	

#define XG_ST				(0 << 7)
#define YG_ST				(0 << 6) 
#define ZG_ST				(0 << 5)
#define FS_SEL				(0 << 3)	//250°/s
#define GYRO_CONFIG_VAL		(XG_ST|YG_ST|ZG_ST|FS_SEL)

#define XA_ST				(0 << 7)
#define YA_ST				(0 << 6) 
#define ZA_ST				(0 << 5)
#define AFS_SEL				(0 << 3)	//2g
#define ACCEL_CONFIG_VAL	(XA_ST|YA_ST|ZA_ST|AFS_SEL)

#define MOT_THR_VAL			0

#define TEMP_FIFO_EN 		(0 << 7)	
#define XG_FIFO_EN 			(0 << 6)
#define YG_FIFO_EN			(0 << 5)
#define ZG_FIFO_EN			(0 << 4)
#define ACCEL_FIFO_EN		(0 << 3)
#define SLV2_FIFO_EN		(0 << 2)
#define SLV1_FIFO_EN		(0 << 1)
#define SLV0_FIFO_EN		(0 << 0)
#define FIFO_EN_VAL	(TEMP_FIFO_EN|XG_FIFO_EN|YG_FIFO_EN|ZG_FIFO_EN|ACCEL_FIFO_EN|SLV2_FIFO_EN|SLV1_FIFO_EN|SLV0_FIFO_EN)		

#define INT_LEVEL 			(0 << 7)
#define INT_OPEN 			(0 << 6)	
#define LATCH_INT_EN 		(1 << 5)
#define INT_RD_CLEAR		(1 << 4)
#define FSYNC_INT_LEVEL 	(0 << 3)	
#define FSYNC_INT_EN		(0 << 2)	
#define I2C_BYPASS_EN		(0 << 1)	
#define INT_PIN_CFG_VAL (INT_LEVEL|INT_OPEN|LATCH_INT_EN|INT_RD_CLEAR|FSYNC_INT_LEVEL|FSYNC_INT_EN|I2C_BYPASS_EN)

#define MOT_EN				(0 << 6)
#define FIFO_OFLOW_EN		(0 << 4)
#define I2C_MST_INT_EN		(0 << 3)
#define DATA_RDY_EN			(1 << 0)
#define INT_ENABLE_VAL		(MOT_EN|FIFO_OFLOW_EN|I2C_MST_INT_EN|DATA_RDY_EN)

#define FIFO_EN_B 			(0 << 6)
#define I2C_MST_EN 			(0 << 5)
#define I2C_IF_DIS 			(0 << 4)
#define FIFO_RESET 			(0 << 2)
#define I2C_MST_RESET 		(0 << 1)
#define SIG_COND_RESET 		(0 << 0)
#define USER_CTRL_VAL		(FIFO_EN_B|I2C_MST_EN|I2C_IF_DIS|FIFO_RESET|I2C_MST_RESET|SIG_COND_RESET)

#define DEVICE_RESET		(0 << 7)
#define SLEEP 				(0 << 6)
#define CYCLE 				(0 << 5)
#define TEMP_DIS 			(0 << 3)
#define CLKSEL				(0 << 0)	//Internal 8MHz clock
#define PWR_MGMT_1_VAL		(DEVICE_RESET|SLEEP|CYCLE|TEMP_DIS|CLKSEL)


#define LP_WAKE_CTRL		(0 << 6)
#define STBY_XA				(0 << 5)
#define STBY_YA				(0 << 4)
#define STBY_ZA				(0 << 3)
#define STBY_XG				(0 << 2)
#define STBY_YG				(0 << 1)
#define STBY_ZG				(0 << 0)
#define PWR_MGMT_2_VAL		(LP_WAKE_CTRL|STBY_XA|STBY_YA|STBY_ZA|STBY_XG|STBY_YG|STBY_ZG)


typedef struct DATAStruct MPU6050Values;

struct DATAStruct {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float temp;
  int data_ready;
};


void MPU6050_Init(void);
int MPU6050_GetMeasurements(MPU6050Values *res);

int MPU6050_StartConversion(void);
int MPU6050_AskForConversionResult(void);
int MPU6050_GetConversionResult(MPU6050Values *res);

#endif
