#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define CTRL 1
#define MAX 3
#define MIN 0.2
#define PERIOD 20

 void servoControl(int angle){
	float y;
	y = (((2.8/180)*angle) + 0.2)*1000;


	while(1){

	digitalWrite(CTRL, HIGH);
	delayMicroseconds(y);
	digitalWrite(CTRL, LOW);
	delayMicroseconds((PERIOD*1000)-y);

}
	}

void writeData (int servoNum, int angle){

	float y = (((2.8/180)*angle) + 0.2);
	int x = y*100;

	FILE *file = fopen("/dev/servoblaster","a+");
	fprintf(file,"%d=%d\n",servoNum,x);
	fclose(file);

}
void rotate(int panangle,int tiltangle){
    writeData(0,tiltangle);
    writeData(1,panangle);
}
void speedControl(int servoNum,int currentPos,int endPos,int time){

  //  writeData(servoNum,currentPos);
    double pulses;


    int i;
    pulses = time*1000/20;
    double postTime;
 //   double startTime = (((2.8/180)*currentPos)+0.2)*1000;

  //  double endTime = (((2.8/180)*endPos)+0.2)*1000;

   // double posTime = endTime - startTime;
   if(endPos< currentPos){
     postTime =  currentPos - endPos;
    }
    if (endPos>currentPos){
         postTime = endPos - currentPos;
    }
	double increments =  postTime/pulses;



   for(i = 0;i<pulses;i++){
        writeData(servoNum,currentPos);
        if (currentPos < endPos){
             currentPos=increments + currentPos;
             delay(20);
        }
        if (currentPos > endPos) {
            currentPos = currentPos - increments;
        }
   }
}

int main(){

	wiringPiSetup();

//	writeData(0,50);//Uper walee Connected to tilt angle and p1-7
//	writeData(1,20);//neeche walee connected pan angle and p1-11
//	pinMode(CTRL, OUTPUT);
    rotate(20,30);
//	servoControl(150);
////	speedControl(0,10,80,1);
////	speedControl(0,50,20,10);
	return 0;
}
