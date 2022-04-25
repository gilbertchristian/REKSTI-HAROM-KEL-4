//// for Arduino Microcontroller
//#define rainAnalog A1
//#define rainDigital 2

// for ESP8266 Microcontroller
//#define rainAnalog A0
//#define rainDigital D1

// for ESP32 Microcontroller
//#define rainAnalog 35
#define rainDigital 23

void setup() {
  Serial.begin(9600);
  pinMode(rainDigital,INPUT);
}
void loop() {
//  int rainAnalogVal = analogRead(rainAnalog);
  int rainDigitalVal = digitalRead(rainDigital);

//  Serial.print(rainAnalogVal);
//  Serial.print("\t");
  Serial.println(rainDigitalVal);
  delay(1000);
}
