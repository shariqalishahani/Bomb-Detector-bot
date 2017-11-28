#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define pin1 0
#define pin3 7
#define pin2 2
int angle (int ang)
{
//	pwmSetMode (PWM_MODE_MS);
//	pwmSetClock (38400);
//	pwmSetRange (100);

/*	while(ang == 0){
		digitalWrite (pin3,HIGH);
        delayMicroseconds(500);
        printf ("HEll");
        digitalWrite (pin3,LOW);
        delayMicroseconds (19500);
     printf("hhehjeje\n");
	}
	else if (ang == 90){
		digitalWrite (pin1,HIGH);
      delayMicroseconds(1.5);
        digitalWrite (pin1,LOW);
        delayMicroseconds (18.5);
        printf("sda");
	}
    else if (ang == 180){
		digitalWrite (pin1, HIGH);
        delayMicroseconds(2.5);
        digitalWrite (pin1, LOW);
      delayMicroseconds(17.5);
       printf("asdsad");
	}*/
   while (1){
        float y;
		y = ((2.0/180.0)*ang)+0.5;
	    digitalWrite(pin1,HIGH);
	    delayMicroseconds(y);
	    digitalWrite(pin1,LOW);
	    delayMicroseconds ((20-y));
//        printf("tatat");
	}
}


int  servo (int sno, int dest)
{   

    double pwmTime = ((((2.0/180.0)*(double)dest)+0.5)*100);
	FILE *file;
	file = fopen("/dev/servoblaster","a+");
	
	fprintf (file,"%d=%d\n",sno, (int)pwmTime);
	printf ("%d\n",(int)dest);
	fclose (file);	
}


int camangle ( float pan, float tilt)
{
	servo (0,pan );
	servo (1, tilt);
}

int speed (int servonos, float curpos, float destpos, float time)
{
	servo (servonos, curpos);
	//float pulse,currtime,endtime,i;
	double pulse = (time/20.0)*1000;
	//currtime = (((2/180)*curpos)+ 0.5);
	//float t = currtime;
	//endtime = (((2/180)*destpos)+ 0.5);
	float i = (destpos - curpos)/pulse;
	float x = curpos;
	for (x; x < destpos; x+=i){
		servo(servonos,x);
		//t = t + i;
		delay (20);
	}
 } 


int main ()
{
	wiringPiSetup();
	pinMode (pin1,OUTPUT);
    pinMode (pin2,OUTPUT);
    pinMode (pin3,OUTPUT);
	//angle (0);
    speed (1,120,180,5);
   // speed(1,20,60,2);
    //servo(0, 180);
   //camangle (0,0);  
}
