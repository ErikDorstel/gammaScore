#include <WiFi.h>
WiFiServer tcpServer(80);
WiFiUDP dnsServer;
#include <Preferences.h>
Preferences preferences;

const char* ssidAP="gammaScore"; const char* passwordAP="";
String ssidStation=""; String passwordStation=""; boolean statusStation=false;

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  preferences.begin("wlanAuth",false); preferences.putString("ssidStation",ssidStation); preferences.putString("passwordStation",passwordStation); preferences.end();
  statusStation=true; if (debug) { Serial.println("WLAN Station " + ssidStation + " connected."); } }

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  statusStation=false; WiFi.disconnect(); if (debug) { Serial.println("WLAN Station disconnected."); }
  preferences.begin("wlanAuth",false); String ssidStationOld=preferences.getString("ssidStation",""); String passwordStationOld=preferences.getString("passwordStation",""); preferences.end();
  if (ssidStationOld==ssidStation & passwordStationOld==passwordStation & WiFi.softAPgetStationNum()==0) { WiFi.reconnect(); } }

void initWLAN() {
  preferences.begin("wlanAuth",false); ssidStation=preferences.getString("ssidStation",""); passwordStation=preferences.getString("passwordStation",""); preferences.end();
  WiFi.mode(WIFI_AP_STA);
  WiFi.onEvent(WiFiStationConnected,SYSTEM_EVENT_STA_CONNECTED);
  WiFi.onEvent(WiFiStationDisconnected,SYSTEM_EVENT_STA_DISCONNECTED);
  WiFi.softAPConfig(IPAddress(192,168,4,1),IPAddress(192,168,4,1),IPAddress(255,255,255,0)); WiFi.softAP(ssidAP,passwordAP);
  WiFi.setHostname("gammaScore"); WiFi.begin(ssidStation.c_str(),passwordStation.c_str());
  if (debug) { Serial.println("WLAN AP with IP address " + WiFi.softAPIP().toString() + " enabled."); }
  tcpServer.begin(); dnsServer.begin(53); }

void reconnectWLAN() {
  if (statusStation==true) { WiFi.disconnect(); delay(250); }
  WiFi.begin(ssidStation.c_str(),passwordStation.c_str()); }
