#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft ;

int dt = 500;
//Machine setup variable
#include "tft_setup.h"
#include "byte_var.h"
#include <LedControl.h>
//#include <LiquidCrystal.h>
#define trigPin 31
#define echoPin 30
//lcd pin list
int lcdRS = 32;
int lcdE = 33;
int lcdD4 = 34;
int lcdD5 = 35;
int lcdD6 = 36;
int lcdD7 = 37;
//button setup pin
int buzzerPin = 29 ;
//led setup pin
int redPin = 22;
int y1Pin = 23;
int y2Pin = 24;
int greenPin = 25;
//8x8 matrix pin
int dinPin = 27, clkPin = 26, csPin = 28;
//variable for statement related
int safeState;
int riskyState;
int dangerState;
//ultrasonic output
long duration, distance;//int value
float distance2;//decimals value
//statement display LCD
String lcdStatement[6] = {"Crash Distance  ", "Risky Distance  ", "Safe Distance   ", "Distance: ", " cm", "  "};

//data for the matrix display
unsigned long delaytime = 1000;

LedControl lc = LedControl(dinPin, clkPin, csPin, 1);
//lcd display function
//LiquidCrystal lcd(lcdRS, lcdE, lcdD4, lcdD5, lcdD6, lcdD7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(y1Pin, OUTPUT);
  pinMode(y2Pin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //lcd.begin(16, 2);
  //lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  //lc.setIntensity(0, 2);
  /* and clear the display */
  //lc.clearDisplay(0);
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.begin(ID);
  tft.setRotation(5);
  tft.fillScreen(BLACK);
  tft.fillRoundRect(10, 5, 302, 40, 5, GREY);
  tft_msg(10, 35, 1, &FreeSansBold18pt7b, "RANGE MACHINE");
  tft.fillRoundRect(10, 50, 300, 60, 5, GREY);
  tft.drawRoundRect(10, 50, 300, 60, 5, 0xEF7D);
  tft.drawRoundRect(11, 51, 298, 58, 5, 0xEF7D);
  tft.drawRoundRect(12, 52, 296, 56, 5, 0xEF7D);
  tft_msg(16, 70, 3, NULL, "DISTANCE:");
  tft.fillRoundRect(10, 118, 200, 30, 5, LIGHT_BLUE);
  tft.drawRoundRect(10, 118, 200, 30, 5, 0xEF7D);
  tft.drawRoundRect(11, 1119, 198, 28, 5, 0xEF7D);
  tft_msg(14, 126, 2, NULL, "STATUS:");

}

void loop() {
  // put your main code here, to run repeatedly:
  final_result();
  delay(200);

}
// main function
void final_result()
{

  noTone(buzzerPin);
  digitalWrite(redPin, dangerState);
  digitalWrite(greenPin, safeState);
  digitalWrite(y1Pin, riskyState);
  digitalWrite(y2Pin, riskyState);
  digitalWrite(trigPin, LOW);

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

    displayer(safeState, riskyState, dangerState, distance2);
    //matrix_dis(safe, sizeof(safe) / sizeof(safe[8]));

  }
  else if (distance > 25) {
    safeState = 0;
    riskyState = 1;
    dangerState = 0;

    displayer(safeState, riskyState, dangerState, distance2);
    //matrix_dis(danger, sizeof(danger) / sizeof(danger[8]));
  }
  else
  {
    safeState = 0;
    riskyState = 0;
    dangerState = 1;

    displayer(safeState, riskyState, dangerState, distance2);
    //matrix_dis(toodanger, sizeof(toodanger) / sizeof(toodanger[8]));

  }
}
// function for simple version of both serial and lcd output display logic
void displayer(int safe, int risky, int danger, float ultradis)
{
  int v = 170;
  int v1 = 190;
  int limit1 = 90;
  int limit2 = 65;
  tft.fillRect(10, 150, 200, 85, BLACK);
  tft.fillRect(14, 182, 18, 18, GREY);//logo animation
  tft.fillRect(32, 170, 10, 42, GREY);//logo animation
  tft.fillRect(180, 70, 127, 24, GREY);// clear number screen
  tft.fillRect(96, 126, 110, 16, LIGHT_BLUE);
  tft.fillRect(220, 112, 86, 124, WHITE);
  tft.drawRect(220, 112, 86, 124, GREY);
  ultradis = ultradis - 1;
  String dis = String(ultradis);
  if (safe == 1 && risky == 0 && danger == 0 ) {
    /*lcd.setCursor(0, 0);
      lcd.print(lcdStatement[3]);
      lcd.print(ultradis);
      lcd.print(lcdStatement[5]);
      lcd.setCursor(0, 1);
      lcd.print(lcdStatement[2]);*/
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 180, 200 , v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 200, 200, v1, WHITE);
      v1 += 5;
    }
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "SAFE", GREEN);
  }
  else if (safe == 0 && risky == 1 && danger == 0) {
    /*lcd.setCursor(0, 0);
      lcd.print(lcdStatement[3]);
      lcd.print(ultradis);
      lcd.print(lcdStatement[5]);
      lcd.setCursor(0, 1);
      lcd.print(lcdStatement[1]);*/
    limit1 += ultradis;
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 180, limit1, v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 200, limit1, v1, WHITE);
      v1 += 5;
    }
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "CAUTION", YELLOW);
    tft.fillRoundRect(245, 118, 35, 75, 30, YELLOW);
    tft.fillCircle(260, 215, 14, YELLOW);
  }
  else if (safe == 0 && risky == 0 && danger == 1)
  {
    /*lcd.setCursor(0, 0);
      lcd.print(lcdStatement[3]);
      lcd.print(ultradis);
      lcd.print(lcdStatement[5]);
      lcd.setCursor(0, 1);
      lcd.print(lcdStatement[0]);*/
    limit2 += ultradis;
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 180, limit2, v, WHITE);
      v += 5;
    }
    for (int x = 0; x <= 5; x++) {
      tft.drawLine(50, 200, limit2, v1, WHITE);
      v1 += 5;
    }
    tft_msg(180, 70, 3, NULL, dis);
    tft_signs(96, 126, 2, NULL, "DANGEROUS", RED);
    tft.fillRoundRect(225, 118, 30, 75, 30, RED);
    tft.fillRoundRect(270, 118, 30, 75, 30, RED);
    tft.fillCircle(240, 215, 14, RED);
    tft.fillCircle(285, 215, 14, RED);
    tone(buzzerPin, 50);
  }
  digitalWrite(redPin, danger);
  digitalWrite(greenPin, safe);
  digitalWrite(y1Pin, 0);
  digitalWrite(y2Pin, risky);

}

void clearMatrix()
{
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, 0); // this is for blank
  }
}
void writeMatrix()
{
  /* Letter   */
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, I[i]);
  }

  delay(delaytime);
  clearMatrix();
  /* love */
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, heart[i]);
  }
  delay(delaytime);
  clearMatrix();
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, U[i]);
  }
  delay(delaytime);
  delay(delaytime);
  clearMatrix();
}
void matrix_dis(byte arrayName[], int Size)
{
  for (int i = 0; i < Size; i++) {
    lc.setRow(0, i, arrayName[i]);
  }
}

void tft_msg(int x, int y, int sz, const GFXfont * f, String msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(BLACK);
  tft.setTextSize(sz);
  tft.print(msg);
}
void tft_signs(int x, int y, int sz, const GFXfont * f, String msg, uint16_t color)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(msg);
}
