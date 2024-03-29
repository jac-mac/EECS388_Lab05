#include <stdio.h>
#include <stdint.h>

#include "eecs388_lib.h"

#define SERVO_PULSE_MAX 2400    /* 2400 us */
#define SERVO_PULSE_MIN 544     /* 544 us */
#define SERVO_PERIOD    20000   /* 20000 us (20ms) */

/**
 * Generate a pwm signal
 * 
 * Input:
 *  @gpio   gpio number
 *  @pos    degree [0,180]
 */
void servo(int gpio, int pos)
{
    
    int duty_time = (pos * (SERVO_PULSE_MAX-SERVO_PULSE_MIN)) / 180;
    int duty_usec = duty_time + SERVO_PULSE_MIN;
    gpio_write(gpio, ON);
    delay_usec(duty_usec);

    int remainingTime = SERVO_PERIOD-duty_usec;
    gpio_write(gpio, OFF);
    delay_usec(remainingTime);
}

int main()
{
    int gpio = PIN_19;
    gpio_mode(gpio, OUTPUT);

    while (1) {
        for (int pos = 0; pos <= 180; pos += 30) {
            printf("pos: %d (degree)\n", pos);
            /* control the servor for 1 sec duration */
            for (int i = 0; i < 50; i++)
                servo(gpio, pos);
        }
    }
}