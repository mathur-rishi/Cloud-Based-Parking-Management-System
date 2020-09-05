// Coded for NodeMCU ESP8266 v0.9, MFRC522 RFID reader, and Google Firebase

// NodeMCU library
#include <ESP8266WiFi.h>

// MFRC522 libraries
#include <SPI.h>
#include <MFRC522.h>

// Firebase libraries
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <FirebaseError.h>

// My credentials library
#include "Credentials.h"

#define SS_PIN 16 // D0 pin of NodeMCU
#define RST_PIN 5 // D1 pin of NodeMCU

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN,RST_PIN);

void setup(){
  
  // Initiate
  Serial.begin(9600); // Serial communication
  SPI.begin();        // SPI bus
  mfrc522.PCD_Init(); // MFRC522

  // Connect to WiFi
  WiFi.begin(WIFI_SSID,WIFI_PASS);
  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  // Initiate Firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void loop(){

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  // Show UID on serial monitor
  Serial.println();
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

  // Upload UID to Firebase
  String UID = Firebase.pushString("logs", content.substring(1));
  if (Firebase.failed()){ // Handle error
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("pushed: /logs/");
  Serial.print(UID);
  delay(1000);
}
