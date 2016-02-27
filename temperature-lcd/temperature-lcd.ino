/*
  Temperature
  Takes temperature from sensor and displays on a sma420564 4 digit 7 segment display 

  My first ever using C
  My first ever Arduino sketch
  by Ben Williams
 */

const int ledCount = 12;
float temp = 0; 
int sensorPin = 0;



// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.begin(9600);

  setNumber(4,5);

  
}

void turnAllOff() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}



void turnAllSegOff(){
  digitalWrite(13, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(12, HIGH);
}

void setSeg(int num, bool othersOff){
  if(othersOff){
    turnAllSegOff();
  } 
  switch(num){
    case 1 : 
      digitalWrite(13,LOW);
      break;
    case 2 : 
      digitalWrite(4,LOW);
      break;
    case 3 : 
      digitalWrite(5,LOW);
      break;
    case 4 : 
      digitalWrite(12,LOW);
      break;
  }
}

void setDigit(int num){
  //turnAllOff();
  switch(num){
    case 1:
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      break;
    case 2: 
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 3:
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 4:
      digitalWrite(3, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      break;
    case 5:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 6:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 7:
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(10, HIGH);
      break;
    case 8:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      break;
    case 9:
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 0:
      digitalWrite(3, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(8, HIGH);
      break;
  }
}

void showPoint(){
  digitalWrite(9, HIGH);
}

void hidePoint(){
  digitalWrite(9, LOW);
}

void getTemp(){
 int reading = analogRead(sensorPin);  

 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // print out the voltage
 //Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" degrees C");

 temp = temperatureC;
}

void loop() {
  getTemp();
  readTemp();
}



void setNumber(int pos, int num){
  setSeg(pos, true);
  setDigit(num);
}

void readTemp(){
  int tempToInt = (int)temp;
  double decPart = temp - tempToInt;
  int segment = 4;
  int num1 = 0;
  int num2 = 0;
  int num3 = 0;
  int num4 = 0;

  
  //Serial.print(intpart);

  while(tempToInt){
    setSeg(segment, true);
    turnAllOff();
    
    switch(segment){
      case 4:
        num2 = tempToInt % 10;
        break;
      case 3:
        num1 = tempToInt % 10;
        break;
      case 2:
        num2 = tempToInt %10;
        break;
      case 1: 
        num1 = tempToInt %10;
    }

    num4 = ((int)(decPart * 100) % 10);
    num3 = ((int)(decPart * 10) % 10);

   // Serial.print(num3); Serial.print("num3, num4 "); Serial.println(num4);

    
    tempToInt /= 10;
    segment -= 1;
  }
  
  displayFullNumber(num1, num2, num3, num4);
  
}

void displayFullNumber(int num1, int num2, int num3, int num4){

  for(int i = 0; i < 1000; i++){
    setSeg(1, true);
    setDigit(num1);
    turnAllOff();
    setSeg(2, true);
    setDigit(num2);
    showPoint();
    turnAllOff();
    setSeg(3, true);
    setDigit(num3);
    turnAllOff();
    setSeg(4, true);
    setDigit(num4);
    turnAllOff();
  }
  
}




