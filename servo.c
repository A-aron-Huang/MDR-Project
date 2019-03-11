#include <wiringPi.h>
#include <stdio.h>

int main(void){
	wiringPiSetupGpio();
	pinMode(18,PWM_OUTPUT);
	int val = 75;

/*	printf("Starting now\n");
	pwmWrite(18,val);
	delay(30000); //30sec
	printf("Ending now\n");*/
while(1){
for(int i = 0;i<=1025;i++){
	pwmWrite(18,i);
	printf("%d\n",i);
	delay(100);
}
for(int i = 1025;i>=0;i--){
	pwmWrite(18,i);
	printf("%d\n",i);
	delay(100);
}
}


	while(1){
		printf("Right");
		pwmWrite(18,val-(val/2)); //138-140 bigger the number more CW speed
		delay(1000);
		printf("Left");
		pwmWrite(18,val+(val/2));
		delay(1000);

/*		for(int val = 525;val < 1024;val = val+10){
			printf("%d\n",val);
			pwmWrite(18,val);
			delay(1000);
		}*/
	}
	return 0;
}
