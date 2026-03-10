
# project ini untuk mengirim state 1 dan 0 dari Arduino ke Thingspeak tanpa module wifi
# pastikan arduino mengirim 1 dan 0 dengan Serial.println(data);
# gunakan codingan button yg dimodifikasi dengan if dan else


import serial
import requests
import time

# ==========================
# KONFIGURASI
# ==========================
SERIAL_PORT = "COM3"      # ganti sesuai port Arduino
BAUDRATE = 9600

THINGSPEAK_API_KEY = "ISI_API_KEY_ANDA"
THINGSPEAK_URL = "https://api.thingspeak.com/update"

# ==========================
# BUKA SERIAL
# ==========================
ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)

print("Menunggu data dari Arduino...")

# ==========================
# LOOP UTAMA
# ==========================
while True:

    if ser.in_waiting > 0:

        data = ser.readline().decode().strip()

        print("Data dari Arduino:", data)

        if data == "0" or data == "1":

            payload = {
                "api_key": THINGSPEAK_API_KEY,
                "field1": data
            }

            try:
                response = requests.post(THINGSPEAK_URL, data=payload)
                print("Data terkirim ke ThingSpeak:", data)

            except:
                print("Gagal kirim ke ThingSpeak")

            # delay agar tidak melanggar rate limit
            time.sleep(16)