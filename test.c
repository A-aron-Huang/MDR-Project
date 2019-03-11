#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define STBY 21 //Motor Driver, to even start STBY must be on

#define PWMA 15 //Left Motor Controls
#define AIN1 3
#define AIN2 4

int main(){

	int stby;
	int pwma;
	int ain1;
	int ain2;

	int val = 100;

	wiringPiSetupGpio(); //Use pin numbering

	pinMode(STBY, OUTPUT); //STBY pin to turn on
 	digitalWrite(STBY,HIGH);

	pinMode(AIN1,OUTPUT);
	pinMode(AIN2,OUTPUT);

	//Testing with soft PWM - works with gpio 18
	softPwmCreate(PWMA,0,100);
	softPwmWrite(PWMA,0);

	//Testiog with actual PWM lirbabry - works with gpio 18
//	pinMode(PWMA,PWM_OUTPUT);
//	pwmWrite(PWMA,0);

	//Testing with analog - nope
//	pinMode(PWMA,OUTPUT);
//	analogWrite(PWMA,0);

	//Testing with digital - Def not even if it did work
//	pinMode(PWMA,OUTPUT);
//	digitalWrite(PWMA,LOW);


	printf("Starting Now\n");
	while(1){
		softPwmWrite(PWMA,0); //Motor A stopped, as no keys pressed
		digitalWrite(AIN1,LOW);
		digitalWrite(AIN2,LOW);
		printf("Done Setting Up\n");
		delay(100);

		printf("Should be going forward now\n");
		digitalWrite(STBY,HIGH);
		digitalWrite(AIN1,HIGH);
		softPwmWrite(PWMA,50);
		//pwmWrite(PWMA,1000);
		//analogWrite(PWMA,1000);
		delay(5000);




		stby=digitalRead(STBY);
		pwma=analogRead(PWMA);
		ain1=digitalRead(AIN1);
		ain2=digitalRead(AIN2);
		printf("STBY: %d, PWMA: %d, AIN1: %d, AIN2: %d\n",stby,pwma,ain1,ain2);

	}
	return 0;
}
