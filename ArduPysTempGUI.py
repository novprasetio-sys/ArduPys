import serial
import tkinter as tk
from tkinter import ttk

class GUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Sistem Pemantau Temperatur")

        self.canvas = tk.Canvas(self.root, width=400, height=400)
        self.canvas.pack()

        self.ser = serial.Serial('COM3', 9600)  # ganti COM9 dengan port serial yang digunakan

        self.update_temperatur()

    def draw_gauge(self, temp):
        self.canvas.delete("all")
        self.canvas.create_oval(50, 50, 350, 350)
        self.canvas.create_arc(50, 50, 350, 350, start=0, extent=180, style="arc", width=20)
        self.canvas.create_arc(50, 50, 350, 350, start=0, extent=temp*1.8, style="arc", width=20, outline="red")
        self.canvas.create_text(200, 200, text=str(temp) + "°C", font=("Arial", 24))

    def update_temperatur(self):
        if self.ser.in_waiting > 0:
            data = self.ser.readline().decode().strip()
            try:
                temp = float(data)
                self.draw_gauge(temp)
            except ValueError:
                pass
        self.root.after(100, self.update_temperatur)  # update setiap 100ms

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    gui = GUI()
    gui.run()