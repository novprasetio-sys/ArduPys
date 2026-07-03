int trig = 6;
int echo = 5;
int led = 13;
long durasi,jarak;
void setup(){ 
 pinMode(trig, OUTPUT); 
 pinMode(echo, INPUT);
 pinMode(led, OUTPUT);
 digitalWrite(led, HIGH);
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
if (jarak <= 10){
  digitalWrite(led, LOW);
  }
else {
  digitalWrite(led, HIGH);
  }
delay(100);
}