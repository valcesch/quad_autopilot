#include <stdint.h>
#include <string.h>

#include "an_packet_protocol.h"
#include "an_packets.h"
#include <stdint.h>

void encode_acknowledge_packet(an_packet_t *an_packet, acknowledge_packet_t *acknowledge_packet)
{
  an_packet->id = packet_id_acknowledge;
  an_packet->an_length = 4;
  memcpy(&an_packet->data[0], &acknowledge_packet->packet_id, 1 * sizeof(uint8_t));
  memcpy(&an_packet->data[1], &acknowledge_packet->packet_crc, 1 * sizeof(uint16_t));
  memcpy(&an_packet->data[3], &acknowledge_packet->acknowledge_result, 1 * sizeof(uint8_t));
}

void encode_status_packet(an_packet_t *an_packet, status_packet_t *status_packet)
{
  an_packet->id = packet_id_status;
  an_packet->an_length = 9 * sizeof(int);
  memcpy(&an_packet->data[0], &status_packet->yaw, sizeof(int));
  memcpy(&an_packet->data[4], &status_packet->pitch, sizeof(int));
  memcpy(&an_packet->data[8], &status_packet->roll, sizeof(int));
  memcpy(&an_packet->data[12], &status_packet->w_x, sizeof(int));
  memcpy(&an_packet->data[16], &status_packet->w_y, sizeof(int));
  memcpy(&an_packet->data[20], &status_packet->w_z, sizeof(int));
  memcpy(&an_packet->data[24], &status_packet->a_x, sizeof(int));
  memcpy(&an_packet->data[28], &status_packet->a_y, sizeof(int));
  memcpy(&an_packet->data[32], &status_packet->a_z, sizeof(int));
}

int decode_request_packet(unsigned char *id, an_packet_t *an_packet)
{
  if (an_packet->id == packet_id_request && an_packet->an_length == 1)
  {
    memcpy(id, &an_packet->data[0], sizeof(unsigned char));
    return 0;
  }
  else return 1;
}

