#include <Servo.h>
Servo myservo; 
int pir = 2; 
int led = 4; 
int val;
int door;    
void setup() {
	myservo.attach(3);
	pinMode(pir, INPUT); 
	pinMode(led, OUTPUT);  
}
void loop() {
	val = digitalRead(pir); 
	if (val == LOW){
		digitalWrite(led, HIGH);         
		myservo.write(0);
		door = 1;
		delay(5000); 
	}
	else { 
		digitalWrite(led,LOW);
		myservo.write(90);
		door = 0;
	}                 
	delay(15);                           
}