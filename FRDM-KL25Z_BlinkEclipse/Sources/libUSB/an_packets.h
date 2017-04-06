#ifndef __ARDUINO_PACKETS_H
#define __ARDUINO_PACKETS_H

#include "an_packet_protocol.h"

typedef enum
{
    packet_id_acknowledge,
    packet_id_request,
    packet_id_status,
}packet_id_e;

/* start of system packets typedef structs */

typedef enum
{
	acknowledge_success,
	acknowledge_failure_crc,
	acknowledge_failure_length,
	acknowledge_failure_range,
	acknowledge_failure_flash,
	acknowledge_failure_not_ready,
	acknowledge_failure_unknown_packet
} acknowledge_result_e;

typedef struct
{
	uint8_t packet_id;
	uint16_t packet_crc;
	uint8_t acknowledge_result;
} acknowledge_packet_t;

typedef struct
{
	int yaw;
	int pitch;
	int roll;
	int w_x;
	int w_y;
	int w_z;
	int a_x;
	int a_y;
	int a_z;
} status_packet_t;

void encode_acknowledge_packet(an_packet_t *an_packet, acknowledge_packet_t *acknowledge_packet);
void encode_status_packet(an_packet_t *an_packet, status_packet_t *status_packet);
int decode_request_packet(unsigned char *id, an_packet_t *an_packet);

#endif
