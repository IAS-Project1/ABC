#include <Servo.h>

Servo gateServo;

// Define pins
const int irSensorEntry = 2;    // IR sensor at entry point
const int irSensorExit = 3;     // IR sensor at exit point
const int redLED = 11;          // Red LED (Gate Closed)
const int greenLED = 10;        // Green LED (Gate Open)
const int buzzer = 12;          // Buzzer to alert when gate is closing

// Define servo positions for gate
const int gateOpenPos = 0;      // Position for open gate
const int gateClosedPos = 90;   // Position for closed gate

// Variables to store IR sensor states
bool trainDetected = false;

void setup() {
  // Initialize servo motor
  gateServo.attach(9);
  gateServo.write(gateOpenPos); // Start with gate open
  
  // Set up pin modes
  pinMode(irSensorEntry, INPUT);
  pinMode(irSensorExit, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initially, set gate open
  digitalWrite(greenLED, HIGH);   // Green LED on
  digitalWrite(redLED, LOW);      // Red LED off
  digitalWrite(buzzer, LOW);      // Buzzer off
  
  Serial.begin(9600); // Initialize serial monitor
}

void loop() {
  // Check IR sensors
  int entrySensorState = digitalRead(irSensorEntry);
  int exitSensorState = digitalRead(irSensorExit);
  
  // If a train is detected at entry sensor
  if (entrySensorState == LOW && !trainDetected) {  // LOW indicates obstacle detected
    trainDetected = true;         // Set train detected flag
    closeGate();                  // Call function to close the gate
  }

  // If a train is detected at exit sensor
  if (exitSensorState == LOW && trainDetected) {     // LOW indicates train passed
    trainDetected = false;        // Reset train detected flag
    openGate();                   // Call function to open the gate
  }
}

void closeGate() {
  Serial.println("Train detected, closing gate...");
  gateServo.write(gateClosedPos); // Move servo to close position
  digitalWrite(greenLED, LOW);    // Turn off green LED
  digitalWrite(redLED, HIGH);     // Turn on red LED
  digitalWrite(buzzer, HIGH);     // Turn on buzzer to alert
  delay(1000);                    // Delay to simulate gate closing time
  digitalWrite(buzzer, LOW);      // Turn off buzzer after delay
}

void openGate() {
  Serial.println("Train passed, opening gate...");
  gateServo.write(gateOpenPos);   // Move servo to open position
  digitalWrite(redLED, LOW);      // Turn off red LED
  digitalWrite(greenLED, HIGH);   // Turn on green LED
  digitalWrite(buzzer, LOW);      // Ensure buzzer is off
  delay(1000);                    // Delay to simulate gate opening time
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
