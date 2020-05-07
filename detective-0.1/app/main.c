#include <stdio.h>
#include <pthread.h>
#include "../gpiolib/gpio.h"
#include "../tcpserverlib/tcpserver.h"
#include "../udpsocketlib/udpsocket.h"


pthread_t main_tcp_tid = NULL;
pthread_t main_udp_tid = NULL;

void tcp_test(char *data){
	printf("%s\n", __func__);
	printf("data = %s\n", data);
}

void tcp_disconnect_notify(char *data){
	printf("%s\n", __func__);
	//pthread_cancel(main_tcp_tid);
	main_tcp_tid = create_tcp_server(0);
}

void get_tcp_client_ip(char *client_ipv4){
	printf("%s\n", __func__);
	printf("client_ipv4 = %s\n", client_ipv4);	
	char gst_cmd[512];
	sprintf(gst_cmd, "gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,framerate=20/1,width=640,height=480,format=YUY2 ! videoconvert ! omxh264enc ! rtph264pay ! udpsink host=%s port=6666&", client_ipv4);
	system(gst_cmd);
}

void motor_forward(void){
	set_gpio_level(GO_BACK_GPIO, 0);
	set_gpio_level(GO_AHEAD_GPIO, 1);
}
void motor_backward(void){
	set_gpio_level(GO_AHEAD_GPIO, 0);
	set_gpio_level(GO_BACK_GPIO, 1);
}
void motor_forward_stop(void){
	set_gpio_level(GO_BACK_GPIO, 0);
	set_gpio_level(GO_AHEAD_GPIO, 0);
}
void motor_left(void){
	set_gpio_level(TURN_RIGHT_GPIO, 0);
	set_gpio_level(TURN_LEFT_GPIO, 1);
}
void motor_right(void){
	set_gpio_level(TURN_LEFT_GPIO, 0);
	set_gpio_level(TURN_RIGHT_GPIO, 1);
}
void motor_direct_stop(void){
	set_gpio_level(TURN_LEFT_GPIO, 0);
	set_gpio_level(TURN_RIGHT_GPIO, 0);
}

void tcp_recv_data(char *data){
	printf("%s\n", __func__);
	printf("data = %s\n", data);
	if(!strcmp(data,"forward")){
		motor_forward();
	}else if(!strcmp(data,"backward")){
		motor_backward();
	}else if(!strcmp(data,"forward_stop")){
		motor_forward_stop();
	}else if(!strcmp(data,"left")){
		motor_left();
	}else if(!strcmp(data,"right")){
		motor_right();
	}else if(!strcmp(data,"direct_stop")){
		motor_direct_stop();
	}	
}
int main(int argc, char **argv)
{
	printf("detective car is activited!\n");
	init_gpio(TURN_RIGHT_GPIO, 1, 0);
	init_gpio(TURN_LEFT_GPIO, 1, 0);
	init_gpio(GO_AHEAD_GPIO, 1, 0);
	init_gpio(GO_BACK_GPIO, 1, 0);
//	set_gpio_level(TURN_RIGHT_GPIO, 1);
	
	register_tcp(CALLBACK_TCP_RECV_MSG,&tcp_recv_data);
	register_tcp(CALLBACK_TCP_GET_CLIENT_IPV4,&get_tcp_client_ip);
	register_tcp(CALLBACK_TCP_TEST,&tcp_test);
	register_tcp(CALLBACK_TCP_DISCONNECT,&tcp_disconnect_notify);


	main_udp_tid = startUDPBroadcast(8000);
	main_tcp_tid = create_tcp_server(0);
	while(1){
		sleep(2);
	}
	return 0;
}
