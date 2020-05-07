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
int set_gpio_level(int gpio_num, int gpio_level);

void motor_forware(void);
void motor_backward(void);
void motor_forward_stop(void);
void motor_left(void);
void motor_right(void);
void motor_direct_stop(void);
