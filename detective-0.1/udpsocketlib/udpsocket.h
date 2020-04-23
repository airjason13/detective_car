#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/errno.h>
#include <string.h>
#include <arpa/inet.h>

int startUDPBroadcast(int port);
