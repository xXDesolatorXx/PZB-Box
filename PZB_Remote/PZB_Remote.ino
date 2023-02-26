
/*  
PZB Remote V0.1

Made by Fabian Witzel
*/

#include <esp_now.h>
#include "WiFi.h"

typedef struct struct_message {
  int a;

} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

bool C500 = false;
bool C1000 = false;
bool C2000 = false;

volatile unsigned long sinceLastTouchC5 = 0;
volatile unsigned long sinceLastTouchC1 = 0;
volatile unsigned long sinceLastTouchC2 = 0;

bool touchDelayComp(unsigned long);

uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x34, 0xA4, 0xD8};
//AC:67:B2:34:A4:D8

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//500Hz Button Interrupt
void IRAM_ATTR H500()
{
    C500 = true;
}
//1000Hz Button Interrupt
void IRAM_ATTR H1000()
{
    C1000 = true;
}
//2000Hz Button Interrupt
void IRAM_ATTR H2000()
{  
    C2000 = true;
}

void setup(){
pinMode(17,INPUT_PULLDOWN);
pinMode(18,INPUT_PULLDOWN);
pinMode(19,INPUT_PULLDOWN);
attachInterrupt(17,H500,RISING);
attachInterrupt(18,H1000,RISING);
attachInterrupt(19,H2000,RISING);
Serial.begin(115200);
WiFi.mode(WIFI_STA);

if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
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

if (C500)
{
C500 = false;
    if (touchDelayComp(sinceLastTouchC5))
    {
     myData.a = 500;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
    sinceLastTouchC5 = millis();         
    }
}
if(C1000){
C1000 = false;
    if (touchDelayComp(sinceLastTouchC1))
    {
     myData.a = 1000;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
    sinceLastTouchC1 = millis();       
    }
}
if (C2000){
C2000 = false;
    if (touchDelayComp(sinceLastTouchC2))
    {
     myData.a = 2000;
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  } 
    sinceLastTouchC2 = millis();        
    }
}
}

bool touchDelayComp(unsigned long lastTouch)
{
  if (millis() - lastTouch < 5000) return false;
  else
  {
  return true;
  }
}