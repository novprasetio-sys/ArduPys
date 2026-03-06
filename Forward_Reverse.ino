// =====================
// PIN SETUP
// =====================
#define BTN_OFF      7
#define BTN_FORWARD  8
#define BTN_REVERSE  9
#define BTN_OVERLOAD 10
#define OUT_FORWARD  2
#define OUT_REVERSE  3
#include <Servo.h>
Servo myservo;  
// =====================
// VARIABLE
// =====================
bool overloadTrip = false;
int state = 0;  
// 0 = STOP
// 1 = FORWARD
// 2 = REVERSE
// =====================
// SETUP
// =====================
void setup() {
	Serial.begin(9600);
	Serial.println("=== FORWARD-REVERSE INDUSTRIAL MODE ===");
	pinMode(BTN_OFF, INPUT_PULLUP);
	pinMode(BTN_FORWARD, INPUT_PULLUP);
	pinMode(BTN_REVERSE, INPUT_PULLUP);
	pinMode(BTN_OVERLOAD, INPUT_PULLUP);
	pinMode(OUT_FORWARD, OUTPUT);
	pinMode(OUT_REVERSE, OUTPUT);
	digitalWrite(OUT_FORWARD, LOW);
	digitalWrite(OUT_REVERSE, LOW);
	myservo.attach(4);  
}
// =====================
// LOOP
// =====================
void loop() {
	bool offPressed      = digitalRead(BTN_OFF) == LOW;
	bool forwardPressed  = digitalRead(BTN_FORWARD) == LOW;
	bool reversePressed  = digitalRead(BTN_REVERSE) == LOW;
	bool overloadPressed = digitalRead(BTN_OVERLOAD) == LOW;
	// =====================
	// OVERLOAD
	// =====================
	if (overloadPressed && !overloadTrip) {
		overloadTrip = true;
		Serial.println("!!! OVERLOAD TERDETEKSI !!!");
	}

	if (overloadTrip) {
		digitalWrite(OUT_FORWARD, LOW);
		digitalWrite(OUT_REVERSE, LOW);
		state = 0;
		myservo.write(90);  
	}
	// =====================
	// OFF (WAJIB UNTUK GANTI ARAH)
	// =====================
	if (offPressed) {
		if (state != 0)
			Serial.println("Motor STOP");
		if (overloadTrip)
			Serial.println("Overload di-reset");
		overloadTrip = false;
		state = 0;
		myservo.write(90);  
		digitalWrite(OUT_FORWARD, LOW);
		digitalWrite(OUT_REVERSE, LOW);
	}
	// =====================
	// INTERLOCK LOGIC
	// =====================
	// Jika dua tombol ditekan bersamaan ? abaikan
	if (forwardPressed && reversePressed) {
		Serial.println("ERROR: Dua arah ditekan bersamaan!");
		return;
	}
	// FORWARD hanya bisa jika kondisi STOP
	if (forwardPressed && state == 0 && !overloadTrip) {
		digitalWrite(OUT_FORWARD, HIGH);
		digitalWrite(OUT_REVERSE, LOW);
		myservo.write(0);  
		state = 1;
		Serial.println("Motor RUN FORWARD");
	}
	// REVERSE hanya bisa jika kondisi STOP
	if (reversePressed && state == 0 && !overloadTrip) {
		digitalWrite(OUT_FORWARD, LOW);
		digitalWrite(OUT_REVERSE, HIGH);
		myservo.write(180);  
		state = 2;
		Serial.println("Motor RUN REVERSE");
	}
}