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
  ajaxObj=[]; lastEvent=0; min1Avg=0; min10Avg=0; avgArray=[]; rayAlarm=0; getAlarm();
  doDisplay(); doDisplayRay(); getRayID=window.setInterval("getRay();",1000); }
  
function doDisplay() {
  id("lastEvent").innerHTML=lastEvent+" µSv/h";
  id("min1Avg").innerHTML=min1Avg+" µSv/h";
  id("min10Avg").innerHTML=min10Avg+" µSv/h";
  if (rayAlarm==1) { id("alarmBtn").style.color="#ffffff"; } else { id("alarmBtn").style.color="#404040"; } }

function doRange(doSet) { }

function getRay() { requestAJAX('getRay'); }
function clearRay() { id("clearBtn").style.color="#404040"; avgArray=[]; lastEvent=0; min1Avg=0; min10Avg=0; requestAJAX('clearRay'); doDisplay(); doDisplayRay(); }
function getAlarm() { requestAJAX('getAlarm'); }
function setAlarm() { if (rayAlarm==1) { rayAlarm=0; } else { rayAlarm=1; } requestAJAX('setAlarm,'+rayAlarm); doDisplay(); }

function doDisplayRay() {
  avgArray.unshift(min1Avg); while (avgArray.length>480) { avgArray.pop(); }
  maxAvg=Math.max(...avgArray,0.1,min1Avg,min10Avg);
  xx=id('rayFrame').width; yy=id('rayFrame').height;
  rayFrame=id('rayFrame').getContext('2d');
  rayFrame.clearRect(0,0,xx,yy);
  rayFrame.strokeStyle='rgb(0,0,0)'; rayFrame.lineWidth=3; rayFrame.font="16px Arial";
  rayFrame.fillStyle='rgb(160,160,160)'; rayFrame.fillRect(100,10,480,200); rayFrame.fillStyle='rgb(0,0,0)';
  rayFrame.fillText("µSv/h",0,10+6);
  rayFrame.fillText(scaleRay(maxAvg*1),50,10+6); rayFrame.fillRect(94,10-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.75),50,60+6); rayFrame.fillRect(94,60-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.5),50,110+6); rayFrame.fillRect(94,110-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.25),50,160+6); rayFrame.fillRect(94,160-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0),50,210+6); rayFrame.fillRect(94,210-1,6,3);
  rayFrame.fillText("sec",60,240);
  rayFrame.fillText("0",100-3,240); rayFrame.fillRect(100,210,3,8);
  rayFrame.fillText("120",209,240); rayFrame.fillRect(220,210,3,8);
  rayFrame.fillText("240",328,240); rayFrame.fillRect(339,210,3,8);
  rayFrame.fillText("360",447,240); rayFrame.fillRect(458,210,3,8);
  rayFrame.fillText("480",566,240); rayFrame.fillRect(577,210,3,8);
  rayFrame.fillStyle='rgb(255,255,255)';
  y=mapValue(min10Avg,0,maxAvg,0,199); rayFrame.fillRect(100,208-y,480,3);
  rayFrame.fillStyle='rgb(0,0,0)';
  rayFrame.beginPath(); y=mapValue(avgArray[0],0,maxAvg,0,199); rayFrame.moveTo(100,209-y);
  for (x=0;x<avgArray.length;x++) { y=mapValue(avgArray[x],0,maxAvg,0,199); rayFrame.lineTo(x+100,209-y); }
  rayFrame.stroke(); }

function scaleRay(value) {
  if (value<10) { return Math.round(value*100)/100; }
  else if (value<100) { return Math.round(value*10)/10; }
  else { return Math.round(value); } }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getRay") { lastEvent=event.target.responseText.split(",")[0]*1; min1Avg=event.target.responseText.split(",")[1]*1;
                                      min10Avg=event.target.responseText.split(",")[2]*1; doDisplay(); doDisplayRay(); }
    if (event.target.url=="getAlarm") { rayAlarm=event.target.responseText.split(",")[0]*1; doDisplay(); }
    if (event.target.url=="clearRay") { id("clearBtn").style.color="#ffffff"; } } }

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
     <div class="x3" id="min1Avg"></div>
     <div class="x3" id="min10Avg"></div></div>
<div><div class="x1"><canvas id="rayFrame" width="600px" height="240px"></canvas></div></div>
<div><div class="x2" id="alarmBtn" onclick="setAlarm();">Acoustic Alarm</div>
     <div class="x2" id="clearBtn" onclick="clearRay();">Clear Measurement</div></div>
</div>

</body></html>

)";
