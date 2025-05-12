//The following code is about how to make a line following robot
int l_ir=8;//to use the port number 8 on the digital board side of the UNO to be used as input of left infrared sensor 
int r_ir=9;//to use the port number 9 on the digital board side of the UNO to be used as input of right infrared sensor 
int s1=10;//to control the speed of one of the motor in our case it is left side motor
int s2=11;//to control the speed of right motor
int lmf=3;//left_motor_forward;ya to ye in1 ya to ye in3 hoga 
int lmb=4;//left_motot_backward;
int rmf=5;//right_motor_forward;ya to ye in1 ya to ye in3 hogas
int rmb=6;//right_motor_backward;
int speed = 65;//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(l_ir,INPUT);//to make the pin with name l_ir to take inputs from user
  pinMode(r_ir,INPUT);//to make the pin with name r_ir to take inputs from user
  analogWrite(s1,speed);//to set the speed of one of the motor to the given speed in our case 65 s1 is nothing but port number 10 of the aurdino actually port number 10 is sending an output to the motor controler via function analog write to set the speed with 65 that is value of speed
  analogWrite(s2,speed);//to set the speed of one of the motor to the given speed in our case 65 s1 is nothing but port number 11 of the aurdino actually port number 11 is sending an output to the motor controler via function analog write to set the speed with 65 that is value of speed
  pinMode(lmf,OUTPUT);//to make port number lmf of the digital side of UNO as  output  port now when it is output if we give high value from here what actually happens is the left side of the motor would move forward
  pinMode(lmb,OUTPUT);//to make port number lmb of the digital side of UNO as  output  port now when it is output if we give high value from here what actually happens is the left side of the motor would move backward 
  pinMode(rmf,OUTPUT);//to make port number rmf of the digital side of UNO as  output  port now when it is output if we give high value from here what actually happens is the right side of the motor would move forward
  pinMode(rmb,OUTPUT);//to make port number lmf of the digital side of UNO as  output  port now when it is output if we give high value from here what actually happens is the right side of the motor would move backward
}

void loop() {
  // put your main code here, to run repeatedly:
  int l_ir_input = digitalRead(l_ir);//to read the output of the left ir 
  int r_ir_input = digitalRead(r_ir);//to read the output of the right ir
  if(l_ir_input == 0 && r_ir_input == 0){
    //means no obstacle ahead go forward
    go_forward();
  }
  if(l_ir_input == 1 && r_ir_input == 0){
    //means that there is obstacle in left
    go_right();
  }
  if(l_ir_input == 0 && r_ir_input == 1){
    //means that there is obstacle in right
    go_left();
  }
  if(l_ir_input == 1 && r_ir_input == 1){
    stop();
  }
}
void go_forward(){
  digitalWrite(rmf,HIGH);//when we supply high to this port the motor of the right side would move clockwise making the vehicle move forward
  digitalWrite(lmf,HIGH);//when we supply high to this port the motor of the left side would move clockwise making the vehicle move forward
  digitalWrite(rmb,LOW);//when we supply low to this port the motor of the right side would not contradict the previous functions
  digitalWrite(lmb,LOW);//when we supply low to this port the motor of the left side would not contradict the previous functions
void stop(){
  digitalWrite(rmf,LOW);
  digitalWrite(lmf,LOW);
  digitalWrite(rmb,LOW);
  digitalWrite(lmb,LOW);
}
void go_right(){
  digitalWrite(rmf,LOW);
  digitalWrite(lmf,HIGH);
  digitalWrite(rmb,HIGH);
  digitalWrite(lmb,LOW);
}
void go_left(){
  digitalWrite(rmf,HIGH);
  digitalWrite(lmf,LOW);
  digitalWrite(rmb,LOW);
  digitalWrite(lmb,HIGH);
}
