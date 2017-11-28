#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include "distance.c"

//using namespace cv;
using namespace std;

#include <ctime>
#include <iostream>
#include "raspicam_cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define range 400
#define f 19200000
#define duty_cycle 100
#define desired 50
#define pin1 0
#define pin2 2
#define pin3 3
#define pin4 4
int drive(void);
void speedControlPWM();
void softPWM(void);
int main(){
   wiringPiSetup();
   pinMode(25,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(3,OUTPUT);


    setup();
    drive();

 //  speedControlPWM();
 // softPWM();

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
}
int drive(void){
	int i;
    for(i=0;i<=4000;i++){
  // while(1){
        speedControlPWM();
	int distance = getCM();

    printf("%d\n",distance);
   if(i<200){

    digitalWrite(25,HIGH);

    digitalWrite(2,LOW);

    digitalWrite(4,HIGH);

    digitalWrite(3,LOW);
 }

   // delay(2000);
   else if (i<3000){
        int threshold = 100;
   
   const int frameDelay = 100, maxContours = 500;
    
    raspicam::RaspiCam_Cv cam;
    Mat image;
    cam.set(CV_CAP_PROP_FORMAT, CV_8UC1);
    if (!cam.open())
        return 1;
    
    const char szSourceWindow[] = "Source", szContoursWindow[] = "Contours";
    namedWindow(szSourceWindow, WINDOW_AUTOSIZE);
    namedWindow(szContoursWindow, WINDOW_AUTOSIZE);
    createTrackbar("Threshold:", szSourceWindow, &threshold, 255, NULL);
 
    for (;;)
    {
        RNG rng(12345);
        cam.grab();
        cam.retrieve(image);
        Mat smallImage;
        resize(image, smallImage, Size(), 0.5, 0.5);
        imshow(szSourceWindow, smallImage);
        
        Mat canny_output;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        Canny(smallImage, canny_output, threshold, threshold * 2, 3);
        findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
 
        Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
        for (size_t i = 0; i < std::min(contours.size(), (size_t)maxContours); i++)
        {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
        }
 
        imshow(szContoursWindow, drawing);
        waitKey(frameDelay);
    }
    cam.release();
        digitalWrite(25,LOW);

        digitalWrite(4,LOW);
    }
    else if (i<3200){

    digitalWrite(25,HIGH);

    digitalWrite(2,LOW);

    digitalWrite(4,HIGH);

    digitalWrite(3,LOW);
}
    else if(i>3500){

        digitalWrite(25,LOW);

        digitalWrite(4,LOW);

}
}
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


