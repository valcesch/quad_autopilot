#ifndef GATT_H_
#define GATT_H_

#define YAW		0
#define PITCH	1
#define ROLL	2

void GATT_getAtt(float G[3], float A[3], float E[3], float dt);

void GATT_gyro_x_angle_LP(float in , float *out);
void GATT_gyro_y_angle_LP(float in , float *out);
void GATT_gyro_z_angle_LP(float in , float *out);

void GATT_x_angle_LP(float in , float *out);
void GATT_y_angle_LP(float in , float *out);
void GATT_z_angle_LP(float in , float *out);

#endif
