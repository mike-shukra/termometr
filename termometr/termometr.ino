#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;

#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
void setup()
{
  Serial.begin(9600);
  delay(100);
  
  lcd.init();                     
//  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Humidite");
}
void loop() {
      a=sr04.Distance();
      Serial.print(a);
      Serial.println("cm");
      delay(1000);
      
   if (a > 1 && a < 60) {
      Serial.println("yes");
      lcd.backlight();// Включаем подсветку дисплея
  
      // start working...
      Serial.println("=================================");
      Serial.println("Sample DHT11...");
      
      // read with raw sample data.
      byte temperature = 0;
      byte humidity = 0;
      byte data[40] = {0};
      if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
        Serial.print("Read DHT11 failed");
        return;
      }
      
      Serial.print("Sample RAW Bits: ");
      for (int i = 0; i < 40; i++) {
        Serial.print((int)data[i]);
        if (i > 0 && ((i + 1) % 4) == 0) {
          Serial.print(' ');
        }
      }
      Serial.println("");
      
      Serial.print("Sample OK: ");
      Serial.print((int)temperature); Serial.print(" *C, ");
      Serial.print((int)humidity); Serial.println(" %");
      
      // DHT11 sampling rate is 1HZ.
      delay(100);
    
      // Устанавливаем курсор на первую строку и 12 символ.
      lcd.setCursor(12, 0);
      // Выводим на экран
      lcd.print((int)temperature); lcd.print("*C");
      
      // Устанавливаем курсор на вторую строку и 9 символ.
      lcd.setCursor(9, 1);
      // Выводим на экран
      lcd.print((int)humidity); lcd.println("%    ");
   }
   else {     
      lcd.noBacklight();// Выключаем подсветку дисплея
   }
}
