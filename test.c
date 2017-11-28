#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <math.h>
#include <softPwm.h>

#define ena1 5
#define ena2 6
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4


int main ()
{
	wiringPiSetup ();
	pinMode (pin1,OUTPUT);
    pinMode (pin2,OUTPUT);
	digitalWrite (pin1,HIGH);
	digitalWrite (pin2,LOW);
    pinMode (ena1,PWM_OUTPUT);
    pwmSetMode (PWM_MODE_MS);
    int  divisor;
    divisor = ((192000000)/(50*100));
    pwmSetClock (divisor);
    pwmSetRange (100);
    pwmWrite (ena1,100);
    
}

