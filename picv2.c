//
// gcc -o alarm alarm.c -L/usr/local/lib -lwiringPi
//

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>

void forkAndExecute (void) // Function, which is called on alarm
        {
        puts("Sensor triggered!");
        int pid = fork();               //fork
        if (pid == -1)
        {
            puts("raspistill fork error!!");         //check for fork failure
            return;
        }
        if (pid != 0) return;
        // If pid == 0, this is the child process.

        if (execlp("raspistill", "raspistill", "-n", "-hf", "-vf","-q", " 75", "-w", "1024", "-h", "768","-o", "forktestpic2.jpg", NULL) == -1)
        { //execlp does not return unless it fails.
            puts("raspistill error");
                exit(-1);
        }
    }

int main()
        {

        system("raspistill -o cam10.jpg");
//                printf("Activating sensor..\n");
 //                       if (wiringPiSetup() == -1)
//                      printf("Error setting up wiringPi\n");
//
  //              pinMode(0, INPUT);

                //Fork the picture taking process on interrupt
    //            wiringPiISR (0, INT_EDGE_RISING, forkAndExecute);
//
  //                      printf("Ready to go... \n");
    //            while(1)
      //                  sleep(360);


return 0;
}
