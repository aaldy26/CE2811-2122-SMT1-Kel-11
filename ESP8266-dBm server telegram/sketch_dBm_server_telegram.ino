
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// konfigurasi jaringan wifi
const char* ssid = "ALIRNOFBERKAH"; // SSID dari wifi anda
const char* password = "aldyft260200"; // Pass dari wfi anda

#define PIN_LED 2             // inisialisasi LED di pin 2

const int RSSI_MAX =-50;      // menentukan kekuatan sinyal maksimum dalam dBm
const int RSSI_MIN =-100;     // menentukan kekuatan sinyal minimum dalam dBm

String r = "Mencari Sinyal WiFi...";
String s = "Jaringan tidak ditemukan.";
String t = "  jaringan ditemukan.";
String u = "";
String za = "\n";

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);        // Set WiFi ke mode stasiun
  //WiFi.disconnect();
  delay(2000);
  pinMode(PIN_LED, OUTPUT);

  // setting koneksi
  Serial.println();
  Serial.println();
  Serial.print("Koneksi ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // cek koneksi
  while(WiFi.status() != WL_CONNECTED){
      
      digitalWrite(PIN_LED, HIGH);     // LED mati

      // NodeMCU akan terus mencoba koneksi
      Serial.print(".");
      delay(500);
  }

  // bila terkoneksi
  digitalWrite(PIN_LED, LOW);          // LED menyala
  // tampilkan di serial monitor
  Serial.println("");
  Serial.println("WiFi Terkoneksi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

void loop() {
  Serial.println(r);
  Serial.println("");
  kirimData(r);

  int n = WiFi.scanNetworks();
  String sn = String(n);
  
  if (n == 0) {
    Serial.println("Jaringan tidak ditemukan.");
    kirimData(s);
  } else {
    String a = sn + t + za + za;
    Serial.print(n);
    Serial.println(t);
    
    u = "";
    for (int i = 0; i < n; ++i) {
      int v = i + 1;
      String nv = String(v) + ") ";
      String w = String(WiFi.SSID(i)) + "  ";
      String x = String(WiFi.RSSI(i)) + "dBm (";
      String xv = String(dBmtoPercentage(WiFi.RSSI(i)));
      String xw = String("%)");
      String y = nv + w + x + xv + xw + za;
      u = u + y;

      Serial.print("  ");
      Serial.print(nv);
      Serial.print(w);
      Serial.print(x);
      Serial.print(dBmtoPercentage(WiFi.RSSI(i)));
      Serial.println("%)");

      delay(10);
    }
    String zu = a + u;
    kirimData(zu);
    u = "";
    zu = "";
  }
  Serial.println("");

  delay(2000);
  WiFi.scanDelete();  
}

void kirimData(String isi) {
    String postData = (String)"data=" + isi;
    
    // cek koneksi ke server
    HTTPClient http;
    http.begin("http://chat.aldikadek.my.id/datadBm.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    auto httpCode = http.POST(postData);
    String isiData = http.getString();     // Mengambil data post yang dikirim
  
    http.end();
    delay(700);
}

// Kekuatan sinyal dalam %
int dBmtoPercentage(int dBm) {
  int quality;
    if(dBm <= RSSI_MIN) {
        quality = 0;
    } else if(dBm >= RSSI_MAX) {  
        quality = 100;
    } else {
        quality = 2 * (dBm + 100);
    }
    return quality;
}




//
