#include <stdio.h>
#include "gpio.h"


int gpio_export(int pin)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

int gpio_unexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

int gpio_direction(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";

#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

int gpio_read(int pin)
{
#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}

	close(fd);

	return(atoi(value_str));
}

int gpio_write(int pin, int value)
{
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}


int set_gpio_level(int gpio_num, int gpio_level){
	return gpio_write(gpio_num, gpio_level);	
}

int init_gpio(int gpio_num, int gpio_dir, int gpio_level){
		
	gpio_export(gpio_num);
	gpio_direction(gpio_num, gpio_dir);
	gpio_write(gpio_num, gpio_level);	
	
	return 0;	
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

