int ADCV=A0;
int LED = 5;
int buzzer =9;
int atomizationPin = 4;
const int transistor = 2;
    

#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define DHTPIN 4
#define DHTPIN2 3 
#define DHTTYPE DHT22
#define DHTTYPE2 DHT22  
 
LiquidCrystal_I2C lcd(0x20,16,2);
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE2);

void setup() {
  lcd.init();
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  pinMode (transistor, OUTPUT);
  pinMode(atomizationPin, OUTPUT);
  dht.begin();
  dht2.begin();
}

void loop() {
  
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  float f2 = dht2.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.backlight();
    lcd.print("Reading Failed");
    delay(5000);
    lcd.clear();
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F"); 
  
  Serial.print("Temperature Second Sensor ");
  Serial.print(t2);
  Serial.println(" C");
  
 if (t2 > 32)
 {
  digitalWrite (transistor, HIGH);
 }
 else
  digitalWrite (transistor, LOW);



if (h < 95)
{
digitalWrite(atomizationPin, LOW);
}
else
digitalWrite(atomizationPin,HIGH);
}


  
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Room Temp: ");
  lcd.print(t);
  lcd.setCursor(1,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  delay(3000);
  lcd.clear();
}
