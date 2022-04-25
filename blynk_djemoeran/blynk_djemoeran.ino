/*************************************************************

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

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL2B0KOv8k"
#define BLYNK_DEVICE_NAME "Djemoeran Dev"
#define BLYNK_AUTH_TOKEN "WjCalS1EeT31Rc3LVsOKDtlg6sQRVy6H"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


//#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Burangrang";
char pass[] = "Legokhaji2022";

#define DHTPIN 4          // What digital pin we're connected to
#define RAINPIN 23
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
int rain;
bool eventTrigger = false;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  rain = digitalRead(RAINPIN);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V2, rain);
  Serial.print("Temperature :");
  Serial.print(t);
  Serial.print("    Humidity : ");
  Serial.print(h);
  Serial.print("    Hujan: ");
  Serial.print(rain);
//  Blynk.logEvent("TEMP", "Check");
//  Blynk.logEvent("HUJAN", "Angkat jemuran!!");
  Blynk.logEvent("HUJAN", "Angkat jemuran!!");
  Blynk.notify("ASDASD");
  if (rain == 0) {
    eventTrigger = true;
    
    Blynk.logEvent("HUJAN", "Angkat jemuran!!");
    Blynk.notify("ASDASD");
  }
  else if (rain == 1) {
    eventTrigger = false;
  }
  Serial.println("");
  Serial.print("evenTrigger");
  Serial.print(eventTrigger);
  Serial.println("");
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();
  pinMode(RAINPIN,INPUT);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
