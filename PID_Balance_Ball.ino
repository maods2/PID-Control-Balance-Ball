#include<Servo.h>
#include <Ultrasonic.h>


/*working variables*/
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastInput;
double kp, ki, kd;

const int trigPin = 9;       //Ultrasonic Sensor Trig Pin
const int echoPin = 10;                                                                                                                                                         
const int pCONTROLE = 13;//Servo Pin                                                                                                           
long distancia;
int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12;  
long duration, filtro;                                                                   
Servo myservo; // Variável Servo 
double StartAngle = 16;


  
void setup() {
  Serial.begin(9600);                                                
  myservo.attach(pCONTROLE);
  myservo.write(StartAngle); // Inicia motor posição zero                                           
  pinMode(pCONTROLE, OUTPUT);
  pinMode(trigPin, OUTPUT);   //Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   

}

void loop() {
  kp = 1;
  ki = 0;
  kd = 200;
  Setpoint = 16;
  Input = readPosition();
  /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += error;
   double dInput = (Input - lastInput);
   int td_ = kd/kp;
   int td = (td_/(1 + 0.1*td_));
   kd = td/kp;
   /*Compute PID Output*/
   Output = kp * error + ki * errSum - kd * dInput;
  
   /*Remember some variables for next time*/
   lastInput = Input;
   lastTime = now;
   
  myservo.write(StartAngle + Output);
  int angulo = StartAngle + Output;
  Serial.println("Angulo:");
  Serial.println(angulo);
  Serial.println("Saída:");
  Serial.println(Output);
}
float readPosition() {  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  //Calculating the distance
  distancia= duration/(29*2); 

  val12 = val11;
  val11 = val10;
  val10 = val9;
  val9 = val8;
  val8 = val7;
  val7 = val6;
  val6 = val5;
  val5 = val4;
  val4 = val3;
  val3 = val2;
  val2 = val1;
  val1 = distancia;

  filtro = (val1 + val2 + val3 + val4 + val5 + val6 + val7 + val8 + val9 + val10 + val11 + val12)/12;
  
  
  
  return filtro;                                          
}
