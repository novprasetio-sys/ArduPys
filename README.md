# ArduPys
Arduino-Python Serial Communications for data Visualizations
https://youtube.com/shorts/Ehjf90_C43w?si=IwztdDMWZYw2OwVf

#python codes

import serial
import requests
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time

# -------------------------
# KONFIGURASI USER
# -------------------------
PORT = "COM3"                  # ganti sesuai port Arduino
BAUD = 9600
WRITE_API_KEY = "FIIUB4XQCNVZGPOP"
UPDATE_INTERVAL = 15           # minimal 15 detik (aturan ThingSpeak)
# -------------------------

ser = serial.Serial(PORT, BAUD, timeout=1)
data_buffer = []
last_upload = time.time()

# Grafik setup
plt.style.use("ggplot")
fig, ax = plt.subplots()
line, = ax.plot([], [])

def update(frame):
    global last_upload
    line.set_data(range(len(data_buffer)), data_buffer)
    ax.relim()
    ax.autoscale_view()

    try:
        raw = ser.readline().decode().strip()
        if raw:
            val = int(raw)
            data_buffer.append(val)
            if len(data_buffer) > 200:
                data_buffer.pop(0)

            # Upload tiap 15 detik
            if time.time() - last_upload >= UPDATE_INTERVAL:
                url = "https://api.thingspeak.com/update"
                params = {"api_key": WRITE_API_KEY, "field1": val}
                requests.get(url, params=params)
                last_upload = time.time()
                print("Upload ke ThingSpeak:", val)

    except:
        pass

    return line,

ani = FuncAnimation(fig, update, interval=200)
plt.title("ArduPys Lite - MQ2 Real-time Plot")
plt.xlabel("Sample")
plt.ylabel("MQ2 Value")
