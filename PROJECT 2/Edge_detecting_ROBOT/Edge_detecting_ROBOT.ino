// Edge Detecting Robot Code (based on modified Line Following Logic)

// IR sensor pins (connected near the bottom of robot to detect table edge or black line)
int l_ir = 8;  // Left IR sensor (digital pin 8)
int r_ir = 9;  // Right IR sensor (digital pin 9)

// Motor speed control (PWM) pins
int s1 = 10;   // Speed control for left motor (ENA)
int s2 = 11;   // Speed control for right motor (ENB)

// Motor control pins (connected to L298N or similar motor driver)
int lmf = 3;   // Left motor forward
int lmb = 4;   // Left motor backward
int rmf = 5;   // Right motor forward
int rmb = 6;   // Right motor backward

// Motor speed (0-255)
int speed = 55;

void setup() {
  Serial.begin(9600);  // For debugging

  // IR sensors as input
  pinMode(l_ir, INPUT);
  pinMode(r_ir, INPUT);

  // Set initial motor speed using PWM
  analogWrite(s1, speed);  // Left motor
  analogWrite(s2, speed);  // Right motor

  // Motor direction pins as output
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
}

void loop() {
  // Read IR sensor values (0 = black line/table edge detected, 1 = white surface)
  int l_ir_input = digitalRead(l_ir);
  int r_ir_input = digitalRead(r_ir);

  if (l_ir_input == 0 && r_ir_input == 0) {
    // Both sensors on table surface → Move forward
    go_forward();
  } 
  else if (l_ir_input == 1 && r_ir_input == 0) {
    // Left edge detected → Turn right to stay on surface
    go_right();
  } 
  else if (l_ir_input == 0 && r_ir_input == 1) {
    // Right edge detected → Turn left to stay on surface
    go_left();
  } 
  else if (l_ir_input == 1 && r_ir_input == 1) {
    // Both sensors detect edge → Go back and turn right (escape)
    go_back();
    delay(1000);   // Move backward for 1 second
    stop();        
    go_right();    // Then turn right to get back on surface
    delay(500);
  }
}

// Function: Move forward
void go_forward() {
  digitalWrite(rmf, HIGH);
  digitalWrite(lmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
}

// Function: Stop all motors
void stop() {
  digitalWrite(rmf, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmb, LOW);
}

// Function: Move backward
void go_back() {
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
}

// Function: Turn right (pivot)
void go_right() {
  digitalWrite(rmf, LOW);   // Right motor reverse
  digitalWrite(rmb, HIGH);
  digitalWrite(lmf, HIGH);  // Left motor forward
  digitalWrite(lmb, LOW);
}

// Function: Turn left (pivot)
void go_left() {
  digitalWrite(rmf, HIGH);  // Right motor forward
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);   // Left motor reverse
  digitalWrite(lmb, HIGH);
}
