//Ultrasonic setup variable
#include <LiquidCrystal.h>
#define trigPin 6
#define echoPin 7
//lcd pin list
int lcdRS = 13;
int lcdE = 11;
int lcdD4 = 10;
int lcdD5 = 9;
int lcdD6 = 8;
int lcdD7 = 22;
//button setup pin
int buttonRead = 8;
int buzzerPin = 12;
//led setup pin
int y1Pin = 5;
int redPin = 4;
int y2Pin = 3;
int greenPin = 2;
//variable for statement related
int safeState;
int riskyState;
int dangerState;
String lcdStatement[4] = {"Crash Distance", "Risky Distance", "Safe Distance ", "Distance: "};
String line0[] = {"                "};

LiquidCrystal lcd(lcdRS, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonRead, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(y1Pin, OUTPUT);
  pinMode(y2Pin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);


}

void loop() {
  // put your main code here, to run repeatedly:
  distance_display();
  delay(80);
  
}
void distance_display()
{
  long duration, distance;
  float distance2;
  digitalWrite(trigPin, LOW);
  noTone(buzzerPin);
  digitalWrite(redPin, dangerState);
  digitalWrite(greenPin, safeState);
  digitalWrite(y1Pin, riskyState);
  digitalWrite(y2Pin, riskyState);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;//integers value
  distance2 = (duration / 2) / 29.1;//decimal value


  if (distance >= 75 || distance <= 0)
  {
    safeState = 1;
    riskyState = 0;
    dangerState = 0;
    digitalWrite(redPin, dangerState);
    digitalWrite(greenPin, safeState);
    digitalWrite(y1Pin, riskyState);
    digitalWrite(y2Pin, riskyState);
    Serial.print(lcdStatement[3]);
    Serial.print(distance2);
    Serial.print(" cm");
    Serial.println(line0[0]);
    lcd.setCursor(0,0);
    lcd.print(lcdStatement[3]);
    lcd.print(distance2);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print(lcdStatement[2]);
    
  }
  else if (distance > 25) {
    safeState = 0;
    riskyState = 1;
    dangerState = 0;
    digitalWrite(greenPin, safeState);
    digitalWrite(redPin, dangerState);
    digitalWrite(y1Pin, riskyState);
    digitalWrite(y2Pin, riskyState);
    Serial.print(lcdStatement[3]);
    Serial.print(distance2);
    Serial.print(" cm");
    Serial.println(line0[0]);
    lcd.setCursor(0,0);
    lcd.print(lcdStatement[3]);
    lcd.print(distance2);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print(lcdStatement[1]);
    

  }
  else
  {
    safeState = 0;
    riskyState = 0;
    dangerState = 1;
    digitalWrite(greenPin, safeState);
    Serial.print(lcdStatement[3]);
    Serial.print(distance2);
    Serial.print(" cm");
    Serial.println(line0[0]);
    tone(buzzerPin, 500);
    digitalWrite(redPin, dangerState);
    digitalWrite(y1Pin, riskyState);
    digitalWrite(y2Pin, riskyState);
    lcd.setCursor(0,0);
    lcd.print(lcdStatement[3]);
    lcd.print(distance2);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print(lcdStatement[0]);
    


  }
}
