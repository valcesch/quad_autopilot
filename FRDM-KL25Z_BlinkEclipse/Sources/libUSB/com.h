#ifndef COM_H_
#define COM_H_

void COM_init(long baudrate);
int COM_request_is_available();
void COM_send_status_packet(int yaw, int pitch, int roll,
		int w_x, int w_y, int w_z,
		int a_x, int a_y, int a_z);
int COM_receive_request_packet(unsigned char *id);
int COM_an_packet_receive_id(void);

#endif
