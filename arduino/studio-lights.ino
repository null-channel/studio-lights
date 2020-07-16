#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <SPI.h>
//#include <WiFi.h>
//#include <WiFi101.h>

#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

//Defines - used as constants, not good practice in c++
#define PIN_1 6
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4

#define RELAY_PIN_1 = 8
#define RELAY_PIN_2 = 9

#define BANK_SIZE 16
#define DELAY 5000

//Global variables - again not good practice in other "real" programming
char ssid[] = "ssid";     //  your network SSID (name)
char pass[] = "yourpass";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char serverAddress[] = "10.1.1.50";  // server address
int port = 32001;
WiFiClient wifi;

HttpClient client = HttpClient(wifi, serverAddress, port);

Adafruit_NeoPixel pixels_1(BANK_SIZE, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2(BANK_SIZE, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_3(BANK_SIZE, PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_4(BANK_SIZE, PIN_4, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  pixels_1.begin();
  pixels_2.begin();
  pixels_3.begin();
  pixels_4.begin();

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  connectToWifi();
  Serial.println("connected");
}

void connectToWifi() {
  Serial.println("Starting Wifi");
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);
    Serial.println(pass);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("connected");
}

void loop() {
  // Check WiFi Status
  int red = 255;
  int blue = 255;
  int green = 255;
  bool is_on = false;
  
  //If connected to the wifi, make a request
  if (WiFi.status() != WL_CONNECTED) {
    connectToWifi();
  }

  client.get("/lights");
  //Check the returning code                                                                  
  if (client.responseStatusCode() > 0) {
    // Get the request response payload
    // TODO: Parsing

    const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4) + 30;
    DynamicJsonDocument doc(capacity);

    const char* json = "{\"Status\":{\"On\":true},\"Red\":0,\"Blue\":50,\"Green\":50}";

    deserializeJson(doc, client.responseBody());

    is_on = doc["Status"]["On"]; // true

    red = doc["Red"]; // 0
    blue = doc["Blue"]; // 50
    green = doc["Green"]; // 50
    Serial.println(red);
  }

  Serial.println(red);

  //right now we will turn both on, or none. could split this out later
  if (is_on) {
    digitalWrite(RELAY_PIN_1,HIGH);
    digitalWrite(RELAY_PIN_2,HIGH);
  }

  //Manage the light color right now all banks have the same color, could change this in the future
  //first clear them;
  pixels_1.clear();
  pixels_2.clear();
  pixels_3.clear();
  pixels_4.clear();
  uint32_t magenta = pixels_1.Color(red, blue, green);

  //fill them with the correct collor
  pixels_1.fill(magenta,0,BANK_SIZE);
  pixels_2.fill(magenta,0,BANK_SIZE);
  pixels_3.fill(magenta,0,BANK_SIZE);
  pixels_4.fill(magenta,0,BANK_SIZE);

  //must call show to acctually update them
  pixels_1.show();
  pixels_2.show();
  pixels_3.show();
  pixels_4.show();

  Serial.println("sleeping");
  delay(DELAY);
}
