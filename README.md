# gammaScore
ESP32 and GDK101 based Gamma Ray Detector
#### Features
* uses GDK101 as PIN diode gamma ray detector
* works as WLAN client and AP (AP chooser included)
* WebUI with IP address 192.168.4.1
* mDNS hostname gammaScore.local
* DNS hostname gammaScore.local (WLAN AP mode only)
* acoustic alarm (click sounds)
* measurement of last event gamma ray in µSv/h
* measurement of 1 minute average gamma ray in µSv/h
* measurement of 10 minute average ray in µSv/h
* WebUI gamma average graph with autoscale
* WebUI gamma event histogram with autoscale
#### digital in (digital ray event from gdk101)
* GPIO 18
#### digital out (acoustic alarm)
* GPIO 19
#### analog in (analog ray event from gdk101)
* GPIO 32
#### Development Hardware
![IMAGE ALT TEXT HERE](https://www.dorstel.de/github/gammaScore_b_v1.0.png)
#### Web UI Screenshot
![IMAGE ALT TEXT HERE](https://www.dorstel.de/github/gammaScore_a_v1.8.png)
