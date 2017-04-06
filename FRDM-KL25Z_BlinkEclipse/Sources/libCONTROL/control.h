#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdint.h>

void CONTROL_Init(void);
void CONTROL_callBack(float rec_yaw, float rec_pitch,
		float rec_roll, float rec_gas,
		float rec_aux1, float rec_aux2,
		float *mot_cmd_avd, float *mot_cmd_avg,
		float *mot_cmd_ard, float *mot_cmd_arg,
		float w_x, float w_y, float w_z,
		float yaw, float pitch, float roll,
		float *state);

#endif
