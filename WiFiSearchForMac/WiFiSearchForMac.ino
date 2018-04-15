#include "ESP8266WiFi.h"

bool wifiFound = false;
bool wifiLastFound = true;
String macAddressToFind = "00:00:00:00:00:00";
int relayPin = D1;      // D1
int statusLedPin = LED_BUILTIN; //4;  // D2
int nChecks = 2;
int iChecks = 0;

void setup() {
  pinMode(relayPin, OUTPUT); // Initialize the relay pin as an output
  pinMode(statusLedPin, OUTPUT); // Initialize the statusLedPin pin as an output
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
}

void loop() {
  wifiFound = findNetwork(macAddressToFind);
  if (wifiFound) {
    digitalWrite(relayPin, LOW); // since connected to NC, switch to LOW to switch switch on power
    Serial.println("Waiting for 1 minute before scanning again...");
    delay(60000);     // Wait a minute before scanning again if network is found
  } else {
      // if not found and last time not found and checked for nChecks times; switch off
      if ( (wifiFound == wifiLastFound) && (iChecks == nChecks)) {  
        blinkTimes(1);
        Serial.println("Switching or remaining off. Waiting for 60 seconds before scanning again...");
        digitalWrite(relayPin, HIGH); // since connected to NC, switch to HIGH to switch off power
        iChecks = 0;
        delay(60000);      // Wait 60 seconds before scanning again if network is not found
      } 
      // if not found for the first time, wait for 30 seconds to check again
      else {  
        blinkTimes(iChecks+1);
        Serial.print("Check for ");
        Serial.print(nChecks-iChecks);
        Serial.print(" more times. ");
        Serial.println("Waiting for the result of following scan(s) in 30 seconds before switching off...");
        iChecks++;
        delay(30000);      // Wait 30 seconds before scanning again if network is not found
      }
      
    }
  wifiLastFound = wifiFound;
}

void blinkTimes(int n) {
  delay(200); // to allow the led to be off for a wee bit after previous action
  for (int i = 0; i < n; i++) {
    digitalWrite(statusLedPin, LOW);   // Turn the LED on (for ESP)
    delay(100);
    digitalWrite(statusLedPin, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(100);
  }
}

bool findNetwork(String mac) {

  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  digitalWrite(statusLedPin, LOW);
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);
  digitalWrite(statusLedPin, HIGH);

  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    if (WiFi.BSSIDstr(thisNet) == mac) {
      Serial.println("The wifi with MAC " + mac + " is found");
      return true;
    }
  }
  Serial.println("The wifi with MAC " + mac + " is not found");
  return false;
}


