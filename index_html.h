char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>gammaScore - Gamma Ray Detector</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/gammaScore">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#888888; color:#ffffff; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#888888; color:#ffffff; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#C0A0A0; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#C0A0A0; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#C0A0A0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1    { background-color:#A0B0C0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#888888; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#888888; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#888888; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function gammaScoreinit() {
  ajaxObj=[]; lastEvent=0; current1Min=0; last10Min=0; getRayID=window.setInterval("getRay();",1000);
  rayAlarm=0; id("alarmBtn").style.color="#404040";
  doDisplay(); }
  
function doDisplay() {
  id("lastEvent").innerHTML=lastEvent+" µSv/h";
  id("current1Min").innerHTML=current1Min+" µSv/h";
  id("last10Min").innerHTML=last10Min+" µSv/h"; }

function doRange(doSet) { }

function getRay() { requestAJAX('getRay'); }
function setAlarm() { if (rayAlarm==1) { rayAlarm=0; id("alarmBtn").style.color="#404040"; } else { rayAlarm=1; id("alarmBtn").style.color="#ffffff"; } requestAJAX('setAlarm,'+rayAlarm); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getRay") { lastEvent=event.target.responseText.split(",")[0]*1; current1Min=event.target.responseText.split(",")[1]*1; last10Min=event.target.responseText.split(",")[2]*1; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="gammaScoreinit();">

<div><div class="x0a">gammaScore</div></div>
<div><div class="x0b">Gamma Ray Detector</div></div>

<div class="x1" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x3">last Event</div>
     <div class="x3">1 min average</div>
     <div class="x3">10 min average</div>
<div><div class="x3" id="lastEvent"></div>
     <div class="x3" id="current1Min"></div>
     <div class="x3" id="last10Min"></div></div>
<div><div class="x2" id="alarmBtn" onclick="setAlarm();">Acoustic Alarm</div></div>
</div>

</body></html>

)";
