#include <stdint.h>
#include <string.h>
#include <stdint.h>

#include "an_packet_protocol.h"
#include "crc.h"

/*
   Function to calculate crc16 over provided table
*/
uint16_t calculate_crc16(uint8_t *data, uint16_t an_length)
{
  uint8_t *bytes = (uint8_t *) data;

  CRC_Init();
  uint16_t syndrome = 0xFFFF;
  uint16_t crc = 0x0000;
  uint16_t i = 0;

  for (i = 0; i < an_length; i++)
  {
    crc = CRC_Optimized((uint8_t)bytes[i], syndrome);
  }
  return crc;
}

/*
   Function to calculate a 4 byte LRC
*/
uint8_t calculate_header_lrc(uint8_t *data)
{
  return ((data[0] + data[1] + data[2] + data[3]) ^ 0xFF) + 1;
}

/*
   Initialise the decoder
*/
void an_decoder_initialise(an_decoder_t *an_decoder)
{
  an_decoder->buffer_length = 0;
  an_decoder->crc_errors = 0;
}

/*
   Function to decode an_packets from raw data
   To fill buffer set an_packet to NULL
   To decode packets set buffer to NULL and buffer_length to zero
   returns TRUE (1) if a packet was decoded or FALSE (0) if no packet was decoded
*/
uint8_t an_packet_decode(an_decoder_t *an_decoder, an_packet_t *an_packet)
{
  uint16_t decode_iterator = 0;
  uint8_t packet_decoded = FALSE;
  uint8_t header_lrc;
  uint16_t crc;

  while (decode_iterator + AN_PACKET_HEADER_SIZE <= an_decoder->buffer_length)
  {
    header_lrc = an_decoder->an_buffer[decode_iterator++];
    if (header_lrc == calculate_header_lrc(&an_decoder->an_buffer[decode_iterator]))
    {
      an_packet->id = an_decoder->an_buffer[decode_iterator++];
      an_packet->an_length = an_decoder->an_buffer[decode_iterator++];
      crc = an_decoder->an_buffer[decode_iterator++];
      crc |= an_decoder->an_buffer[decode_iterator++] << 8;

      if (decode_iterator + an_packet->an_length > an_decoder->buffer_length)
      {
        decode_iterator -= AN_PACKET_HEADER_SIZE;
        break;
      }

      if (crc == calculate_crc16(&an_decoder->an_buffer[decode_iterator], an_packet->an_length))
      {
        packet_decoded = TRUE;
        memcpy(an_packet->header, &an_decoder->an_buffer[decode_iterator - AN_PACKET_HEADER_SIZE], AN_PACKET_HEADER_SIZE * sizeof(uint8_t));
        memcpy(an_packet->data, &an_decoder->an_buffer[decode_iterator], an_packet->an_length * sizeof(uint8_t));
        decode_iterator += an_packet->an_length;
        break;
      }
      else
      {
        decode_iterator -= (AN_PACKET_HEADER_SIZE - 1);
        an_decoder->crc_errors++;
      }
    }
  }
  if (decode_iterator < an_decoder->buffer_length)
  {
    if (decode_iterator > 0)
    {
      memmove(&an_decoder->an_buffer[0], &an_decoder->an_buffer[decode_iterator], (an_decoder->buffer_length - decode_iterator) * sizeof(uint8_t));
      an_decoder->buffer_length -= decode_iterator;
    }
  }
  else an_decoder->buffer_length = 0;

  return packet_decoded;
}

/*
   Function to encode an an_packet
*/
void an_packet_encode(an_packet_t *an_packet)
{
  uint16_t crc;
  an_packet->header[1] = an_packet->id;
  an_packet->header[2] = an_packet->an_length;
  crc = calculate_crc16(an_packet->data, an_packet->an_length);
  memcpy(&an_packet->header[3], &crc, sizeof(uint16_t));
  an_packet->header[0] = calculate_header_lrc(&an_packet->header[1]);
}
