int trig = 3;
int echo = 2;
int led = 13;
long durasi, jarak; 
void setup(){ 
 pinMode(trig, OUTPUT); 
 pinMode(echo, INPUT);
 pinMode(led, OUTPUT);
 Serial.begin(9600);
 }
void loop() { 
digitalWrite(trig, LOW); 
delayMicroseconds(8); 
digitalWrite(trig, HIGH); 
delayMicroseconds(8); 
digitalWrite(trig, LOW); 
delayMicroseconds(8); 
durasi = pulseIn(echo, HIGH);
jarak = (durasi / 2) / 29.1; 
Serial.println(jarak); 
delay(1000);
if (jarak <= 10){
  digitalWrite(led, HIGH);
  }
else {
  digitalWrite(led, LOW);
  }
}