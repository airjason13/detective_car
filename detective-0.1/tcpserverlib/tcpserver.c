#include <pthread.h>
#include "tcpserver.h"

#define DEFAULT_SERV_PORT 5134


#define MAXNAME 1024

pthread_t tcp_tid = NULL;

extern int errno;

static int real_server_port;

static callback_t callbacks[CALLBACK_MAX] = {NULL};

static size_t n = 0;

void register_tcp(int func_num, callback_t callback){
	printf("%s\n", __func__);
	if(func_num >= CALLBACK_MAX){
		printf("callback functions full");
		return ;
	}
	if(callbacks[func_num] != NULL){
		printf("callback function is already assigned!\n");
	}
	callbacks[func_num] = callback;
}

void tcp_thread(void){
	int socket_fd;      /* file description into transport */
 	int recfd;     /* file descriptor to accept        */
 	int length;     /* length of address structure      */
 	int nbytes;     /* the number of read **/
 	char buf[BUFSIZ];
 	struct sockaddr_in myaddr; /* address of this service */
 	struct sockaddr_in client_addr; /* address of client    */
	printf("%s\n", __func__);
	/*                             
 	*      Get a socket into TCP/IP
 	*/
 	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
  		perror ("socket failed");
  		exit(1);
 	}
	/*
 	*    Set up our address
 	*/
	
 	bzero ((char *)&myaddr, sizeof(myaddr));
 	myaddr.sin_family = AF_INET;
 	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 	myaddr.sin_port = htons(real_server_port);

	/*
 	*     Bind to the address to which the service will be offered
 	*/
 	if (bind(socket_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) <0) {
  		perror ("bind failed");
  		exit(1);
 	}


	/*
 	* Set up the socket for listening, with a queue length of 5
 	*/
 	if (listen(socket_fd, 20) <0) {
  		perror ("listen failed");
 		 exit(1);
 	}
	/*
 	* Loop continuously, waiting for connection requests
 	* and performing the service
 	*/
 	length = sizeof(client_addr);
 	printf("Server is ready to receive !!\n");
 	printf("Can strike Cntrl-c to stop Server >>\n");
  	if ((recfd = accept(socket_fd, (struct sockaddr_in *)&client_addr, &length)) <0) {
   		perror ("could not accept call");
   		exit(1);
         }else{
		printf("tcpserver accept ok!\n");
	}

	printf("tcpserver ready to read commands!\n");
 	
	while (1) {
  		if ((nbytes = read(recfd, &buf, BUFSIZ)) < 0) {
   			perror("read of data error nbytes !");
  			close(recfd);
   			exit (1);
  		}
   
  		/*printf("Create socket #%d form %s : %d\n", recfd,
  		inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));*/
 	 	printf("%s\n", &buf);
	
		callbacks[CALLBACK_TCP_RECV_MSG](&buf);
 
  		/* return to client */
		sprintf(&buf, "ok\n");
  		if (write(recfd, &buf, nbytes) == -1) {
   			perror ("write to client error");
   			exit(1);
  		}
 	}
  	close(recfd);
}

pthread_t create_tcp_server(int port){

	printf("%s\n", __func__);	
	callbacks[CALLBACK_TCP_TEST]("test");
	if(port < 1024){
		printf("port: %d is not allowed,use default port : %d\n", port, DEFAULT_SERV_PORT);
		real_server_port = DEFAULT_SERV_PORT;
	}else{
		real_server_port = port;// = SERV_PORT;	
	}
	printf("real_server_port = %d\n", real_server_port);
	pthread_create(&tcp_tid, NULL, tcp_thread, NULL);
	return tcp_tid;
	
}
