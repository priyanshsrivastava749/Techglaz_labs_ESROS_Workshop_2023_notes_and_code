// Object Following Robot Code

// IR Sensor Pins (used for detecting the object)
int l_ir = 8;  // Left IR sensor connected to digital pin 8
int r_ir = 9;  // Right IR sensor connected to digital pin 9

// Motor speed control (PWM) pins
int s1 = 10;   // Speed control for left motor (ENA pin of motor driver)
int s2 = 11;   // Speed control for right motor (ENB pin of motor driver)

// Motor control pins
int lmf = 3;   // Left motor forward (IN1)
int lmb = 4;   // Left motor backward (IN2)
int rmf = 5;   // Right motor forward (IN3)
int rmb = 6;   // Right motor backward (IN4)

// Motor speed (0 to 255)
int speed = 100;

void setup() {
  Serial.begin(9600);  // Start serial monitor (for debugging)

  // Set IR sensor pins as input
  pinMode(l_ir, INPUT);
  pinMode(r_ir, INPUT);

  // Set motor speed using PWM
  analogWrite(s1, speed);  // Left motor speed
  analogWrite(s2, speed);  // Right motor speed

  // Set motor direction pins as output
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
}

void loop() {
  // Read sensor values
  int l_ir_input = digitalRead(l_ir);  // 1 if object detected on left
  int r_ir_input = digitalRead(r_ir);  // 1 if object detected on right

  Serial.print("Left Sensor: ");
  Serial.print(l_ir_input);
  Serial.print(" | Right Sensor: ");
  Serial.println(r_ir_input);

  if (l_ir_input == 1 && r_ir_input == 1) {
    // Object is in front of both sensors → Move forward
    go_forward();
  } 
  else if (l_ir_input == 0 && r_ir_input == 1) {
    // Object is only on the right → Turn right to follow
    go_right();
  } 
  else if (l_ir_input == 1 && r_ir_input == 0) {
    // Object is only on the left → Turn left to follow
    go_left();
  } 
  else {
    // Object not detected by any sensor → Stop
    stop();
  }
}

// Move both motors forward
void go_forward() {
  digitalWrite(rmf, HIGH);
  digitalWrite(lmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
  Serial.println("Moving Forward");
}

// Stop all motor movement
void stop() {
  digitalWrite(rmf, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
  Serial.println("Stopped");
}

// Turn right by making right motor reverse and left motor forward
void go_right() {
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  Serial.println("Turning Right");
}

// Turn left by making left motor reverse and right motor forward
void go_left() {
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  Serial.println("Turning Left");
}
