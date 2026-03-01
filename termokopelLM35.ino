// =====================
// PIN SETUP
// =====================
#define SENSOR_PIN A0
#define LED_PIN    2

// =====================
// VARIABLE
// =====================
int adcValue = 0;
float voltage = 0.0;
float temp = 0.0;

// =====================
// SETUP
// =====================
void setup() {

  Serial.begin(9600);
  Serial.println("=== SIMULASI LM35 - ADC SLIDER ===");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // default ON
}

// =====================
// LOOP
// =====================
void loop() {

  // Baca nilai ADC
  adcValue = analogRead(SENSOR_PIN);

  // Konversi ADC -> Voltage
  voltage = (adcValue / 1023.0) * 5.0;

  // Konversi Voltage -> Temperature (LM35)
  temp = (voltage * 1000.0) / 10.0;

  // Tampilkan ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | Temp: ");
  Serial.print(temp);
  Serial.println(" C");

  // Logic kontrol LED
  if (temp >= 30) {
    digitalWrite(LED_PIN, LOW);   // LED OFF
  } 
  else {
    digitalWrite(LED_PIN, HIGH);  // LED ON
  }

  delay(500);
}