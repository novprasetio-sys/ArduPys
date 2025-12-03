# ArduPys – Microcontroller Monitoring & Control Platform  
*Lightweight • Functional • Industrial-Ready*

ArduPys adalah platform pengembangan microcontroller (Arduino / ESP32)  
yang terintegrasi dengan Python untuk monitoring dan kontrol industri ringan.

Repositori ini berisi integrasi:  
**Sensor MQ-2 → Arduino → Python → Matplotlib → Thingspeak**

---

## 📦 Isi Project

### `arduino/mq2_monitor.ino`
- Membaca nilai analog dari sensor MQ-2  
- Mengirim data ke PC melalui Serial (9600 baud)  
- Format data: angka murni, tanpa teks tambahan  

### `python/ardupys_gateway.py`
- Membaca nilai sensor dari Serial (PySerial)  
- Menampilkan grafik real-time menggunakan Matplotlib  
- Mengirim data ke Thingspeak setiap 15 detik  

### `docs/`
- Dokumentasi wiring  
- Foto rangkaian atau hasil pengujian  

---

## 🔌 Arsitektur Sistem

| Komponen         | Fungsi / Keterangan |
|-----------------|-------------------|
| Arduino / ESP32  | Membaca sensor MQ-2 dan kirim data Serial |
| Python Gateway   | Menerima data Serial, plot grafik realtime |
| Thingspeak       | Menyimpan data dan menampilkan chart online |

---

## ▶️ Cara Menjalankan

### 1. Arduino
Upload `mq2_monitor.ino` ke board (UNO / Nano / ESP32).

### 2. Python
Install dependency:  

```bash
pip install pyserial requests matplotlib


// Arduino C code — mq2_monitor.ino

const int MQ2_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.println(gasValue); // kirim angka murni
  delay(200);
}

# Python code — ardupys_gateway.py

import serial
import time
import requests
import matplotlib.pyplot as plt

SERIAL_PORT = "COM6"   # ubah sesuai port kamu
BAUD = 9600

API_KEY = "YOUR_API_KEY"
TS_URL = "https://api.thingspeak.com/update"

ser = serial.Serial(SERIAL_PORT, BAUD, timeout=1)
time.sleep(2)

# Matplotlib init
plt.ion()
fig, ax = plt.subplots()
xs, ys = [], []
line, = ax.plot(xs, ys)
ax.set_title("ArduPys – MQ2 Realtime Monitoring")
ax.set_xlabel("Sample")
ax.set_ylabel("MQ2 Value")

last_upload = time.time()
last_value = None
sample = 0

def upload(value):
    try:
        requests.get(TS_URL, params={"api_key": API_KEY, "field1": value})
        print(f"Kirim Thingspeak: {value}")
    except:
        print("Gagal upload Thingspeak")

while True:
    raw = ser.readline().decode().strip()
    if raw == "":
        continue

    try:
        last_value = int(raw)
        print("MQ2:", last_value)
    except:
        print("Invalid:", raw)
        continue

    # --- LIVE GRAPH ---
    sample += 1
    xs.append(sample)
    ys.append(last_value)
    line.set_xdata(xs)
    line.set_ydata(ys)
    ax.relim()
    ax.autoscale_view()
    plt.draw()
    plt.pause(0.001)

    # --- Thingspeak Upload ---
    if time.time() - last_upload >= 15:
        upload(last_value)
        last_upload = time.time()


# link vidio demo

https://youtube.com/shorts/Ehjf90_C43w?si=IwztdDMWZYw2OwVf