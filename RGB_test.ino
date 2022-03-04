int rPin = 7;
int gPin = 6;
int bPin = 5;
int dt = 10;
int bob;
int sheesh;
int lol;
int buttonPin = 2;
int buttonRead;
int initialState;
int currentState = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  randomSeed(analogRead(0));

}
void setColor(int red, int green, int blue)// function for the RGB output
{
  int normal = 255;
  red = normal - red;
  green = normal - green;
  blue = normal - blue;

  analogWrite(rPin, red);
  analogWrite(gPin, green);
  analogWrite(bPin, blue);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonRead = digitalRead(buttonPin);
  Serial.println(buttonRead);
  
  if (buttonRead == 1 and initialState == 0) {
    if (currentState == LOW)
    {
      currentState = HIGH;
      bob = random(0, 255);
      sheesh = random(0, 255);
      lol = random(0, 255);
      
      Serial.print("1st State"); // Serial Monitor list
      Serial.print(". RGB: ");
      Serial.print(lol);
      Serial.print("\t");
      Serial.print(sheesh);
      Serial.print("\t");
      Serial.print(bob);
      Serial.println();
      setColor(lol, sheesh, bob);
    }
    else {
      currentState = LOW;
      setColor(0, 0, 0);
      bob = random(0, 255);
      sheesh = random(0, 255);
      lol = random(0, 255);
      
      Serial.print("2nd State"); // Serial Monitor list
      Serial.print(". RGB: ");
      Serial.print(lol);
      Serial.print("\t");
      Serial.print(sheesh);
      Serial.print("\t");
      Serial.print(bob);
      Serial.println();
      setColor(lol, sheesh, bob);
    }
  }
 
  initialState = buttonRead;
  Serial.println(initialState);
  delay(dt);
}
