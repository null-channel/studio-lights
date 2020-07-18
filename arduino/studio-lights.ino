#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <SPI.h>

#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

/* 
 *  Defines - used as constants, not good practice in c++.
 *  expanded when compiled  
 *  can be cool, but don't over use.
 */
#define PIN_1 5
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4

//BANK_SIZE is the number of lights in a bank of lights, used to fill
#define BANK_SIZE 16
//How often to check for updates in miliseconds
#define DELAY 5000

struct light {
  int number, red, green, blue;
} l0,l1,l2,l3 ;

//Global variables - again not good practice in other "real" programming
char ssid[] = "The Prancing Pony";     //  your network SSID (name)
char pass[] = "M@r3k1553xy1!";  // your network password
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

void collorize(Adafruit_NeoPixel* pixel, uint32_t color, int bank_size) {
  pixel->clear();
  pixel->fill(color,0,bank_size);
  pixel->show();
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

    const size_t capacity = JSON_ARRAY_SIZE(4) + 4*JSON_OBJECT_SIZE(4) + 100;
    DynamicJsonDocument doc(capacity);
    
    const char* json = "[{\"Number\":0,\"Red\":255,\"Blue\":50,\"Green\":255},{\"Number\":1,\"Red\":255,\"Blue\":255,\"Green\":0},{\"Number\":2,\"Red\":0,\"Blue\":50,\"Green\":50},{\"Number\":3,\"Red\":0,\"Blue\":100,\"Green\":10}]";

    deserializeJson(doc, client.responseBody());
    
    
    JsonObject lights_0_light = doc[0];
    l0.number = lights_0_light["Number"];
    l0.blue = lights_0_light["Blue"];
    l0.green = lights_0_light["Green"];
    l0.red = lights_0_light["Red"];
    
    JsonObject lights_1_light = doc[1];
    l1.number = lights_1_light["Number"];
    l1.blue = lights_1_light["Blue"];
    l1.green = lights_1_light["Green"];
    l1.red = lights_1_light["Red"];
    
    JsonObject lights_2_light = doc[2];
    l2.number = lights_2_light["Number"];
    l2.blue = lights_2_light["Blue"];
    l2.green = lights_2_light["Green"];
    l2.red = lights_2_light["Red"];
    
    JsonObject lights_3_light = doc[3];
    l3.number = lights_3_light["Number"];
    l3.blue = lights_3_light["Blue"];
    l3.green = lights_3_light["Green"];
    l3.red = lights_3_light["Red"];
    
    Serial.println(l3.red);
    Serial.println(l3.blue);
    Serial.println(l3.green);
    
  }

  //Manage the light color right now all banks have the same color, could change this in the future
  uint32_t color = pixels_1.Color(l0.red, l0.green, l0.blue);
  collorize(&pixels_1, color, BANK_SIZE); 
  color = pixels_1.Color(l1.red, l1.green, l1.blue);
  collorize(&pixels_2, color, BANK_SIZE); 
  color = pixels_1.Color(l2.red, l2.green, l2.blue);
  collorize(&pixels_3, color, BANK_SIZE); 
  color = pixels_1.Color(l3.red, l3.green, l3.blue);
  collorize(&pixels_4, color, BANK_SIZE); 

  Serial.println("wait a second to call the api again");
  delay(DELAY);
}
