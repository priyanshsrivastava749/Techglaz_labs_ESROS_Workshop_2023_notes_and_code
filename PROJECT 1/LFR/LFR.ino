// Line Following Robot Code

// IR sensor pins
int l_ir = 8;  // Left IR sensor connected to digital pin 8
int r_ir = 9;  // Right IR sensor connected to digital pin 9

// Motor speed control (PWM) pins
int s1 = 10;   // Speed control for left motor via PWM (connected to ENA of motor driver)
int s2 = 11;   // Speed control for right motor via PWM (connected to ENB of motor driver)

// Motor control pins
int lmf = 3;   // Left motor forward (IN1 or IN3 depending on your wiring)
int lmb = 4;   // Left motor backward (IN2 or IN4)
int rmf = 5;   // Right motor forward (IN1 or IN3)
int rmb = 6;   // Right motor backward (IN2 or IN4)

// Speed value (0-255)
int speed = 65;

void setup() {
  Serial.begin(9600);  // Initialize serial monitor for debugging

  // Set IR sensor pins as input
  pinMode(l_ir, INPUT);
  pinMode(r_ir, INPUT);

  // Set speed of motors using PWM
  analogWrite(s1, speed);  // Set speed for left motor
  analogWrite(s2, speed);  // Set speed for right motor

  // Set motor control pins as output
  pinMode(lmf, OUTPUT);  // Left motor forward pin
  pinMode(lmb, OUTPUT);  // Left motor backward pin
  pinMode(rmf, OUTPUT);  // Right motor forward pin
  pinMode(rmb, OUTPUT);  // Right motor backward pin
}

void loop() {
  // Read IR sensor values (0 = black line detected, 1 = white surface)
  int l_ir_input = digitalRead(l_ir);
  int r_ir_input = digitalRead(r_ir);

  if (l_ir_input == 0 && r_ir_input == 0) {
    // Both sensors on line → Go forward
    go_forward();
  } 
  else if (l_ir_input == 1 && r_ir_input == 0) {
    // Left sensor off line, right sensor on line → Turn right
    go_right();
  } 
  else if (l_ir_input == 0 && r_ir_input == 1) {
    // Right sensor off line, left sensor on line → Turn left
    go_left();
  } 
  else if (l_ir_input == 1 && r_ir_input == 1) {
    // Both sensors off line → Stop
    stop();
  }
}

// Move forward: both motors forward
void go_forward() {
  digitalWrite(rmf, HIGH);  // Right motor forward
  digitalWrite(lmf, HIGH);  // Left motor forward
  digitalWrite(rmb, LOW);   // Right motor not backward
  digitalWrite(lmb, LOW);   // Left motor not backward
}

// Stop all motors
void stop() {
  digitalWrite(rmf, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
}

// Turn right: left motor forward, right motor backward
void go_right() {
  digitalWrite(rmf, LOW);   // Right motor stop / reverse
  digitalWrite(rmb, HIGH);  // Right motor backward
  digitalWrite(lmf, HIGH);  // Left motor forward
  digitalWrite(lmb, LOW);   // Left motor not backward
}

// Turn left: right motor forward, left motor backward
void go_left() {
  digitalWrite(rmf, HIGH);  // Right motor forward
  digitalWrite(rmb, LOW);   // Right motor not backward
  digitalWrite(lmf, LOW);   // Left motor stop / reverse
  digitalWrite(lmb, HIGH);  // Left motor backward
}
