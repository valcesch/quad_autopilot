#ifndef __AN_PACKET_PROTOCOL_H
#define __AN_PACKET_PROTOCOL_H

#include <stdint.h>

#define AN_PACKET_HEADER_SIZE 5
#define AN_MAXIMUM_PACKET_SIZE 64
#define AN_DECODE_BUFFER_SIZE 2*(AN_MAXIMUM_PACKET_SIZE + AN_PACKET_HEADER_SIZE)
#define AN_DECODE_MAXIMUM_FILL_SIZE (AN_MAXIMUM_PACKET_SIZE + AN_PACKET_HEADER_SIZE)
#define an_packet_pointer(packet) (packet)->header
#define an_packet_size(packet) ((packet)->an_length + AN_PACKET_HEADER_SIZE)*sizeof(uint8_t)

#define an_decoder_pointer(an_decoder) &(an_decoder)->an_buffer[(an_decoder)->buffer_length]
#define an_decoder_size(an_decoder) (sizeof((an_decoder)->an_buffer) - (an_decoder)->buffer_length)
#define an_decoder_increment(an_decoder, bytes_received) (an_decoder)->buffer_length += bytes_received

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

typedef struct
{
	uint8_t an_buffer[AN_DECODE_BUFFER_SIZE];
	uint16_t buffer_length;
	uint32_t crc_errors;
} an_decoder_t;

typedef struct
{
    uint8_t id;
    uint8_t an_length;
    uint8_t header[AN_PACKET_HEADER_SIZE];
    uint8_t data[AN_MAXIMUM_PACKET_SIZE];
} an_packet_t;

void an_decoder_initialise(an_decoder_t *an_decoder);
uint8_t an_packet_decode(an_decoder_t *an_decoder, an_packet_t *an_packet);
void an_packet_encode(an_packet_t *an_packet);

#endif
