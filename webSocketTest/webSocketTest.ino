#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>

// Replace with your network credentials
const char* ssid = "TP-LINK_D12FE3";
const char* password = "31133289";

int tau;
int lambda1;
int lambda2;

bool pass = false;
bool test = false;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create a WebSocket object
AsyncWebSocket ws("/ws");

// Json Variable to Hold Sensor Readings
JSONVar readings;

// Get Sensor Readings and return JSON object
String getSensorReadings(int count){
  readings["magneti field"] = String(hallRead());
  readings["count"] = String(count);
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
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notifyClients(String sensorReadings) {
  ws.textAll(sensorReadings);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char*)data;
    // Check if the message is "getReadings"
    if (strcmp((char*)data, "getReadings") == 0) {
      // if it is, send current sensor readings
      String sensorReadings = getSensorReadings(0);
      notifyClients(sensorReadings);
      pass = true;
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
  pinMode(4, OUTPUT);
  initWiFi();
  initWebSocket();

  // Start server
  server.begin();
}

void loop() {
  if(pass) {
    for(int i=0; i<10; i++) {
      digitalWrite(4, HIGH);
      delay(100);
      digitalWrite(4, LOW);
      delay(100);
    }
    pass = false;
  } else if(test) {
    for(int i=lambda1; i<lambda2; i++) {
      Serial.println(i);
      delay(100);
  }
    test = false;
  }
  //for(int i=0; i<1000; i++){
  //  String sensorReadings = getSensorReadings(i);
  //  notifyClients(sensorReadings);
  //  delay(100);
  //}

  ws.cleanupClients();
}
