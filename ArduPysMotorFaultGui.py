import serial
import tkinter as tk
from tkinter import messagebox

# ===== SERIAL =====
ser = serial.Serial('COM3', 9600, timeout=0.1)

# ===== FAULT LATCH =====
fault_motor1 = False
fault_motor2 = False
fault_motor3 = False

# ===== GUI =====
root = tk.Tk()
root.title("ArduPys Motor Fault Monitor")
root.geometry("300x200")

label = tk.Label(root, text="System Normal", font=("Arial", 14))
label.pack(pady=40)

def check_serial():
    global fault_motor1, fault_motor2, fault_motor3

    if ser.in_waiting:
        data = ser.readline().decode().strip()
        print(data)

        if data == "FAULT:MOTOR1" and not fault_motor1:
            fault_motor1 = True
            label.config(text="Motor 1 FAULT")
            messagebox.showwarning("FAULT", "Motor 1 Bermasalah!")

        elif data == "FAULT:MOTOR2" and not fault_motor2:
            fault_motor2 = True
            label.config(text="Motor 2 FAULT")
            messagebox.showwarning("FAULT", "Motor 2 Bermasalah!")

        elif data == "FAULT:MOTOR3" and not fault_motor3:
            fault_motor3 = True
            label.config(text="Motor 3 FAULT")
            messagebox.showwarning("FAULT", "Motor 3 Bermasalah!")

    root.after(100, check_serial)

check_serial()
root.mainloop()