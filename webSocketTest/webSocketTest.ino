#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>

// Replace with your network credentials
const char* ssid = "TP-LINK_D12FE3";
const char* password = "31133289";

int client_;

int tau;
int lambda1;
int lambda2;

int M0 = 12;
int M1 = 14;
int M2 = 27;
int DIR = 23;
int STEP = 25;
int RESET = 26;
int ENABLE = 13;
int FOTOMULTIPLICADOR = 34;

bool test = false;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 196);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Get Sensor Readings and return JSON object
String getSensorReadings(float nanometer){
  readings["voltaje"] = String(3.3*analogRead(FOTOMULTIPLICADOR)/4096);
  readings["nanometer"] = String(nanometer);
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

String getIP(){
  readings["ip"] = String(WiFi.localIP());
  String jsonString = JSON.stringify(readings);
  return jsonString;
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);   // Connect to WiFi
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  // Blink a LED when the MCU succesfully connect to WiFi
  Serial.println(WiFi.localIP());
}

// This function send the data each time
// notifyClients is called
void notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char*)data;
    // Check if the message is "stop"
    if (strcmp((char*)data, "stop") == 0) {
      test = false;
    } else {
      JSONVar obj = JSON.parse(message);
      String tauString = JSON.stringify(obj["tau"]);
      String lambda1String = JSON.stringify(obj["lambda1"]);
      String lambda2String = JSON.stringify(obj["lambda2"]);

      tauString.replace("\"", "");
      lambda1String.replace("\"", "");
      lambda2String.replace("\"", "");
      
      tau = tauString.toInt();
      lambda1 = lambda1String.toInt();
      lambda2 = lambda2String.toInt();
      test = true;
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      client_ = client->id();
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup() {
  Serial.begin(115200);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  initWiFi();
  initWebSocket();

  pinMode(2, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(FOTOMULTIPLICADOR, INPUT);

  digitalWrite(2, LOW);
  digitalWrite(M0, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(RESET, HIGH);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(ENABLE, HIGH);

  //https://lastminuteengineers.com/esp32-static-ip-tutorial/

  // Start server
  server.begin();
}

void loop() {
  if(test) {

    digitalWrite(RESET, LOW);
    digitalWrite(DIR, LOW);
    delay(3);
    digitalWrite(RESET, HIGH);
    delay(2000);

    for(int i=0; i<(lambda1+3) & test; i++) {
      digitalWrite(2, HIGH);
      digitalWrite(STEP, HIGH);
      digitalWrite(ENABLE, LOW);
      delay(10);
      digitalWrite(2, LOW);
      digitalWrite(ENABLE, HIGH);
      digitalWrite(STEP, LOW);
      delay(10);
    }

    delay(1000);
    
    for(int i=0; i<(lambda2-lambda1) & test; i++) {
      digitalWrite(2, HIGH);
      digitalWrite(STEP, HIGH);
      digitalWrite(ENABLE, LOW);
      delay(tau);
      notifyClients(getSensorReadings(lambda1/4 + i*0.25));
      digitalWrite(2, LOW);
      digitalWrite(ENABLE, HIGH);
      digitalWrite(STEP, LOW);
      delay(tau);
    }

    digitalWrite(DIR, HIGH);
    delay(2000);
    digitalWrite(ENABLE, LOW);
    
    for(int i=0; i<lambda2 & test; i++) {
      digitalWrite(2, HIGH);
      digitalWrite(STEP, HIGH);
      delay(10);
      digitalWrite(2, LOW);
      digitalWrite(STEP, LOW);
      delay(10);
    }
    
    digitalWrite(ENABLE, HIGH);
    test = false;
    ws.closeAll();
  }
}
