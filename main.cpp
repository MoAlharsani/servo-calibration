#include <Arduino.h>
#include <Servo.h>

// Define the number of servos
#define NUM_SERVOS 6

// Create an array to hold servo objects
Servo servos[NUM_SERVOS];

// Array to hold pin numbers for each servo
int servoPins[NUM_SERVOS] = {11, 10, 9, 6, 5, 3}; // Adjust these pins according to your wiring

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Attach each servo to its corresponding pin
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90);

  }
}

void loop() {
  // Check if data is available on the Serial port
  if (Serial.available()) {
    // Read the data from the Serial port
    String receivedData = Serial.readStringUntil('\n');
    
    // Parse the received data to extract servo index and angle value
    int separatorIndex = receivedData.indexOf(':');
    if (separatorIndex != -1) {
      int servoIndex = receivedData.substring(0, separatorIndex).toInt() - 1; // Subtract 1 to make it 0-based index
      int angle = receivedData.substring(separatorIndex + 1).toInt();

      // Validate the servo index and angle
      if (servoIndex >= 0 && servoIndex < NUM_SERVOS && angle >= 0 && angle <= 180) {
        // Move the corresponding servo to the desired angle
        servos[servoIndex].write(angle);
        Serial.println("Servo " + String(servoIndex + 1) + " set to angle " + String(angle));
      }
    }
  }
}
