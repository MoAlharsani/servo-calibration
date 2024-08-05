import tkinter as tk
from tkinter import ttk
import serial

# Initialize serial port
ser = serial.Serial('COM10', 9600)  # Change 'COM10' to the appropriate serial port

class SliderApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Slider App")

        self.sliders = []
        self.labels = []

        for i in range(6):
            label = ttk.Label(root, text=f"Servo {i+1}")
            label.pack(pady=5)
            self.labels.append(label)
            
            slider = ttk.Scale(root, from_=0, to=180, orient='horizontal', command=lambda value, i=i: self.send_to_serial(value, i))
            slider.pack(pady=5)
            self.sliders.append(slider)

    def send_to_serial(self, value, slider_index):
        print(f"Slider {slider_index+1}: {int(float(value))}")
        ser.write(f"{slider_index+1}:{int(float(value))}\n".encode())
        
        


if __name__ == "__main__":
    root = tk.Tk()
    app = SliderApp(root)
    root.mainloop()
