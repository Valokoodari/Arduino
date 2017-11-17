#include <LiquidCrystal.h>

LiquidCrystal lcd(1,2,4,5,6,7);

int swState = 0;
int prevSwState = 0;
int color = 0;
int sensorVal = 0;
int sensVolt1 = 0;
int sensVolt2 = 0;
int count = 0;
float voltage = 0.0;
float sensVoltage = 0.0;
String colorW = "Red";

void setup() {
  lcd.begin(16,2);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
}

void loop() {
  prevSwState = swState;
  swState = digitalRead(13);
  sensorVal = analogRead(A0);
  sensVolt1 = analogRead(A1);
  sensVolt2 = analogRead(A2);
  sensVoltage = (abs(sensVolt1 - sensVolt2) / 1024.0) * 5.0;
  voltage = (sensorVal / 1024.0) * 5.0;

  if (swState == HIGH && prevSwState == LOW) {
    if (color == 0) {
      color = 1;
      colorW = "Green";
    } else if (color == 1) {
      color = 2;
      colorW = "Both";
    } else {
      color = 0;
      colorW = "Red";
    }
  }

  if (color == 0) {
    digitalWrite(8, LOW);
    analogWrite(12, sensorVal/4);
    delay(10);
  } else if (color == 1) {
    digitalWrite(12, LOW);
    analogWrite(8, sensorVal/4);
    delay(10);
  } else {
    digitalWrite(8, LOW);
    analogWrite(12, sensorVal/4);
    delay(5);
    digitalWrite(12, LOW);
    analogWrite(8, sensorVal/4);
    delay(5);
  }
  if (count == 50) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Source: ");
    lcd.print(voltage);
    lcd.print(" V");
    lcd.setCursor(0,1);
    lcd.print("LED: ");
    lcd.print(sensVoltage);
    lcd.print(" V");
    count = 0;
  } else {
    count++;
  }
}
