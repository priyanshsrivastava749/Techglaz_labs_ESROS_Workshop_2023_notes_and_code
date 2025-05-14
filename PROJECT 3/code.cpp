// Bluetooth Controlled Robot Code

// Define motor speed control pins (PWM capable)
int s1 = 10;  // Speed control pin for left motor
int s2 = 11;  // Speed control pin for right motor

// Variable to store incoming character from Bluetooth
char m = '0';  // Default command character

// Define motor control pins
int lmf = 5;   // Left Motor Forward
int lmb = 6;   // Left Motor Backward
int rmf = 3;   // Right Motor Forward
int rmb = 4;   // Right Motor Backward

// Speed variable (0 to 255)
int Speed = 0;  // Initial speed

void setup() {
  // Initialize Serial Communication at 9600 baud rate
  Serial.begin(9600);

  // Set motor driver pins as output
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT); 
  pinMode(rmb, OUTPUT);
}

void loop() {
  // Check if Bluetooth data is available
  if (Serial.available() > 0) {
    m = Serial.read();  // Read the incoming character
    Serial.println(m);  // Print received character for debugging
  }

  // Apply speed to both motors
  analogWrite(s1, Speed);
  analogWrite(s2, Speed);

  // Control robot movement based on received command
  if (m == 'F') {
    go_forward();
    Serial.println("go forward!");
  } 
  else if (m == 'B') {
    go_back();
    Serial.println("go backward!");
  } 
  else if (m == 'R') {
    go_right();
    Serial.println("go right");
  } 
  else if (m == 'L') {
    go_left();
    Serial.println("go left");
  } 
  else if (m == 'S') {
    stop();
    Serial.println("stopped");
  }

  // Speed control via Bluetooth commands
  else if (m == '0') {
    Speed = 0;
    Serial.println("speed is 0");
  } 
  else if (m == '1') {
    Speed = 50;
    Serial.println("speed is 50");
  } 
  else if (m == '2') {
    Speed = 100;
    Serial.println("speed is 100");
  } 
  else if (m == '3') {
    Speed = 150;
    Serial.println("speed is 150");
  }
}

// Function to move robot forward
void go_forward() {
  digitalWrite(rmf, HIGH);
  digitalWrite(lmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
}

// Function to stop all motors
void stop() {
  digitalWrite(rmf, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
}

// Function to move robot backward
void go_back() {
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
}

// Function to turn robot right
void go_right() {
  digitalWrite(rmf, LOW);    // Right motor reverse
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, HIGH);   // Left motor forward
  digitalWrite(lmb, LOW);
}

// Function to turn robot left
void go_left() {
  digitalWrite(rmf, HIGH);   // Right motor forward
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);    // Left motor reverse
  digitalWrite(lmb, HIGH);
}
