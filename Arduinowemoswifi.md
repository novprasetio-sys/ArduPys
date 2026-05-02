Sistem Kontrol Relay Berbasis Wemos & Arduino

📌 Deskripsi Sistem

Sistem ini menggunakan dua mikrokontroler:

- Wemos (ESP8266) sebagai Web Server (Access Point)
- Arduino Uno sebagai pengendali relay

Wemos menerima input dari user melalui web server, lalu mengirimkan sinyal digital ke Arduino.

---

⚙️ Arsitektur Sistem

Wemos (ESP8266)

- Mode: Access Point (AP)
- Web Server untuk kontrol ON/OFF
- Output pin: D1 – D5
- Default kondisi: HIGH
- Saat tombol ditekan: LOW

Arduino Uno

- Input pin: D2 – D6 (dari Wemos)
- Output pin: D8 – D12 (ke relay)

---

🔌 Wiring

Wemos ke Arduino

Wemos| Arduino
D1| D2
D2| D3
D3| D4
D4| D5
D5| D6

⚠️ GND Wemos harus terhubung ke GND Arduino

---

🧠 Logika Sistem

Wemos| Arduino| Relay
HIGH| HIGH| OFF
LOW| LOW| ON

Active LOW system:

- LOW = ON
- HIGH = OFF

---

💻 Kode Wemos (ESP8266)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Pin output
int pins[5] = {D1, D2, D3, D4, D5};

// HTML sederhana
String html = "<html><head><title>Control Relay</title></head><body>";
html += "<h2>Relay Control</h2>";

void handleRoot() {
  String page = html;

  for (int i = 0; i < 5; i++) {
    page += "Relay " + String(i+1) + " ";
    page += "<a href=\"/on" + String(i) + "\">ON</a> ";
    page += "<a href=\"/off" + String(i) + "\">OFF</a><br><br>";
  }

  page += "</body></html>";
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(9600);

  // Set pin sebagai OUTPUT dan default HIGH
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }

  // Setup Access Point
  WiFi.softAP("Relay_Control", "12345678");

  // Routing
  server.on("/", handleRoot);

  for (int i = 0; i < 5; i++) {
    int idx = i;

    server.on(("/on" + String(i)).c_str(), [idx]() {
      digitalWrite(pins[idx], LOW); // ON (active LOW)
      server.sendHeader("Location", "/");
      server.send(303);
    });

    server.on(("/off" + String(i)).c_str(), [idx]() {
      digitalWrite(pins[idx], HIGH); // OFF
      server.sendHeader("Location", "/");
      server.send(303);
    });
  }

  server.begin();
}

void loop() {
  server.handleClient();
}

---

💻 Kode Arduino

int inputPins[5] = {2,3,4,5,6};
int relayPins[5] = {8,9,10,11,12};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(inputPins[i]) == LOW) {
      digitalWrite(relayPins[i], HIGH);
    } else {
      digitalWrite(relayPins[i], LOW);
    }
  }
}

---

🌐 Cara Akses

1. Nyalakan Wemos
2. Connect ke WiFi:
   - SSID: Relay_Control
   - Password: 12345678
3. Buka browser:
   - http://192.168.4.1
4. Klik tombol ON/OFF

---

⚠️ Catatan

Tegangan

- Wemos: 3.3V
- Arduino: 5V
  ✔ Aman untuk komunikasi digital

---

Relay

- Umumnya active LOW
- Sesuaikan jika berbeda

---

Enclosure

- Bisa pakai paralon / box bekas
- Pastikan ventilasi & isolasi aman

---

🚀 Upgrade Selanjutnya

- Tampilan UI lebih bagus
- Status feedback
- Monitoring sensor
- Integrasi IoT

---