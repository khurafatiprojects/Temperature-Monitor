
// include the library code:

#include "DHT.h"
#include <LiquidCrystal_I2C.h>


// initialize the library by associating any needed LCD interface pin
LiquidCrystal_I2C lcd(0x27,16,2);     // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(D3, DHT11);                  // set the GPIO Pin no and Type of DHT sensor
void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHT11 Started!"));
  // For Writing the Welcome screen on the LCD
  // Print a message to the LCD.
  lcd.setCursor(4,0);
  lcd.print("WELCOME");
  lcd.setCursor(7,1);
  lcd.print("TO");
  delay(1000);
  lcd.setCursor(2,0);
  lcd.print("TEMPERATURE");
  lcd.setCursor(4,1);
  lcd.print("MONITOR");
  delay(2000);
  dht.begin();
}

void loop() {
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Not Found");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // for Output in Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // Print Values to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Temp  : ");
  lcd.print(t);
  lcd.print((char)223);// for Degree(°) 
  lcd.print("C   ");
  lcd.setCursor(0, 1);
  lcd.print("Humid : ");
  lcd.print(h);
  lcd.print("%");
  
}
