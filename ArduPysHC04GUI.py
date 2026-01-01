import serial
import tkinter as tk
from tkinter import ttk
class GUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Sistem Pemantau Level Air Tandon")
        self.canvas = tk.Canvas(self.root, width=400, height=400)
        self.canvas.pack()
        self.ser = serial.Serial('COM4', 9600)  # ganti COM9 dengan port serial yang digunakan
        self.update_distance()
    def draw_gauge(self, dist):
        self.canvas.delete("all")
        self.canvas.create_arc(50, 50, 360, 360, start=180, extent=360, style="arc", width=20)
        self.canvas.create_arc(50, 50, 360, 360, start=180, extent=dist*1.8, style="arc", width=20, outline="red")
        self.canvas.create_text(200, 200, text=str(dist) + "cm", font=("Arial", 24))
    def update_distance(self):
        if self.ser.in_waiting > 0:
            data = self.ser.readline().decode().strip()
            try:
                dist = float(data)
                self.draw_gauge(dist)
            except ValueError:
                pass
        self.root.after(100, self.update_distance)  # update setiap 100ms

    def run(self):
        self.root.mainloop()
if __name__ == "__main__":
    gui = GUI()
    gui.run()