#include <stdio.h>
#include <pthread.h>
#include "../gpiolib/gpio.h"
#include "../tcpserverlib/tcpserver.h"
#include "../udpsocketlib/udpsocket.h"

int main(int argc, char **argv)
{
	int tcp_tid = NULL;
	int udp_tid = NULL;

	printf("detective car is activited!\n");
	init_gpio(TURN_RIGHT_GPIO, 1, 0);
	init_gpio(TURN_LEFT_GPIO, 1, 0);
	init_gpio(GO_AHEAD_GPIO, 1, 0);
	init_gpio(GO_BACK_GPIO, 1, 0);
	set_gpio_level(TURN_RIGHT_GPIO, 1);
	
	udp_tid = startUDPBroadcast(8000);
	tcp_tid = create_tcp_server(0);
	pthread_join(&tcp_tid,NULL);
	return 0;
}
