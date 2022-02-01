#include <Arduino.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_BusIO_Register.h> //Без этого он не может зарегать устройство на шине
#include "Adafruit_SHTC3.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
Adafruit_BMP085 bmp;
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }
Serial.println("SHTC3 test");
  if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");
lcd.init();                      // Инициализация дисплея  
  lcd.backlight();                 // Подключение подсветки
  lcd.setCursor(0,0);              // Установка курсора в начало первой строки
  lcd.print("Welcome home");       // Набор текста на первой строке
  lcd.setCursor(0,1);              // Установка курсора в начало второй строки
  lcd.print("Eshen one");       // Набор текста на второй строке

}

void loop() {
  Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
    delay(500);
sensors_event_t humidity, temp;//Специальная структура для ивентов
  
  shtc3.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");

  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");


  delay(1000);
  // lcd.clear();
  lcd.noDisplay();
  lcd.clear();
  
  lcd.display();
//  float pressuer= bmp.readPressure();
//  int32_t MMRT=pressuer*0.0075;
 Serial.println(bmp.readPressure());
 lcd.setCursor(0,0);
lcd.print(bmp.readPressure());lcd.print(" Pa ");lcd.print(temp.temperature);lcd.print("C");
lcd.setCursor(0,1);
lcd.print(humidity.relative_humidity);lcd.print(" %");
  delay(5000);
}