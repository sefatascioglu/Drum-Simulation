//pin assignments

const int buttonPin  = 8;
const int ledPin=13;

int buttonState = 0;
int counter = 0;


///1. motor Motor
const int motor1Pin = 12; // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 5; // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 4; // H-bridge enable pin




//2. motor
const int motor3Pin = 13; // H-bridge leg 1 (pin 2, 1A)
const int motor4Pin = 6; // H-bridge leg 2 (pin 7, 2A)
const int enablePin2 = 3; // H-bridge enable pin

int ReadData = 0;

void setup(){
 // pinMode(buttonPin, INPUT);
  
  //set all the other pins you✬re using as outputs:
    pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT);
  
  pinMode(motor1Pin, OUTPUT);
  
  pinMode(motor2Pin, OUTPUT);
  
  pinMode(enablePin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  
  pinMode(motor4Pin, OUTPUT);
  
  pinMode(enablePin2, OUTPUT);
  
  Serial.begin(9600);
}
void  loop(){
  
 while (Serial.available()==0);
  
  
  
   buttonState =digitalRead(buttonPin);
    delay(10);

    if(buttonState ==HIGH){
      
       
        Serial.println("9");
        delay(10);
        //digitalWrite(ledPin,HIGH);
        
        //Serial.write(counter);
  
    }
    else if(buttonState==LOW){
      //Serial.println("8");
      digitalWrite(ledPin,LOW);
      
    }
 
     ReadData= Serial.read();
      
      //Serial.println(ReadData,DEC);
      delay(10);
      // if the switch is high, motor will turn on one direction:
      //ReadData=53;
   if(ReadData == 53){
      digitalWrite(enablePin, HIGH);
      
      //delay(10);
      
   }
   else if(ReadData == 52)
    {
    
      digitalWrite(enablePin2,HIGH);
      //delay(10);
    }
   else {
     digitalWrite(enablePin, LOW);
     digitalWrite(enablePin2, LOW);
     //delay(10);
   }

  if (digitalRead(enablePin) == HIGH) {
    
    digitalWrite(motor2Pin, HIGH); // set leg 2 of the H-bridge high
    
    digitalWrite(motor1Pin, LOW); // set leg 1 of the H-bridge low
    
    delay(50);
    
    ReadData=0;
  }
 
  else {
  
    digitalWrite(motor1Pin, LOW); // set leg 1 of the H-bridge high
  
    digitalWrite(motor2Pin, LOW); // set leg 2 of the H-bridge low
  //  delay(10);
   

   
  }
  if (digitalRead(enablePin2) == HIGH) {
    
    digitalWrite(motor4Pin, HIGH); // set leg 2 of the H-bridge high
    
    digitalWrite(motor3Pin, LOW); // set leg 1 of the H-bridge low
    delay(50);
    ReadData=0;
    
  }
    //Serial.read(enablePin);
    // if the switch is low, motor will turn in the other direction:
  else {
  
    digitalWrite(motor4Pin, LOW); // set leg 1 of the H-bridge high
  
    digitalWrite(motor3Pin, LOW); // set leg 2 of the H-bridge low
    //delay(10);
    
  }


}
