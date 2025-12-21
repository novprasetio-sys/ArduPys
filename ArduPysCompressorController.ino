const int pinMain = 13;
const int pinStar = 12;
const int pinDelta = 11;
const int btnOverload = 2;   // Pakai Pull-up Internal
const int btnPressure = 3;   // Pakai Pull-up Internal

enum State { OFF, STAR, DELTA, UNLOAD, OVERLOAD };
State currentState = OFF;

unsigned long startTime = 0;
const unsigned long starToDeltaDelay = 9000; 
bool lastBtnPressureState = HIGH; // Default HIGH untuk Pull-up

void allOff() {
  digitalWrite(pinMain, LOW);
  digitalWrite(pinStar, LOW);
  digitalWrite(pinDelta, LOW);
}

void startSequence() {
  currentState = STAR;
  startTime = millis();
  digitalWrite(pinMain, HIGH);
  digitalWrite(pinStar, HIGH);
  digitalWrite(pinDelta, LOW);
  Serial.println("STATUS:STAR_STARTING");
}

void setup() {
  Serial.begin(115200);
  pinMode(pinMain, OUTPUT);
  pinMode(pinStar, OUTPUT);
  pinMode(pinDelta, OUTPUT);
  
  // Mengaktifkan Pull-up Internal (Input aktif LOW)
  pinMode(btnOverload, INPUT_PULLUP);
  pinMode(btnPressure, INPUT_PULLUP);
  
  allOff();
}

void loop() {
  // 1. Cek Serial dari GUI
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "START" && (currentState == OFF || currentState == UNLOAD)) {
      startSequence();
    } else if (cmd == "RESET") {
      currentState = OFF;
      allOff();
      Serial.println("STATUS:READY_OFF");
    }
  }

  // 2. Simulasi Overload (LOW = Ditekan)
  if (digitalRead(btnOverload) == LOW) {
    if (currentState != OVERLOAD) {
      currentState = OVERLOAD;
      allOff();
      Serial.println("STATUS:ALARM_OVERLOAD");
    }
  }

  // 3. Logika Transisi Star ke Delta
  if (currentState == STAR) {
    if (millis() - startTime >= starToDeltaDelay) {
      currentState = DELTA;
      digitalWrite(pinStar, LOW);
      digitalWrite(pinDelta, HIGH);
      Serial.println("STATUS:DELTA_LOADING");
    }
  }

  // 4. Logika Tombol Pressure (Toggle Load/Unload)
  bool currentBtnPressure = digitalRead(btnPressure);
  
  // Deteksi Falling Edge (Dari HIGH ke LOW bearti tombol baru ditekan)
  if (currentBtnPressure == LOW && lastBtnPressureState == HIGH) {
    delay(50); // Debounce
    
    if (currentState == DELTA) {
      currentState = UNLOAD;
      allOff();
      Serial.println("STATUS:UNLOADING_IDLE");
    } 
    else if (currentState == UNLOAD) {
      startSequence(); // Restart urutan Star-Delta
    }
  }
  
  lastBtnPressureState = currentBtnPressure;
}