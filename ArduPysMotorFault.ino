int butt1 = 2;
int butt2 = 3;
int butt3 = 4;
int state1;
int state2;
int state3;
void setup() {
Serial.begin(9600);
pinMode(butt1,INPUT_PULLUP);
pinMode(butt2,INPUT_PULLUP);
pinMode(butt3,INPUT_PULLUP);
}
void loop() {
state1 = digitalRead(butt1);
state2 = digitalRead(butt2);
state3 = digitalRead(butt3);
if (state1 == LOW){
  Serial.println("motor1 bermasalah");
}
if (state2 == LOW){
  Serial.println("motor2 bermasalah");
}
if (state3 == LOW){
  Serial.println("motor3 bermasalah");
}
delay(100);
}