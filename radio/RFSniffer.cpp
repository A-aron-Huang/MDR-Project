/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LED 29
#define PIN 2 //Receiver Pin

RCSwitch mySwitch;



int main(int argc, char *argv[]) {

	//Will use later to check for setup fail
    /* if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }*/

     int pulseLength = 0; //Start with a pulse length of 0
     if (argv[1] != NULL) //If received value is not null
		 pulseLength = atoi(argv[1]); //Convert string to int
	}

     mySwitch = RCSwitch(); //Create RCSwitch object
     if (pulseLength != 0){ //If int value is not 0
		 mySwitch.setPulseLength(pulseLength);
	}
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2

	pinMode(LED,OUTPUT);



     while(1) {

      if (mySwitch.available()) { //If read to read value

        int value = mySwitch.getReceivedValue();
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {
          	printf("Received %i\n", mySwitch.getReceivedValue() );
			if(mySwitch.getReceivedValue() == 1){
				digitalWrite(LED,HIGH);
				delay(1000);
				digitalWrite(LED,LOW);
			}
        }
		fflush(stdout); //Delete saved value
        mySwitch.resetAvailable(); //Now ready to accept new values
      }
      usleep(100); 
  
  }

  exit(0);


}

