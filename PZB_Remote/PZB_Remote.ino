
/*  
PZB Remote V0.2

PCB Prototype Version for Akiem Technik

Made by Fabian Witzel
*/

#include <esp_now.h>
#include "WiFi.h"
#include "credentials.h"

//Define a structure for the message
typedef struct struct_message {
  int a;

} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;
//declaring of booleans for each button
bool C5H = false;
bool C1K = false;
bool C2K = false;

volatile unsigned long sinceLastTouchC5H = 0;
volatile unsigned long sinceLastTouchC1K = 0;
volatile unsigned long sinceLastTouchC2K = 0;

bool touchDelayComp(unsigned long);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  
}
//500Hz Button Interrupt
void IRAM_ATTR H500()
{
    C5H = true;
}
//1000Hz Button Interrupt
void IRAM_ATTR H1000()
{
    C1K = true;
}
//2000Hz Button Interrupt
void IRAM_ATTR H2000()
{  
    C2K = true;
}

void setup(){
//Setting up the Pins  
pinMode(17,INPUT_PULLDOWN);
pinMode(18,INPUT_PULLDOWN);
pinMode(19,INPUT_PULLDOWN);
pinMode(21,OUTPUT); //RED
pinMode(22,OUTPUT); //GREEN
pinMode(23,OUTPUT); //BLUE
digitalWrite(21,LOW);
digitalWrite(22,LOW);
digitalWrite(23,LOW);
//Setting up interrupts
attachInterrupt(17,H500,RISING);
attachInterrupt(18,H1000,RISING);
attachInterrupt(19,H2000,RISING);
//Establishing a serial connection for debugging
Serial.begin(115200);
//Setting the WiFi to Station Mode
WiFi.mode(WIFI_STA);

if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    digitalWrite(22,LOW);
    digitalWrite(21,HIGH);
    return; 
  }
  else {
   digitalWrite(22,HIGH);
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop(){
//500Hz Loop
if (C5H)
{
C5H = false;
    if (touchDelayComp(sinceLastTouchC5H))
    {
     myData.a = 500;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(21,LOW);
    digitalWrite(22,LOW);
    digitalWrite(23,HIGH);
    delay(500);  
    }
  else {
    Serial.println("Error sending the data");
    digitalWrite(22,LOW);
    digitalWrite(21,HIGH);
    delay(500);
  }
    digitalWrite(21,LOW);
    digitalWrite(23,LOW);
    digitalWrite(22,HIGH);  
    sinceLastTouchC5H = millis();         
    }
}
//1000Hz Loop
if(C1K){
C1K = false;
    if (touchDelayComp(sinceLastTouchC1K))
    {
     myData.a = 1000;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(21,LOW);
    digitalWrite(22,LOW);
    digitalWrite(23,HIGH);
    delay(500);    
  }
  else {
    Serial.println("Error sending the data");
    digitalWrite(22,LOW);
    digitalWrite(21,HIGH);
    delay(500);    
  }
    sinceLastTouchC1K = millis(); 
    digitalWrite(21,LOW);
    digitalWrite(23,LOW);
    digitalWrite(22,HIGH);          
    }
}
//2000Hz Loop
if (C2K){
C2K = false;
    if (touchDelayComp(sinceLastTouchC2K))
    {
     myData.a = 2000;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
    digitalWrite(22,LOW);
    digitalWrite(23,HIGH);
    delay(500);
  }
  else {
    Serial.println("Error sending the data");
    digitalWrite(21,LOW);
    digitalWrite(22,LOW);
    digitalWrite(21,HIGH);
    delay(500);
  } 
    digitalWrite(21,LOW);
    digitalWrite(23,LOW);
    digitalWrite(22,HIGH);
    sinceLastTouchC2K = millis();        
    }
}
}
//Delay Comparison for debouncing
bool touchDelayComp(unsigned long lastTouch)
{
  if (millis() - lastTouch < 2000) return false;
  else
  {
  return true;
  }
}
