// =====================
// PIN SETUP
// =====================
#define BTN_ON       7
#define BTN_OFF      8
#define BTN_OVERLOAD 9
//=======================================
// di rangkaian nyata button bisa diganti overload kontak NO 97 & 98
//=======================================
#define OUT_RUN      2
#define OUT_STAR     3
#define OUT_DELTA    4
#define BUZZER       5

// =====================
// VARIABLE
// =====================
bool motorRunning = false;
bool overloadTrip = false;

unsigned long starStartTime = 0;
unsigned long starDuration = 5000; // 5 detik star

int state = 0; 
// 0 = OFF
// 1 = STAR
// 2 = DELTA

// =====================
// SETUP
// =====================
void setup() {

  Serial.begin(9600);
  Serial.println("=== SISTEM STAR-DELTA SIAP ===");

  pinMode(BTN_ON, INPUT_PULLUP);
  pinMode(BTN_OFF, INPUT_PULLUP);
  pinMode(BTN_OVERLOAD, INPUT_PULLUP);

  pinMode(OUT_RUN, OUTPUT);
  pinMode(OUT_STAR, OUTPUT);
  pinMode(OUT_DELTA, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(OUT_RUN, LOW);
  digitalWrite(OUT_STAR, LOW);
  digitalWrite(OUT_DELTA, LOW);
  digitalWrite(BUZZER, LOW);
}

// =====================
// LOOP
// =====================
void loop() {

// inisiasi fungsi tombol jika ditekan memberikan logic LOW

  bool onPressed       = digitalRead(BTN_ON) == LOW;
  bool offPressed      = digitalRead(BTN_OFF) == LOW;
  bool overloadPressed = digitalRead(BTN_OVERLOAD) == LOW;

  // =====================
  // OVERLOAD LOGIC
  // =====================
  if (overloadPressed && !overloadTrip) {
    overloadTrip = true;
    Serial.println("!!! OVERLOAD TERDETEKSI !!!");
  }

  if (overloadTrip) {
    digitalWrite(OUT_RUN, LOW);
    digitalWrite(OUT_STAR, LOW);
    digitalWrite(OUT_DELTA, LOW);
    digitalWrite(BUZZER, HIGH);
    motorRunning = false;
    state = 0;
  }

  // Reset overload dengan tombol OFF
  if (offPressed) {
    if (overloadTrip) {
      Serial.println("Overload di-reset.");
    } else {
      Serial.println("Motor dihentikan.");
    }

    overloadTrip = false;
    digitalWrite(BUZZER, LOW);
    motorRunning = false;
    state = 0;

    digitalWrite(OUT_RUN, LOW);
    digitalWrite(OUT_STAR, LOW);
    digitalWrite(OUT_DELTA, LOW);
  }

  // =====================
  // START MOTOR
  // =====================
  if (onPressed && !overloadTrip && !motorRunning) {
    motorRunning = true;
    state = 1;
    starStartTime = millis();

    digitalWrite(OUT_RUN, HIGH);
    digitalWrite(OUT_STAR, HIGH);
    digitalWrite(OUT_DELTA, LOW);

    Serial.println("Motor START - Mode STAR");
  }

  // =====================
  // STAR → DELTA TRANSITION
  // =====================
  if (motorRunning && state == 1) {
    if (millis() - starStartTime >= starDuration) {
      digitalWrite(OUT_STAR, LOW);
      delay(500); // jeda interlock
      digitalWrite(OUT_DELTA, HIGH);
      state = 2;

      Serial.println("Transisi ke DELTA");
    }
  }
}