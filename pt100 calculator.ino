const int sensorPin = A0;  // Pin input analog
const int motorPin = 9;  // Pin output motor
const int ledPin = 8;    // Pin output LED

float VCC = 5.0;  // Tegangan referensi
float tempThreshold = 95.0;  // Batas suhu cut-off

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(sensorPin);

  // Konversi ADC ke tegangan
  float voltage = (adcValue / 1023.0) * VCC;

  // Konversi tegangan ke suhu
  float temperature = (voltage * 260) - 650;

  // Tampilkan hasil di serial monitor
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Tegangan (V): ");
  Serial.print(voltage);
  Serial.print(" | Suhu (°C): ");
  Serial.println(temperature);

  // Logika kontrol output
  if (temperature <= tempThreshold) {
    digitalWrite(motorPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(motorPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500);  // Delay setengah detik sebelum pembacaan berikutnya
}