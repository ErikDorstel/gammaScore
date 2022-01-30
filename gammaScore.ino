boolean debug=true;

#include "ray.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initRay(); }

void loop() { httpWorker(); dnsWorker(); rayWorker(); }
