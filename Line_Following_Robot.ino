#define NUMIR          5    // Amount of proximity sensors
#define Kp             0.01 // Kp gain
#define Ki             0    // Ki gain
#define Kd             0    // Kd gain
#define BASESPEED      100  // Base speed of motor 
#define ROTATESPEED    75   // Speed of motor when change direction (when not go straight)
#define ENA            6    // ENA pin of motor controller
#define ENB            5    // END pin of motor controller
#define IN1            A2   // IN1 pin of motor controller
#define IN2            A3   // IN2 pin of motor controller
#define IN3            A0   // IN3 pin of motor controller
#define IN4            A1   // IN4 pin of motor controller
#define R              13   // Red light of the robot
#define Y              12   // Yellow light of the robot
#define G              5    // Green light of the robot

int pinSensors[]      = {8, 7, 4, 3, 2};    // digital pin of 5 proximity sensors 
int senseValues[]     = {0, 0, 0, 0, 0};    // values from proximity sensors
int sum               = 0;
int devide            = 0;
int result            = 0;
int proportional      = 0;
int position          = 0;
int derivative        = 0;
int prevProportional  = 0;
int integral          = 0;
int powerError        = 0;
int motorSpeed        = 0;
int leftWheelSpeed    = 0;
int rightWheelSpeed   = 0;

void setup(){
  pinMode(pinSensors[0], INPUT);
  pinMode(pinSensors[1], INPUT);
  pinMode(pinSensors[2], INPUT);
  pinMode(pinSensors[3], INPUT);
  pinMode(pinSensors[4], INPUT);
  pinMode(ENA  , OUTPUT);
  pinMode(ENB  , OUTPUT);
  pinMode(IN1  , OUTPUT);
  pinMode(IN2  , OUTPUT);
  pinMode(IN3  , OUTPUT);
  pinMode(IN4  , OUTPUT);
  digitalWrite(R, HIGH);
  digitalWrite(R, LOW);
  digitalWrite(Y, HIGH);
  delay(5500);
  digitalWrite(Y, LOW);
  delay(2000); 
}

void forward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

int readSensors(){
  for(int i = 0 ; i < NUMIR ; i++)
    senseValues[i] = digitalRead(pinSensors[i]);
    sum          = (0 * senseValues[0]) + (1000 * senseValues[1]) + (2000 * senseValues[2]) + (3000 * senseValues[3]) + (4000 * senseValues[4]);
    devide       = senseValues[0] + senseValues[1] + senseValues[2] + senseValues[3] + senseValues[4];
    result       = sum / devide;
    return result;
}

void calculatePID(){
  proportional      = readSensors() - 2000;
  derivative        = proportional - prevProportional;
  integral         += proportional;
  prevProportional = proportional;
  powerError       = (proportional * Kp) + (integral * Ki) + (derivative * Kd);
}

void configMotor(){
  motorSpeed = powerError;
  leftWheelSpeed  = BASESPEED + motorSpeed;
  rightWheelSpeed = BASESPEED - motorSpeed;
  leftWheelSpeed  = constrain(leftWheelSpeed, 0, 255);
  rightWheelSpeed = constrain(rightWheelSpeed, 0, 255);
  analogWrite(ENA, leftWheelSpeed);
  analogWrite(ENB, rightWheelSpeed);
  forward();
}

void loop(){
  readSensors();
  if(senseValues[0] == LOW && senseValues[1] == LOW && senseValues[2] == LOW && senseValues[3] == LOW && senseValues[4] == LOW){
    while(senseValues[0] == LOW && senseValues[1] == LOW && senseValues[2] == LOW && senseValues[3] == LOW && senseValues[4] == LOW){
      do{
    analogWrite(ENA, ROTATESPEED);
    analogWrite(ENB, ROTATESPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    readSensors();
      }while(senseValues[0] != HIGH && senseValues[1] == LOW && senseValues[2] == LOW && senseValues[3] == HIGH && senseValues[4] == LOW);
  }
  }
  else{
    calculatePID();
    configMotor();
  }
}
