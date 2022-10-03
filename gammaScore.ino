boolean debug=true;

const char* appName="gammaScore";
const char* appDesc="Gamma Ray Detector";

#include "ray.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initDNS();
  initHTTP();
  initRay(); }

void loop() { wlanWorker(); httpWorker(); dnsWorker(); rayWorker(); }
