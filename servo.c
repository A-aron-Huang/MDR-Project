#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define SERVO 18

long map(long value, long fromLow,long fromHigh, long toLow, long toHigh){
	return (toHigh-toLow)*(value-fromLow)/(fromHigh-fromLow)+toLow;
}

void servoWrite(int angle){
	if(angle > 180){
		angle = 180;
	}
	if(angle < 0){
		angle = 0;
	}
	softPwmWrite(SERVO,map(angle,0,180,7,23));
}


int main(void){
	wiringPiSetupGpio();
	softPwmCreate(SERVO,0,200);

	while(1){
		printf("Clockwise\n");
		for(int i = 0;i<180;i+=2){
			servoWrite(i);
			delay(10);
		}
		printf("Counterclockwise\n");
		for(int i = 180;i>0;i-=2){
			servoWrite(i);
			delay(10);
		}
		printf("Finish, resting\n");
		delay(1000);
	}
	return 0;
}
