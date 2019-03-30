#include <wiringPi.h>	//-lwiringPi
#include <stdio.h>
#include <softPwm.h>	//-lpthread

#define SERVO 18


//Servo myservo;

int main(void){
	wiringPiSetupGpio();
	int pos = 90;

	printf("Starting now\n");

	pinMode(SERVO,PWM_OUTPUT);

	while(1){
		for(int i = 0;i<=1000;i=i+10){
			pwmWrite(SERVO,i);
			printf("%d\n",i);
			delay(100);
		}
	}

	return 0;
}

