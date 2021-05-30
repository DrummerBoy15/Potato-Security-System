#include <Key.h>
#include <Keypad.h>



const byte keyRows = 4; 
const byte keyCols = 4; 
char keys [keyRows][keyCols] = {
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'}  
  
};
byte rowPins[keyRows] = {9,8,7,6};  
byte colPins[keyCols] = {5,4,3,2};  
const int echo = 11;
const int trig = 12; 
const int ledPin = 13; 
int i = 0; 
String password; 
bool buzz = false; 
String entered; 

Keypad keyboard = Keypad(makeKeymap(keys),rowPins, colPins, keyRows, keyCols);  
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); 
  pinMode(echo, INPUT); 
  pinMode(trig, OUTPUT); 
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  char keyPressed; 
  if ( i == 0){
    while (keyPressed != '#'){
      password = password + String(keyPressed); 
      Serial.println(password);
      keyPressed = keyboard.getKey();  
    }
    digitalWrite(ledPin, HIGH); 
    delay(100); 
    digitalWrite(ledPin, LOW); 
    delay(30000);
    digitalWrite(ledPin, HIGH); 
    delay(500); 
    digitalWrite(ledPin, LOW);  
    i++; 
  }
  else{
  long pulse1; 
  long pulse2;
  
  Serial.print(keyPressed);  
  if (buzz == true){
     
  }
  digitalWrite(trig, HIGH); 
  delayMicroseconds(50); 
  digitalWrite(trig, LOW); 

  pulse1 = pulseIn(echo, HIGH); 
  //Serial.println(String(pulse1));
  delay(10); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(50); 
  digitalWrite(trig, LOW); 

  pulse2 = pulseIn(echo, HIGH); 
  //Serial.println(String(pulse2));
  delay(10); 
  entered = entered + String(keyboard.getKey());
  if (entered.length() > password.length()){
    if (entered != password){
      Serial.println("YALALALALA"); 
      Serial.println(entered); 
      entered = ""; 
      digitalWrite(ledPin, LOW); 
      delay(500); 
      digitalWrite(ledPin, HIGH);
    } 
  }
  if (entered == password){
    digitalWrite(ledPin, LOW); 
  }
  Serial.println(entered); 
  if (pulse1-pulse2 >= 1000 || pulse2-pulse1 >= 1000 && entered != password ){
      if (entered == password){
        
      }
      else {
        Serial.println("Alert Alert");
        digitalWrite(ledPin, HIGH);  
        bool buzz = true;
      }
       
       
  }
  } 
  
  
  
}
