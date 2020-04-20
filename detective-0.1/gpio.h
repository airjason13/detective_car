#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define TURN_RIGHT_GPIO		17
#define TURN_LEFT_GPIO		18

#define GO_AHEAD_GPIO		22
#define GO_BACK_GPIO		23

int init_gpio(int gpio_num, int gpio_dir, int gpio_level);
int set_gpio_high(int gpio_num, int gpio_level);
