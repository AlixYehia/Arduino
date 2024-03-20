#include <NewPing.h>



char Incoming_value='1';
int ENA = 3;  //ENA connected to digital pin 3
int ENB = 9;  //ENB connected to digital pin 9
int MOTOR_A1 = 4; // MOTOR_A1 connected to digital pin 4
int MOTOR_A2 = 5; // MOTOR_A2 connected to digital pin 5
int MOTOR_B1 = 6; // MOTOR_B1 connected to digital pin 6
int MOTOR_B2 = 7; // MOTOR_B2 connected to digital pin 7

int RIGHT = A0; // RIGHT sensor connected to analog pin A0
int LEFT = A1;  // LEFT sensor connected to analog pin A0

#define TRIG A2 // TRIG PIN connected to analog pin A2
#define ECHO A3 // ECHO PIN connected to analog pin A3
#define MAX_DISTANCE 100 // Define Maximum Distance

NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 

void setup() {
  // put your setup code here, to run once:
  
pinMode(ENA, OUTPUT); // initialize ENA pin as an output
pinMode(ENB, OUTPUT); // initialize ENB pin as an output
pinMode(MOTOR_A1, OUTPUT); // initialize MOTOR_A1 pin as an output
pinMode(MOTOR_A2, OUTPUT); // initialize MOTOR_A2 pin as an output
pinMode(MOTOR_B1, OUTPUT); // initialize MOTOR_B1 pin as an output
pinMode(MOTOR_B2, OUTPUT); // initialize MOTOR_B2 pin as an output
pinMode(RIGHT, INPUT); // initialize RIGHT pin as an input
pinMode(LEFT, INPUT);  // initialize LEFT pin as an input
Serial.begin(9600);


}

void loop() {



   if (Serial.available())
    {
      Incoming_value = Serial.read();
      Serial.print(Incoming_value);
      Serial.print("/n");
    }



    if (Incoming_value=='0')     // Master mode when incoming bluetooth signal is 0
    {
      
    
      delay(70);
      int distance = sonar.ping_cm();
      if (distance == 0) {
        distance = 30;
      }
      if(distance <=25) {

        Stop();
        delay(4000);
      }

 
      if (analogRead(RIGHT)<=150 && analogRead(LEFT)<=150) {//FORWARD
        analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, HIGH);
        digitalWrite(MOTOR_B2, LOW);
        
      }else if (analogRead(RIGHT)<=150 && !analogRead(LEFT)<=150) { //right
          analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, LOW);
        digitalWrite(MOTOR_B2, LOW);

      }else if (!analogRead(RIGHT)<=150 && analogRead(LEFT)<=150) { //LEFT
          analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, LOW);
        digitalWrite(MOTOR_B1, HIGH);
        digitalWrite(MOTOR_B2, LOW);
        
      }else if (!analogRead(RIGHT)<=150 && !analogRead(LEFT)<=150) {
      
        Stop();
      }
    }
 

    if (Incoming_value=='1')
    {
      
      delay(70);
      int distance = sonar.ping_cm();
      if (distance == 0)
      {
        distance = 35;
      }


      if(distance <=33) 
      {

        Stop();
        delay(100);
        turnRight();
        delay(600);
        Stop();
        delay(350);
        moveForward();
        delay(600);
        Stop();
        delay(350);
        turnLeft();
        delay(650);
        Stop();
        delay(350);
        moveForward();
        delay(1100);
        Stop();
        delay(350);
        turnLeft();
        delay(650);
        Stop();
        
        do {
        moveForward();

        } while (analogRead(RIGHT)>=150);
        Stop();

      }

 
      if (analogRead(RIGHT)<=150 && analogRead(LEFT)<=150) {//FORWARD
          analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, HIGH);
        digitalWrite(MOTOR_B2, LOW);
        
      }else if (analogRead(RIGHT)<=150 && !analogRead(LEFT)<=150) { //right
          analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, LOW);
        digitalWrite(MOTOR_B2, LOW);

      }else if (!analogRead(RIGHT)<=150 && analogRead(LEFT)<=150) { //LEFT
          analogWrite(ENA, 70);
        analogWrite(ENB, 55);
        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, LOW);
        digitalWrite(MOTOR_B1, HIGH);
        digitalWrite(MOTOR_B2, LOW);
        
      }else if (!analogRead(RIGHT)<=150 && !analogRead(LEFT)<=150) {
      
        Stop();
      }

    }

 
}
  

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
} 

void turnRight() {
   analogWrite(ENA, 70);
  analogWrite(ENB, 55);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
  
}

void turnLeft() {
    analogWrite(ENA, 70);
  analogWrite(ENB, 55);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
}

void moveForward() {
   analogWrite(ENA, 70);
  analogWrite(ENB, 55);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
}
