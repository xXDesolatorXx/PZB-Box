/*
PZB Receiver 0.1
Made by Fabian Witzel
*/


#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int a;

} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.a);
  Serial.print("Int: ");

if (myData.a == 500){
    digitalWrite(18,HIGH);
    delay(1000);
    digitalWrite(18,LOW);
}
if (myData.a == 1000){
    digitalWrite(19,HIGH);
    delay(1000);
    digitalWrite(19,LOW);
}
if (myData.a == 2000){
    digitalWrite(21,HIGH);
    delay(1000);
    digitalWrite(21,LOW);
}
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  pinMode(18,OUTPUT); //500
  pinMode(19,OUTPUT); //1000
  pinMode(21,OUTPUT); //2000

  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}