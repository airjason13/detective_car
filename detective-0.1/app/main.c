#include <stdio.h>
#include "../gpiolib/gpio.h"

int main(int argc, char **argv)
{
	printf("detective car is activited!\n");
	init_gpio(TURN_RIGHT_GPIO, 1, 0);
	init_gpio(TURN_LEFT_GPIO, 1, 0);
	init_gpio(GO_AHEAD_GPIO, 1, 0);
	init_gpio(GO_BACK_GPIO, 1, 0);
	set_gpio_level(TURN_RIGHT_GPIO, 1);
	return 0;
}
