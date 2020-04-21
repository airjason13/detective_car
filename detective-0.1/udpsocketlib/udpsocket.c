#include "udpsocket.h"

int sockfd;
struct sockaddr_in server_addr, client_addr;
int so_broadcast = 1;
//char buf[1024] = {1};
pthread_t broadcast_tid = NULL;
int clientlen = 0;
struct sockaddr_in broadcast_addr;
int addr_len;


void broadcast_thread(void){
	printf("ready to broadcsat!\n");
	char *buf = "good to go!";
	printf("strlen(buf) = %d\n", strlen(buf));	
	while(1){
		if((sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&broadcast_addr, (socklen_t)addr_len)) < 0){
			
   			perror("sendto");
  	 		return -1;
  		}
		usleep(2); 
	}
}

int startUDPBroadcast(int port){
	if(port < 1024){
		printf("port error!\n");
	}
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror ("socket failed!");
                exit(1);
        }
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast))<0){
  		perror("setsockopt");
		return -1;
 	}
	
	addr_len = sizeof(struct sockaddr_in);

  	memset((void*)&broadcast_addr, 0, addr_len);
  	broadcast_addr.sin_family = AF_INET;
  	broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  	broadcast_addr.sin_port = htons(port);

	pthread_create(&broadcast_tid, NULL, broadcast_thread, NULL);
	return broadcast_tid;
}
