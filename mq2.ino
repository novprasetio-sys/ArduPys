// Arduino Codes

void setup() {
  Serial.begin(9600);
}

void loop() {
  int mq = analogRead(A0);     // baca MQ-2 (0–1023 untuk Arduino)
  Serial.println(mq);          // kirim ke PC via serial
  delay(200);                  // 5 sampel per detik
}