#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "com.h"
#include "an_packet_protocol.h"
#include "an_packets.h"
#include "usbdrive.h"

uint8_t rx_buffer[64] = {0};
uint16_t rx_ctr = 0;

void COM_packet_transmit(an_packet_t *an_packet);
void COM_packet_receive(an_packet_t *an_packet, unsigned char packet_length);
void COM_send_packet_acknowledge(an_packet_t an_packet_ack, uint8_t acknowledge_result);

void COM_init(long baudrate) {

	USBDRIVE_Init();
}

int COM_request_is_available() {

	if (USBDRIVE_DataIsAvailable() > 0)
		return TRUE;
	else
		return FALSE;
}

void COM_an_packet_transmit(an_packet_t *an_packet)
{
	an_packet_encode(an_packet);

	uint8_t buf[AN_MAXIMUM_PACKET_SIZE + AN_PACKET_HEADER_SIZE] = {0};

	for (int i = 0; i < AN_PACKET_HEADER_SIZE; i++)
		buf[i] = an_packet->header[i];

	for (int i = 0; i < an_packet->an_length; i++)
		buf[i + AN_PACKET_HEADER_SIZE] = an_packet->data[i];

	USBDRIVE_SendBuffer(buf, AN_PACKET_HEADER_SIZE + an_packet->an_length);

}

void COM_an_packet_receive(an_packet_t *an_packet, unsigned char packet_length)
{
	an_decoder_t an_decoder;

	an_decoder_initialise(&an_decoder);

	for (int i = 0; i < AN_PACKET_HEADER_SIZE + packet_length; i++)
		an_decoder.an_buffer[i] = rx_buffer[i];

	an_decoder.buffer_length = AN_PACKET_HEADER_SIZE + packet_length;

	an_packet_decode(&an_decoder, an_packet);
}

void COM_send_packet_acknowledge(an_packet_t an_packet_ack, uint8_t acknowledge_result) {
	an_packet_t an_packet;
	acknowledge_packet_t acknowledge_packet;

	uint8_t packet_id;
	uint16_t packet_crc;

	packet_id = an_packet_ack.id;
	memcpy(&packet_crc, &an_packet_ack.header[3], sizeof(uint16_t));

	acknowledge_packet.packet_id = packet_id;
	acknowledge_packet.packet_crc = packet_crc;
	acknowledge_packet.acknowledge_result = acknowledge_result;

	encode_acknowledge_packet(&an_packet, &acknowledge_packet);

	COM_an_packet_transmit(&an_packet);
}

void COM_send_status_packet(int yaw, int pitch, int roll,
		int w_x, int w_y, int w_z,
		int a_x, int a_y, int a_z) {

	an_packet_t an_packet;
	status_packet_t status_packet;

	status_packet.yaw = (int)yaw;
	status_packet.pitch = (int)pitch;
	status_packet.roll = (int)roll;
	status_packet.w_x = (int)w_x;
	status_packet.w_y = (int)w_y;
	status_packet.w_z = (int)w_z;
	status_packet.a_x = (int)a_x;
	status_packet.a_y = (int)a_y;
	status_packet.a_z = (int)a_z;

	encode_status_packet(&an_packet, &status_packet);

	COM_an_packet_transmit(&an_packet);
}

int COM_receive_request_packet(unsigned char *id) {

	an_packet_t an_packet;

	COM_an_packet_receive(&an_packet, 6);

	if (decode_request_packet(id, &an_packet) == 0)
		return 0;
	else
		return 1;
}

int COM_an_packet_receive_id(void)
{
	//Read byte if available in uart buffer:
	rx_ctr = USBDRIVE_ReceiveBuffer(rx_buffer) - 1;


	//If number of bytes collected correspond to expected number of bytes (indicated in packet header) -> go to packet analysis
	if (rx_buffer[2] != 0 && rx_buffer[2] == rx_ctr - AN_PACKET_HEADER_SIZE) {

		//Clean uart buffer:
		USBDRIVE_flush();

		//Reset counter:
		rx_ctr = 0;

		return rx_buffer[1];
	}
	else{
		USBDRIVE_flush();

		rx_ctr = 0;

		return -1;  //No packet ready
	}
}
