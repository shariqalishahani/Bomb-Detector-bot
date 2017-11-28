#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include "distance.c"
//#include "servo1.c"
 #define range 400
//#include "rect.cpp"
const int f = 19200000
#define duty_cycle 100
#define desired 50
#define pin1 0
#define pin2 2
#define pin3 3
#define pin4 4
#define CTRL 0
#define CTRL1 7 
#define MAX 3
#define MIN 0.2
#define PERIOD 20
#define necheleft 25
#define necheright 135
#define straight 80

#define START 1000
#define RUN 600
#define STOP 1000

#define RIGHT 135
#define TOP 43
#define time 4000

#define STRAIGHT 80
#define LEFT 25
#define BOTTOM 0 
//neche wali
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace cv;
using namespace std;

Mat src;Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
//int main( int argc, char** argv )
void readImage(string image)
{
  /// Load source image and convert it to gray
  src = imread(image, 1 );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );// size (3,3)

  /// Create Window
  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );//cv_window_autosize, before
  imshow( source_window, src );

  createTrackbar( " Wayihaatpan:", source_window, &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
 // return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}

 void servoControl(int angle){
	float y;
	y = (((2.8/180)*angle) + 0.2)*1000;
	int i;
    for(i=0;i<=100;i++){

	digitalWrite(CTRL, HIGH);
	delayMicroseconds(y);
//    printf("High %f\n",y);
	digitalWrite(CTRL, LOW);
	delayMicroseconds((PERIOD*1000)-y);
  //  printf("Low %f\n",((PERIOD*1000)-y));
}
	}
    //upper wali
void servoControl1(int angle){
    float  y;
    y = (((2.8/180)*angle) + 0.2)*1000;
    int i;
    for(i=0;i<=100;i++){
        digitalWrite(CTRL1,HIGH);
        delayMicroseconds(y);
        digitalWrite(CTRL1,LOW);
        delayMicroseconds((PERIOD*1000)-y);
    }
}
void writeData (int servoNum, int angle){

	float y = (((2.8/180)*angle) + 0.2);
	int x = y*100;

	FILE *file = fopen("/dev/servoblaster","w");
	fprintf(file,"%d=%d\n",servoNum,x);
	fclose(file);

}
void rotate(int panangle,int tiltangle){
    writeData(0,tiltangle);
    writeData(1,panangle);
}
void speedControl(int servoNum,int currentPos,int endPos,int t){

  //  writeData(servoNum,currentPos);
    double pulses;


    int i;
    pulses = t*1000/20;
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
void moveServo(){
    servoControl(RIGHT);
    servoControl1(TOP);
    system("raspistill -vf -hf -w 640 -h 480 -t 1000  -o image1.jpg");
    readImage("image1.jpg");
    system(make);
    system(cmake .);

    delay(time);
    servoControl(STRAIGHT);
    servoControl1(BOTTOM);
    system("raspistill -vf -hf -w 640 -h 480 -t 1000 -o image2.jpg");
    readImage("image2.jpg");
    delay(time);
    servoControl(LEFT);
    servoControl1(TOP);
    system("raspistill -vf -hf -w 640 -h 480 -t 1000 -o image3.jpg");
    readImage("image3.jpg");
    delay(time);
    }
void motorON(){
    digitalWrite(25,HIGH);
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(3,LOW);
    }
void motorOFF(){
    digitalWrite(25,LOW);
    digitalWrite(4,LOW);
}
void speedControlPWM();
int drive(void){
	int i,j,k;
//    rotate(20,30);
for(k=0;k<=8;k++){
    for(i=0;i<=START;i++){
  // while(1){
        speedControlPWM();
//	int distance = getCM();
  
//    printf("%d\n",distance);
   if(i<RUN){
    motorON();
  
 }
   else if (i<STOP){

        motorOFF();
       
    }
   // servoControl(25);
    }
    moveServo();
    }
//  for (j=0;j<=START;j++){
//    speedControlPWM();
//    if(j<RUN){
 //       motorON();

  //      }
  //  else if(j<STOP){
    //    motorOFF();
  //      } 
  

//  }

}


void speedControlPWM(void){

    pinMode(1,PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(f/(desired*range));
    pwmSetRange(range);
    pwmWrite(1,duty_cycle);

}
void softPWM(void){
    pinMode(1,OUTPUT);
    softPwmCreate(1,0,200);
    softPwmWrite(1,duty_cycle);
}


int main(){
   wiringPiSetup();
   pinMode(25,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(3,OUTPUT);
pinMode(0,OUTPUT);
//digitalWrite(0,HIGH);
pinMode(7,OUTPUT);

//rotate(10,20);
//delay(2000);
//rotate(80,50);
//    setup();
   drive();
//  moveServo();
 // delay(1000);
//rotate(70,60);
 //  speedControlPWM();
 // softPWM();
//servoControl(20); //neche wali
//delay(3000);
//servoControl(60); //uper wali
//pinMode(0,OUTPUT);
//pinMode(2,OUTPUT);
//pinMode(3,OUTPUT);
//pinMode(4,OUTPUT);

//digitalWrite(0,HIGH);
//delay(100);
//digitalWrite(3,HIGH);
//delay(100);
//digitalWrite(2,HIGH);
//delay(100);
//digitalWrite(4,HIGH);
return 0;
}
