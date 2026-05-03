/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL22oTbWptc"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "uoE3J3yRcQNDPbG5b4YggABllCxwLfKW"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HammangaTest";
char pass[] = "doncorleone26";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

const int ledPin = 9; // We are using pin 8 for the LED // We are using pin 9 for the Relay
WidgetLED ledWidget(V0);
BlynkTimer timer;

// Select your pin with physical button
BLYNK_WRITE(V0) {
  int pinValue = param.asInt(); // Get value from the app button (0 or 1)
  
  if (pinValue == 1) {
    digitalWrite(9, HIGH); // Turn physical LED on
  } else {
    digitalWrite(9, LOW);  // Turn physical LED off
  }
}


void checkPhysicalStatus() {
  // This just updates the App's LED widget to match the physical LED state
  if (digitalRead(ledPin) == HIGH) {
    ledWidget.on();
  } else {
    ledWidget.off();
  }
}
 

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  //Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
  // You can also specify server:
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  // ... your existing setup code ...
  pinMode(9, OUTPUT); // Add this line
 
  // ... rest of your setup ...

  timer.setInterval(500L, checkPhysicalStatus);
}

void loop()
{
  Blynk.run();
  timer.run();
}
