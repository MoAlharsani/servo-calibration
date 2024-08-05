# Servo Control using Arduino and Python

This project allows you to control the angles of multiple servos connected to an Arduino via a Python GUI application. The communication between the Arduino and the PC is done using a serial connection.

## Demo 
https://github.com/user-attachments/assets/25f0c78f-fe7b-4a37-b45d-e522a5797132

## Requirements

### Hardware
- Arduino (e.g., Arduino Uno, ESP32, etc)
- 6 Servo motors (or whatever you want to control)
- Jumper wires
- USB cable or CH341 USB-to-serial adapter

### Software
- Arduino IDE
- Python 3.x

### Arduino Libraries
- `Servo.h`

### Python Libraries
- `tkinter`
- `pyserial`

## Arduino Setup

1. Connect your servos to the Arduino as per the following pin configuration:

    | Servo | Pin |
    |-------|-----|
    | 1     | 11  |
    | 2     | 10  |
    | 3     | 9   |
    | 4     | 6   |
    | 5     | 5   |
    | 6     | 3   |

    Adjust the pin numbers in the Arduino code if you connect your servos to different pins.

2. Upload the following Arduino code to your Arduino board:

    ```cpp
    #include <Arduino.h>
    #include <Servo.h>

    #define NUM_SERVOS 6

    Servo servos[NUM_SERVOS];
    int servoPins[NUM_SERVOS] = {11, 10, 9, 6, 5, 3};

    void setup() {
      Serial.begin(9600);
      for (int i = 0; i < NUM_SERVOS; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(90);
      }
    }

    void loop() {
      if (Serial.available()) {
        String receivedData = Serial.readStringUntil('\n');
        int separatorIndex = receivedData.indexOf(':');
        if (separatorIndex != -1) {
          int servoIndex = receivedData.substring(0, separatorIndex).toInt() - 1;
          int angle = receivedData.substring(separatorIndex + 1).toInt();
          if (servoIndex >= 0 && servoIndex < NUM_SERVOS && angle >= 0 && angle <= 180) {
            servos[servoIndex].write(angle);
            Serial.println("Servo " + String(servoIndex + 1) + " set to angle " + String(angle));
          }
        }
      }
    }
    ```

## Python Setup

1. Install the required Python libraries:

    ```sh
    pip install pyserial
    ```

    `tkinter` usually comes pre-installed with Python. If not, you can install it based on your OS. For example, on Ubuntu, you can use:

    ```sh
    sudo apt-get install python3-tk
    ```

2. Create and run the following Python script:

    ```python
    import tkinter as tk
    from tkinter import ttk
    import serial

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
    ```

    Change `'COM10'` to the appropriate serial port your Arduino is connected to.

## Usage

1. Connect your Arduino to your PC using a USB cable or CH341 USB-to-serial adapter.
2. Upload the provided Arduino code to your Arduino.
3. Run the provided Python script.
4. Use the sliders in the GUI to adjust the angles of the servos.

## Troubleshooting

- Ensure the correct serial port is specified in the Python script.
- Verify the servo connections to the correct pins on the Arduino.
- Check the baud rate in both the Arduino code and Python script matches (9600 in this case).


