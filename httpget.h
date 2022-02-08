String httpget(String request) {
  String response="";

  // gammaScore specific pages

  if (request.indexOf("/getRay")>=0) { response+=String(ray.lastEventSv) + "," + String(ray.min1Sv) + "," + String(ray.min10Sv) + ","; }

  else if (request.indexOf("/getAlarm")>=0) { response+=String(ray.alarmEnable) + ","; }

  else if (request.indexOf("/setAlarm")>=0) { int a=request.indexOf(",")+1; ray.alarmEnable=request.substring(a).toInt(); }

  else if (request.indexOf("/clearRay")>=0) { clearRay(); }

  // WLAN Choose specific pages

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (statusStation==true) { response="<div class=\"x1\">WLAN AP " + ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) { response=a2h(ssidStation) + "," + a2h(passwordStation) + ","; }

  else if (request.indexOf("/scanAP")>=0) {
    int indexes=WiFi.scanNetworks(); for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<div class=\"x1\" onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</div>"; } } }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    ssidStation=h2a(request.substring(a,b-1)); passwordStation=h2a(request.substring(b));
    reconnectWLAN(); }

  // Default page

  else { response=index_html; }

  return response; }
