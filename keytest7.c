/*Notes:
 *Add check for wiringpi setup
 *
 *
 */

//Libraries
#include <ncurses.h>	//For keyboard commands
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#define OFFSET_MS 3     //Define the unit of servo pulse offset: 0.1ms
#define SERVO_MIN_MS 10-OFFSET_MS        //define the pulse duration for minimum angle of servo
#define SERVO_MAX_MS 20+OFFSET_MS       //define the pulse duration for maximum angle of servo

//Constants
#define servoPin    18       //define the GPIO number connected to servo


//Functions
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}
void servoInit(int pin){        //initialization function for servo PMW pin
    softPwmCreate(pin,  0, 200);
}
void servoWrite(int pin, int angle){    //Specif a certain rotation angle (0-180) for the servo
    if(angle > 180)
        angle = 180;
    if(angle < 0)
        angle = 0;
    softPwmWrite(pin,map(angle,0,180,SERVO_MIN_MS,SERVO_MAX_MS));   
}
void servoWriteMS(int pin, int ms){     //specific the unit for pulse(5-25ms) with specific duration output by servo pin: 0.1ms
    if(ms > SERVO_MAX_MS)
        ms = SERVO_MAX_MS;
    if(ms < SERVO_MIN_MS)
        ms = SERVO_MIN_MS;
    softPwmWrite(pin,ms);
}

int main(){
int ch;
int i;
    if(wiringPiSetupGpio() == -1){ //when initialize wiring faiservo,print messageto screen
        printf("setup wiringPi faiservo !");
        return 1; 
    }
    printw("Program is starting ...\n");
    servoInit(servoPin);        //initialize PMW pin of servo
	
	
	
	initscr(); //Intilaizing keypressing
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE); //ch will be 'ERR' if no character clicked


	//Finish Setting Up
	printw("Starting Now - Press 'q' to Quit\n");
	while((ch = getch()) != 'q'){
        for(i=15;i<SERVO_MAX_MS;i++){  //make servo rotate from minimum angle to maximum angle
            servoWriteMS(servoPin,i);
            delay(100);
        }
        delay(500);
        for(i=SERVO_MAX_MS;i>SERVO_MIN_MS;i--){  //make servo rotate from maximum angle to minimum angle
            servoWriteMS(servoPin,i);
            delay(100);
        }
		for(i=SERVO_MIN_MS;i<15;i++){
			servoWriteMS(servoPin,i);
			delay(100);
		}
		servoWriteMS(servoPin,15);
		if(ch == KEY_DOWN){
			servoWriteMS(ServoPin,10);
		}
		
        delay(5000);
	}


	
	//While loop has been exited
	printw("\nBye Now!\n"); //Deintialize keypressing
	refresh();
	getch();
	endwin();
	return 0;
}
