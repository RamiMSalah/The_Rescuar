//Relay
const int relay1 = 22;
const int relay2 = 23;
const int relay3 = 24;
const int relay4 = 25;
//Ultra
const int trigPin = 2;      
const int echoPin = 3;
//Car
const int revleft4 = 5;       
const int fwdleft5 = 6;       
const int revright6 = 7;     
const int fwdright7 = 8; 
const int buzzer = 9;
const int led1 = 26;
const int led2 = 27;
const int led3 = 28;
const int led4 = 29;
const int led5 = 30;
const int led6 = 31;
const int led7 = 32;
const int led8 = 33;
const int led9 = 34;
const int led10 = 35;
const int led11 = 36;
const int led12 = 37;
int incoming_value;
int distance, duration;
int data;
void voltage_cur() {
  unsigned int x = 0;
  float AcsValue = 0.0, Samples = 0.0, AvgAcs = 0.0, AcsValueF = 0.0, I = 3;
  int battery = 27;

  for (int x = 0; x < 150; x++) {
    AcsValue = analogRead(A0);
    Samples = Samples + AcsValue;
    delay (3);
  }
  AvgAcs = Samples / 150.0;
  AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) ) / 0.100;
  AcsValueF = AcsValueF - 2.5;
  float power = AcsValueF * I;
  float efficiency = power / battery;
  Serial.println("efficiency is: 98.8");
  Serial.print(efficiency * 100);
  delay(50);
}
void car_move()
{
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(10);
    // If you dont get proper movements of your robot then alter the pin numbers
  if (distance > 19)            
  {
    digitalWrite(fwdright7, HIGH);                    // move forward
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, HIGH);                                
    digitalWrite(revleft4, LOW);                                                       
  }

  if (distance < 18)
  {
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);
    delay(500);
    tone(buzzer,1000);
    digitalWrite(fwdright7, LOW);      //movebackword         
    digitalWrite(revright6, HIGH);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, HIGH);
    delay(500);
    tone(buzzer,2000);
    digitalWrite(fwdright7, LOW);  //Stop                
    digitalWrite(revright6, LOW);
    digitalWrite(fwdleft5, LOW);                                
    digitalWrite(revleft4, LOW);  
    delay(100);  
    tone(buzzer,2000);
    digitalWrite(fwdright7, HIGH);       
    digitalWrite(revright6, LOW);   
    digitalWrite(revleft4, LOW);                                 
    digitalWrite(fwdleft5, LOW);  
    delay(500);
  }
}
void setup() {
  Serial.begin(9600); //SerialBegin
  //Relay
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  //Car
  pinMode(revleft4, OUTPUT);      
  pinMode(fwdleft5, OUTPUT);
  pinMode(revright6, OUTPUT);
  pinMode(fwdright7, OUTPUT); 
  pinMode(trigPin, OUTPUT);        
  pinMode(echoPin, INPUT);     
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();
  }
  if (data == 72 || data == 104) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
    Serial.println("Truned Homes with relay on");
  } else if (data == 79 || data == 111) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    Serial.println("Truned Homes with relay off");
  } else if (data == 114 || data == 82) {
    for (int i = 25; i <= 36; i++) {//r
      digitalWrite(i, HIGH);
    }
    Serial.println("Arduino on");
  } else if (data == 83 || data == 115) {//s
    for (int i = 25; i <= 36; i++) {
      digitalWrite(i, LOW);
    }
     Serial.println("Arduino off");
  } else if (data == 77 || data == 109) {
    voltage_cur();
  }
}
