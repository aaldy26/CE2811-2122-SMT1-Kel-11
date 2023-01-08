#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include "CTBot.h"

// Deklarasi Variable dan Konstanta
String wifiSSID = "ALIRNOFBERKAH";
String wifiPassword = "aldyft260200";

String r = "Mencari Jaringan Wifi";
String s = "Jaringan tidak ditemukan.";
String t = "  Jaringan ditemukan.";
String u = "";
String za = "\n";

TBMessage tMessage;
String token = "5450499188:AAHN6oasj0OhT-Fmg5WMZgY3jozDNScOl9k";
CTBot myBot;

const int RSSI_MAX =-50;      // menentukan kekuatan sinyal maksimum dalam dBm
const int RSSI_MIN =-100;     // menentukan kekuatan sinyal minimum dalam dBm

// Deklarasi Fungsi
void connectWifi();
void loginTelegram();

void setup()
{
    Serial.begin(9600);
    connectWifi();
    loginTelegram();

}

void loop()
{
  

    if (myBot.getNewMessage(tMessage))
    {
        Serial.println(tMessage.text);
        if (tMessage.messageType == CTBotMessageText)
        {
            if (tMessage.text.equalsIgnoreCase("/start"))
            {
                String reply = "";
                reply += "Hi, Selamat Datang "+ tMessage.sender.firstName + " dibot Kelompok 11\n";
                reply += "Berikut List Commandnya : \n";
                reply += "Memulai Mencari WIFI : /scan \n";

                myBot.sendMessage(tMessage.sender.id, reply);
            }
            else if (tMessage.text.equalsIgnoreCase("/scan"))
            {
              int n = WiFi.scanNetworks();
            String sn = String(n);
              Serial.println("scan done");
              if (n == 0) {
                  Serial.println("no networks found");
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
                  String reply = "";
                  String zu = a + u;
                  reply += "Scanning :  \n";
                  reply += zu;
                  u = "";
                  zu = "";
                  
                  

                  myBot.sendMessage(tMessage.sender.id, reply);
              }
              Serial.println("");
              delay(2000);
              WiFi.scanDelete();       
            }
            else
            {
                String reply = "";
                reply += "Hi, Selamat Datang "+ tMessage.sender.firstName + " dibot Kelompok 11\n";
                reply += "Command tidak terdefinisi, ketik /start untuk melihat List Command! \n";

                myBot.sendMessage(tMessage.sender.id, reply);
            }
        }
    }
}

void connectWifi()
{
    Serial.println("Connecting To Wifi");
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("Wifi Connected");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.dnsIP());
}

void loginTelegram()
{
    Serial.println("logging in...");
    while (!myBot.testConnection())
    {
        myBot.setTelegramToken(token);
        delay(1000);
    }
    Serial.println("Telegram connection OK!");
}

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
