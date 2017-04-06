/*
 * global.h
 *
 *  Created on: 2 mars 2017
 *      Author: Raphael
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


typedef struct {

	float yaw;
	float pitch;
	float roll;
	float yaw_d;
	float pitch_d;
	float roll_d;
	float w_x;
	float w_y;
	float w_z;
	float a_x;
	float a_y;
	float a_z;

	float rec_ch[6];

	float mot_cmd[4];

	float temp;
	float pressure;

} STATE_Dev;

STATE_Dev gstate;


#endif /* GLOBAL_H_ */
