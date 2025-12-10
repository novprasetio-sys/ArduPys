# ArduPys -- Microcontroller Monitoring & Control Platform

*Lightweight Functional Industrial-Ready*

ArduPys is a lightweight development platform that integrates **Arduino
/ ESP32 microcontrollers** with **Python** to provide simple yet
effective monitoring and control for light industrial applications.

This repository contains a complete example flow: **MQ-2 Sensor >>
Arduino >> Python >> Matplotlib >> Thingspeak**

------------------------------------------------------------------------

##  Project Contents

### `arduino/mq2_monitor.ino`

-   Reads analog values from the MQ-2 gas sensor
-   Sends raw numeric data via Serial (9600 baud)
-   Output format: pure integer data (no extra text)

### `python/ardupys_gateway.py`

-   Reads sensor data from Serial using PySerial
-   Displays real-time graph using Matplotlib
-   Uploads data to Thingspeak every 15 seconds

### `docs/`

-   Wiring documentation
-   Test photos or hardware setup images

------------------------------------------------------------------------

## System Architecture

  -----------------------------------------------------------------------
  Component                                 Description
  ----------------------------------------- -----------------------------
  Arduino / ESP32                           Reads MQ-2 sensor and streams
                                            Serial data

  Python Gateway                            Receives Serial data and
                                            displays real-time graph

  Thingspeak                                Stores and visualizes cloud
                                            data
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## How to Run

### **1. Arduino**

Upload `mq2_monitor.ino` to your board (UNO / Nano / ESP32).

### **2. Python**

Install the required dependencies:

``` bash
pip install pyserial requests matplotlib
```

------------------------------------------------------------------------

## Source Code

### **Arduino -- mq2_monitor.ino**

``` cpp
const int MQ2_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.println(gasValue); // send raw integer
  delay(200);
}
```

------------------------------------------------------------------------

### **Python -- ardupys_gateway.py**

``` python
import serial
import time
import requests
import matplotlib.pyplot as plt

SERIAL_PORT = "COM6"   # change to your serial port
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
ax.set_title("ArduPys â€“ MQ2 Realtime Monitoring")
ax.set_xlabel("Sample")
ax.set_ylabel("MQ2 Value")

last_upload = time.time()
last_value = None
sample = 0

def upload(value):
    try:
        requests.get(TS_URL, params={"api_key": API_KEY, "field1": value})
        print(f"Sent to Thingspeak: {value}")
    except:
        print("Upload failed")

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
```

------------------------------------------------------------------------

##  Demo Video

YouTube Short:
https://youtube.com/shorts/Ehjf90_C43w?si=IwztdDMWZYw2OwVf