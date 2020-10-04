#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>                                     // Responsible for communication with API via HTTP requests.
#include <PubSubClient.h>
#include <NTPClient.h>                                            // Responsible for the handling of time.
#include <WiFiUdp.h>                                              // ^
#include "secrets.h"

const char* ssid = MY_SSID;
const char* password = MY_PASS;
const char* mqtt_server = MY_IP;


#define A 12
#define B 14
#define C 4

boolean useClockA = false;
int dayA;
int hoursA;
int minutesA;
int secondsA;

boolean useClockB = false;
int dayB;
int hoursB;
int minutesB;
int secondsB;

boolean useClockC = false;
int dayC;
int hoursC;
int minutesC;
int secondsC;

WiFiClient espClient;
PubSubClient client(espClient);
IPAddress HOST(MY_IP_a,MY_IP_b,MY_IP_c,MY_IP_d);                            // Host for the HTTP requests. note: to use an IP address as host IPAddress is needed.


#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

/* ----------------------------
  Time implementation
 ---------------------------- */
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 7200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


// ------------------------------------------------------------------------------------------------------------------------------------------------ WIFI
void setup_wifi() {
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// ------------------------------------------------------------------------------------------------------------------------------------------------ CALLBACK
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  timeClient.update();

  switch ((char)payload[0]){

    case 'A':
      if ((char)payload[1] == '1'){
        digitalWrite(A, HIGH);
        useClockA = false;
        
      } else if ((char)payload[1] == '0'){
        digitalWrite(A, LOW);
        useClockA = false;
        
      } else if ((char)payload[1] == 'T'){

        digitalWrite(A, HIGH);

        useClockA = true;
        
        dayA = timeClient.getDay();
        dayA %= 7;
        
        hoursA = ((String)(char)payload[2] + (String)(char)payload[3]).toInt() + timeClient.getHours();
        dayA += hoursA / 24;
        hoursA %= 24;
        
        minutesA = ((String)(char)payload[4] + (String)(char)payload[5]).toInt() + timeClient.getMinutes();
        hoursA += minutesA / 60;
        minutesA %= 60;

        secondsA = timeClient.getSeconds() + 10;
        secondsA %= 60;

        Serial.print("Clock set for A ");
        Serial.print(dayA); Serial.print(" - "); Serial.print(hoursA); Serial.print(":"); Serial.print(minutesA); Serial.print(":"); Serial.print(secondsA); Serial.println();
        
      }
      break;

    case 'B':
      if ((char)payload[1] == '1'){
        digitalWrite(B, HIGH);
        useClockB = false;
        
      } else if ((char)payload[1] == '0'){
        digitalWrite(B, LOW);
        useClockB = false;
        
      } else if ((char)payload[1] == 'T'){

        digitalWrite(B, HIGH);

        useClockB = true;
        
        dayB = timeClient.getDay();
        dayB %= 7;
        
        hoursB = ((String)(char)payload[2] + (String)(char)payload[3]).toInt() + timeClient.getHours();
        dayB += hoursB / 24;
        hoursB %= 24;
        
        minutesB = ((String)(char)payload[4] + (String)(char)payload[5]).toInt() + timeClient.getMinutes();
        hoursB += minutesB / 60;
        minutesB %= 60;

        secondsB = timeClient.getSeconds() + 10;
        secondsB %= 60;

        Serial.print("Clock set for B ");
        Serial.print(dayB); Serial.print(" - "); Serial.print(hoursB); Serial.print(":"); Serial.print(minutesB); Serial.print(":"); Serial.print(secondsB); Serial.println();
        
      }
      break;

    case 'C':
      if ((char)payload[1] == '1'){
        digitalWrite(C, HIGH);
        useClockC = false;
        
      } else if ((char)payload[1] == '0'){
        digitalWrite(C, LOW);
        useClockC = false;
        
      } else if ((char)payload[1] == 'T'){

        digitalWrite(C, HIGH);

        useClockC = true;
        
        dayC = timeClient.getDay();
        dayC %= 7;
        
        hoursC = ((String)(char)payload[2] + (String)(char)payload[3]).toInt() + timeClient.getHours();
        dayC += hoursC / 24;
        hoursC %= 24;
        
        minutesC = ((String)(char)payload[4] + (String)(char)payload[5]).toInt() + timeClient.getMinutes();
        hoursC += minutesC / 60;
        minutesC %= 60;

        secondsC = timeClient.getSeconds() + 10;
        secondsC %= 60;

        Serial.print("Clock set for C ");
        Serial.print(dayC); Serial.print(" - "); Serial.print(hoursC); Serial.print(":"); Serial.print(minutesC); Serial.print(":"); Serial.print(secondsC); Serial.println();
        
      }
      break;

  }
}

// ------------------------------------------------------------------------------------------------------------------------------------------------ RECONNECT
void reconnect() {
  // Loop until we're reconnected
  digitalWrite(BUILTIN_LED, LOW);
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection... ");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      
      client.publish("RPi", "ESP001 - OK");
      client.subscribe("ESP001");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in .5 seconds");
      // Wait .5 seconds before retrying
      delay(500);
    }
  }
  digitalWrite(BUILTIN_LED, HIGH);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------ CLOCK
void clockCheckLoop() {
  
  timeClient.update();
  int currentDay = timeClient.getDay();
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();
  if (useClockA) {
      if (currentDay >= dayA and currentHour >= hoursA and currentMinute >= minutesA and currentSecond >= secondsA) {
        digitalWrite(A, LOW);
        useClockA = false;
        toggleDatabase("ESP001-A");
      }
  } 

  if (useClockB) {
      if (currentDay >= dayB and currentHour >= hoursB and currentMinute >= minutesB and currentSecond >= secondsB) {
        digitalWrite(B, LOW);
        useClockB = false;
        toggleDatabase("ESP001-B");
      }
  }

  if (useClockC) {
      if (currentDay == dayC and currentHour == hoursC and currentMinute == minutesC and currentSecond >= secondsC) {
        digitalWrite(C, LOW);
        useClockC = false;
        toggleDatabase("ESP001-C");
      }
  }
  
}

void toggleDatabase(String DEVICE_ID) {

  Serial.print("Made request [POST]...");

  if (!espClient.connect(HOST, MY_PORT_apache))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  // give the esp a breather
  yield();

  String data = String("id=") + DEVICE_ID;
  int dataLength = data.length();

  // Send HTTP request
  espClient.print(F("POST "));
  espClient.print("/database/toggleState.php");
  espClient.println(F(" HTTP/1.1"));

  //Headers
  espClient.print(F("Host: "));
  espClient.println(HOST);
  espClient.println(F("Accept: application/json"));
  espClient.println(F("Content-Type: application/x-www-form-urlencoded"));
  espClient.print(F("Content-Length: "));
  espClient.println(dataLength);
  espClient.println();
  espClient.println(data);

  if (espClient.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return;
  } 
  
  // Check HTTP status
  char status[32] = {0};
  espClient.readBytesUntil('\r', status, sizeof(status));

  Serial.println(" DONE");

}

// ------------------------------------------------------------------------------------------------------------------------------------------------ SETUP
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);     
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, MY_PORT_mqtt);
  client.setCallback(callback);
  timeClient.begin();
  digitalWrite(BUILTIN_LED, HIGH);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------ LOOP
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  clockCheckLoop();
  
}
