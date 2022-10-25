
#include "ESP8266WiFi.h"

const int RSSI_MAX =-50;      // menentukan kekuatan sinyal maksimum dalam dBm
const int RSSI_MIN =-100;     // menentukan kekuatan sinyal minimum dalam dBm

//const int displayEnc=1;       // 1 untuk menampilkan Enkripsi atau 0 untuk tidak ditampilkan

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);        // Set WiFi ke mode stasiun
  WiFi.disconnect();
  delay(2000);
}

void loop() {
  Serial.println("  Mencari Sinyal WiFi...");
  Serial.println("");

  int n = WiFi.scanNetworks();
  //Serial.println("  Pencarian Sinyal WiFi Selesai");
  if (n == 0) {
    Serial.println("  Jaringan tidak ditemukan.");
  } else {
    Serial.print("  ");
    Serial.print(n);
    Serial.println(" jaringan yang ditemukan.");
    for (int i = 0; i < n; ++i) {
      Serial.print("     ");
      Serial.print(i + 1);
      Serial.print(") ");
      Serial.print(WiFi.SSID(i));
      Serial.print("  ");
 
      Serial.print(WiFi.RSSI(i));   //Kekuatan sinyal dalam dBm
      Serial.print("dBm.");

      delay(10);
    }
  }
  Serial.println("");

  delay(5000);
  WiFi.scanDelete();  
}
