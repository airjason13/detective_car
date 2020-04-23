#include <stdio.h>
#include <pthread.h>
#include "../gpiolib/gpio.h"
#include "../tcpserverlib/tcpserver.h"
#include "../udpsocketlib/udpsocket.h"


void tcp_test(char *data){
	printf("%s\n", __func__);
	printf("data = %s\n", data);
}

void tcp_recv_data(char *data){
	printf("%s\n", __func__);
	printf("data = %s\n", data);
	
}


int main(int argc, char **argv)
{
	pthread_t tcp_tid = NULL;
	pthread_t udp_tid = NULL;


	
	printf("detective car is activited!\n");
	init_gpio(TURN_RIGHT_GPIO, 1, 0);
	init_gpio(TURN_LEFT_GPIO, 1, 0);
	init_gpio(GO_AHEAD_GPIO, 1, 0);
	init_gpio(GO_BACK_GPIO, 1, 0);
	set_gpio_level(TURN_RIGHT_GPIO, 1);
	
	register_tcp(CALLBACK_TCP_RECV_MSG,&tcp_recv_data);
	register_tcp(CALLBACK_TCP_TEST,&tcp_test);

	udp_tid = startUDPBroadcast(8000);
	tcp_tid = create_tcp_server(0);
	while(1){
		sleep(2);
	}
	return 0;
}
