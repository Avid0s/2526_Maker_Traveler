#include <Arduino.h>
#include <BluetoothSerial.h>
#include <string.h>

struct Motor{
  int IN1;
  int IN2;
  int C1;
  int C2;
};

//function declarations
void forward(Motor motor);
void backward(Motor motor);
void stop(Motor motor);

struct Motor motorFL = {16, 17, 32, 33}; // Initialize motor structure
struct Motor motorFR = {5, 18, 34, 35}; 
struct Motor motorBR = {0, 4, 25, 26};
struct Motor motorBL = {15, 2, 27, 14};

uint16_t RxValue = 0;    // Initialisation de la valeur de reception
uint8_t buffer[100]; // Initialisation d'un buffer de 100 octets

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial time to initialize

  Serial.println("Starting ESP32 Bluetooth...");

  pinMode(22, OUTPUT);

  pinMode(motorFL.IN1, OUTPUT);
  pinMode(motorFL.IN2, OUTPUT);
  pinMode(motorFR.IN1, OUTPUT);
  pinMode(motorFR.IN2, OUTPUT);
  pinMode(motorBR.IN1, OUTPUT);
  pinMode(motorBR.IN2, OUTPUT);
  pinMode(motorBL.IN1, OUTPUT);
  pinMode(motorBL.IN2, OUTPUT);

  // Initialize Bluetooth - slave mode to accept connections from phone
  bool btStarted = SerialBT.begin("ESP32_BT");
  Serial.print("BT Start: ");
  Serial.println(btStarted ? "OK" : "FAILED");
  
  SerialBT.setPin("1234"); // Set PIN code
  Serial.println("PIN set to: 1234");
  
  Serial.println("Bluetooth ready - search for ESP32_BT on your device");

  // Check connection status
  do{
    if (SerialBT.hasClient()) {
      Serial.println("Phone connected!");
    }
    else {
      Serial.println("Waiting for phone to connect...");
      delay(500);
    }
  } while (!SerialBT.hasClient());
  Serial.println("Setup finished.");

}

void loop() {

  if (SerialBT.hasClient()) { //Connection check
    digitalWrite(22, HIGH);
  }
  else {
    digitalWrite(22, LOW);
  }
  
  // Check if Bluetooth data is available (at least 1 char)
  int btAvail = SerialBT.available();
  if (btAvail >= 1) {
    delay(30); // Wait for data to arrive
    // Clear buffer first to avoid garbage
    memset(buffer, 0, sizeof(buffer));
    
    // Read all available bytes
    int i = 0;
    while (SerialBT.available() && i < 98) {
      int c = SerialBT.read();
      
      if (c == 10 || c == 13) {  // Newline or CR - skip but mark as command
        break;  // Stop reading on terminator
      } else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {  // A-Z or a-z
        buffer[i++] = (char)c;
      } else if (c >= 48 && c <= 57) {  // 0-9 digits
        buffer[i++] = (char)c;
      }
      // Skip everything else
    }
    
    // Flush any remaining data in buffer
    while (SerialBT.available()) {
      SerialBT.read();
    }
    
    // Process if we got valid characters
    if (i > 0) {
      buffer[i] = '\0';
      Serial.print("Cmd: ");
      Serial.println((char*)buffer);

      // Handle commands
      // First, stop all motors before changing direction or continuing
      stop(motorFL);
      stop(motorFR);
      stop(motorBR);
      stop(motorBL);

      if (strcmp((char*)buffer, "F") == 0) {
        forward(motorFL);
        forward(motorFR);
        forward(motorBR);
        forward(motorBL);
        Serial.println("Moving Forward");
      } else if (strcmp((char*)buffer, "B") == 0) {
        backward(motorFL);
        backward(motorFR);
        backward(motorBR);
        backward(motorBL);
        Serial.println("Moving Backward");
      } else if (strcmp((char*)buffer, "TL") == 0) {
        forward(motorFR);
        forward(motorBR);
        backward(motorFL);
        backward(motorBL);
        Serial.println("Turning Left");
      } else if (strcmp((char*)buffer, "TR") == 0) {
        backward(motorFR);
        backward(motorBR);
        forward(motorFL);
        forward(motorBL);
        Serial.println("Turning Right");
      } else if (strcmp((char*)buffer, "ML") == 0) {
        forward(motorFL);
        backward(motorFR);
        backward(motorBR);
        forward(motorBL);
        Serial.println("Moving Left");
      } else if (strcmp((char*)buffer, "MR") == 0) {
        backward(motorFL);
        forward(motorFR);
        forward(motorBR);
        backward(motorBL);
        Serial.println("Moving Right");
      } else {
        Serial.println("Unknown Command");
      }
    }
  }

}

// put function definitions here:
void forward(Motor motor) {
  digitalWrite(motor.IN1, LOW);
  digitalWrite(motor.IN2, HIGH); // Setting to spin in one direction
}

void backward(Motor motor) {
  digitalWrite(motor.IN1, HIGH);
  digitalWrite(motor.IN2, LOW); // Setting to spin in the opposite direction
}

void stop(Motor motor) {
  digitalWrite(motor.IN1, LOW);
  digitalWrite(motor.IN2, LOW); // Stop the motor
}