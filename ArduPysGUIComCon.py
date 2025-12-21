import tkinter as tk
import serial
import threading

# Ganti 'COM3' dengan port Arduino Uno Anda
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
except:
    print("Gagal membuka port. Pastikan Arduino terhubung!")

def read_serial():
    while True:
        try:
            if ser.in_waiting:
                line = ser.readline().decode('utf-8').strip()
                lbl_status.config(text=f"Status: {line}")
                
                # Logika warna status
                if "OVERLOAD" in line:
                    lbl_status.config(fg="red")
                    btn_start.config(state="disabled")
                    btn_off.config(state="disabled")
                elif "STAR" in line or "DELTA" in line:
                    lbl_status.config(fg="green")
                elif "UNLOADING" in line:
                    lbl_status.config(fg="orange")
                elif "READY" in line:
                    lbl_status.config(fg="black")
                    btn_start.config(state="normal")
                    btn_off.config(state="normal")
        except:
            break

def send_start():
    ser.write(b"START\n")

def send_off():
    # Menggunakan perintah RESET yang sama untuk mematikan sistem
    ser.write(b"RESET\n")

def send_reset_overload():
    ser.write(b"RESET\n")
    btn_start.config(state="normal")
    btn_off.config(state="normal")
    lbl_status.config(fg="black")

# Setup UI
root = tk.Tk()
root.title("ArduPys - Screw Compressor Controller")
root.geometry("400x350")

lbl_status = tk.Label(root, text="Status: READY", font=("Arial", 16, "bold"))
lbl_status.pack(pady=30)

# Frame untuk tombol-tombol
frame = tk.Frame(root)
frame.pack(pady=10)

btn_start = tk.Button(frame, text="COMPRESSOR ON", command=send_start, 
                      bg="green", fg="white", width=20, height=2)
btn_start.grid(row=0, column=0, pady=5)

btn_off = tk.Button(frame, text="COMPRESSOR OFF", command=send_off, 
                    bg="red", fg="white", width=20, height=2)
btn_off.grid(row=1, column=0, pady=5)

btn_reset = tk.Button(frame, text="SOFT RESET (Overload)", command=send_reset_overload, 
                      bg="orange", width=20, height=2)
btn_reset.grid(row=2, column=0, pady=20)

# Threading untuk Serial
thread = threading.Thread(target=read_serial, daemon=True)
thread.start()

root.mainloop()