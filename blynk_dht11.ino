/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>


// initialize the library by associating any needed LCD interface pin
LiquidCrystal_I2C lcd(0x27,16,2);     // set the LCD address to 0x27 for a 16 chars and 2 line display

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "jmzs76_IhJ0Z2t4WwmffA_FeqNOrbuuB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "khurafati";
char pass[] = "h!m@n$hu97";

#define DHTPIN D3          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  Blynk.virtualWrite(V5,(int) h);
  Blynk.virtualWrite(V6, (int)t);
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

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
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

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
