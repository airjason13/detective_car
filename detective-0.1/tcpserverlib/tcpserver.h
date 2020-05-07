#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <pthread.h>
#include <stdbool.h>
typedef void (*callback_t)(char*);

#define CALLBACK_TCP_RECV_MSG   	0
#define CALLBACK_TCP_DISCONNECT 	1
#define CALLBACK_TCP_RECV_MSG   	2
#define CALLBACK_TCP_GET_CLIENT_IPV4   	3
#define CALLBACK_TCP_TEST       	4

#define CALLBACK_MAX 10

void register_tcp(int func_num, callback_t callback);

pthread_t create_tcp_server(int port);
