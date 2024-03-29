const char *index_html=R"(

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
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1    { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function gammaScoreinit() {
  ajaxObj=[]; appName="&nbsp;"; appDesc="&nbsp;"; requestAJAX('appName');
  lastEvent=0; min1Avg=0; min10Avg=0; avgArray=[]; histArray={lastEvent:[],count:[]}; histTime=0; lastHistTime=0; rayAlarm=0; getAlarm(); id("clearBtn").style.color="#000000";
  doDisplay(); doDisplayRay(); doDisplayHist(); getRayID=window.setInterval("getRay();",1000); }
  
function doDisplay() {
  id("lastEvent").innerHTML=lastEvent+" µSv/h";
  id("min1Avg").innerHTML=min1Avg+" µSv/h";
  id("min10Avg").innerHTML=min10Avg+" µSv/h";
  if (rayAlarm==1) { id("alarmBtn").style.color="#000000"; } else { id("alarmBtn").style.color="#f0f0f0"; } }

function doRange(doSet) { }

function getRay() { requestAJAX('getRay'); }
function clearRay() {
  id("clearBtn").style.color="#f0f0f0"; avgArray=[]; lastEvent=0; min1Avg=0; min10Avg=0;
  histArray={lastEvent:[],count:[]}; histTime=0; lastHistTime=0;
  requestAJAX('clearRay'); doDisplay(); doDisplayRay(); doDisplayHist(); }
function getAlarm() { requestAJAX('getAlarm'); }
function setAlarm() { if (rayAlarm==1) { rayAlarm=0; } else { rayAlarm=1; } requestAJAX('setAlarm,'+rayAlarm); doDisplay(); }

function doDisplayRay() {
  avgArray.unshift(min1Avg); while (avgArray.length>600) { avgArray.pop(); }
  maxAvg=Math.max(...avgArray,0.1,min1Avg,min10Avg);
  xx=id('rayFrame').width; yy=id('rayFrame').height;
  rayFrame=id('rayFrame').getContext('2d'); rayFrame.clearRect(0,0,xx,yy);
  rayFrame.strokeStyle='rgb(0,0,0)'; rayFrame.lineWidth=3; rayFrame.font="16px Arial";
  rayFrame.fillStyle='rgb(160,160,160)'; rayFrame.fillRect(100,10,600,200); rayFrame.fillStyle='rgb(0,0,0)';
  rayFrame.fillText("µSv/h",0,10+6);
  rayFrame.fillText(scaleRay(maxAvg*1),50,10+6); rayFrame.fillRect(94,10-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.75),50,60+6); rayFrame.fillRect(94,60-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.5),50,110+6); rayFrame.fillRect(94,110-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0.25),50,160+6); rayFrame.fillRect(94,160-1,6,3);
  rayFrame.fillText(scaleRay(maxAvg*0),50,210+6); rayFrame.fillRect(94,210-1,6,3);
  rayFrame.fillText("sec",60,240);
  rayFrame.fillText("0",100-3,240); rayFrame.fillRect(100,210,3,8);
  rayFrame.fillText("120",220-12,240); rayFrame.fillRect(220-1,210,3,8);
  rayFrame.fillText("240",340-12,240); rayFrame.fillRect(340-1,210,3,8);
  rayFrame.fillText("360",460-12,240); rayFrame.fillRect(460-1,210,3,8);
  rayFrame.fillText("480",580-12,240); rayFrame.fillRect(580-1,210,3,8);
  rayFrame.fillText("600",700-14,240); rayFrame.fillRect(700-3,210,3,8);
  rayFrame.fillStyle='rgb(255,255,255)';
  y=mapValue(min10Avg,0,maxAvg,0,199); rayFrame.fillRect(100,208-y,600,3);
  rayFrame.fillStyle='rgb(0,0,0)';
  rayFrame.beginPath(); y=mapValue(avgArray[0],0,maxAvg,0,199); rayFrame.moveTo(100,209-y);
  for (x=0;x<avgArray.length;x++) { y=mapValue(avgArray[x],0,maxAvg,0,199); rayFrame.lineTo(x+100,209-y); }
  rayFrame.stroke(); }

function doDisplayHist() {
  if (histTime>lastHistTime) { lastHistTime=histTime; i=histArray.lastEvent.lastIndexOf(lastEvent);
    if (i==-1) { histArray.lastEvent.push(lastEvent); histArray.count.push(1); }
    else { y=histArray.count[i]; histArray.count[i]=0; histArray.lastEvent.push(lastEvent); histArray.count.push(y+1); } }
  else { histArray.lastEvent.push(-1); histArray.count.push(0); }
  while (histArray.lastEvent.length>600) { if (histArray.count[0]==0) {
      histArray.count[histArray.lastEvent.lastIndexOf(histArray.lastEvent[0])]--; }
    histArray.lastEvent.shift(); histArray.count.shift(); }
  maxLastEvent=Math.max(...histArray.lastEvent,1);
  maxCount=Math.max(...histArray.count,1);
  xx=id('histFrame').width; yy=id('histFrame').height;
  histFrame=id('histFrame').getContext('2d'); histFrame.clearRect(0,0,xx,yy);
  histFrame.strokeStyle='rgb(0,0,0)'; histFrame.lineWidth=3; histFrame.font="16px Arial";
  histFrame.fillStyle='rgb(160,160,160)'; histFrame.fillRect(100,10,600,200); histFrame.fillStyle='rgb(0,0,0)';
  histFrame.fillText("Count",0,10+6);
  histFrame.fillText(scaleRay(maxCount*1),50,10+6); histFrame.fillRect(94,10-1,6,3);
  if (maxCount>2) { histFrame.fillText(scaleRay(maxCount*0.75),50,60+6); histFrame.fillRect(94,60-1,6,3); }
  if (maxCount>1) { histFrame.fillText(scaleRay(maxCount*0.5),50,110+6); histFrame.fillRect(94,110-1,6,3); }
  if (maxCount>2) { histFrame.fillText(scaleRay(maxCount*0.25),50,160+6); histFrame.fillRect(94,160-1,6,3); }
  histFrame.fillText(scaleRay(maxCount*0),50,210+6); histFrame.fillRect(94,210-1,6,3);
  histFrame.fillText("µSv/h",40,240);
  histFrame.fillText(scaleRay(maxLastEvent*1),100-3,240); histFrame.fillRect(100,210,3,8);
  x=mapValue(scaleRoot(maxLastEvent*0.5),0,scaleRoot(maxLastEvent),599,0);
    histFrame.fillText(scaleRay(maxLastEvent*0.5),100+x-3,240); histFrame.fillRect(100+x,210,3,8);
  x=mapValue(scaleRoot(maxLastEvent*0.1),0,scaleRoot(maxLastEvent),599,0);
    histFrame.fillText(scaleRay(maxLastEvent*0.1),100+x-3,240); histFrame.fillRect(100+x,210,3,8);
  x=mapValue(scaleRoot(maxLastEvent*0.05),0,scaleRoot(maxLastEvent),599,0);
    histFrame.fillText(scaleRay(maxLastEvent*0.05),100+x-3,240); histFrame.fillRect(100+x,210,3,8);
  x=mapValue(scaleRoot(maxLastEvent*0.01),0,scaleRoot(maxLastEvent),599,0);
    histFrame.fillText(scaleRay(maxLastEvent*0.01),100+x-3,240); histFrame.fillRect(100+x,210,3,8);
  histFrame.fillText(scaleRay(maxLastEvent*0),700-6,240); histFrame.fillRect(700-3,210,3,8);
  last5Array=[]; for (a=0;a<histArray.lastEvent.length;a++) { if (histArray.count[a]>0) {
    c=mapValue(a,0,histArray.lastEvent.length-1,128,0); histFrame.fillStyle='rgb('+c+','+c+','+c+')';
    y=mapValue(histArray.count[a],0,maxCount,0,200);
    x=mapValue(scaleRoot(histArray.lastEvent[a]),0,scaleRoot(maxLastEvent),599,0);
    histFrame.fillRect(100+x,210-y,3,y); last5Array.push({"x":100+x,"y":210-y}); } }
  if (last5Array.length>5) { last5Array.splice(0,last5Array.length-5); }
  last5Array.sort(function(m,n) { return ( (m.x<n.x) ? -1 : ((m.x==n.x) ? 0 : 1) ); });
  histFrame.fillStyle='rgb(255,255,255)'; histFrame.lineWidth=3; histFrame.strokeStyle='rgb(220,220,220)';
  for (a=0;a<last5Array.length;a++) { if (a<last5Array.length-1) {
      histFrame.beginPath(); histFrame.moveTo(last5Array[a].x+2,last5Array[a].y+3);
      histFrame.lineTo(last5Array[a+1].x+1,last5Array[a+1].y+3); histFrame.stroke(); }
    histFrame.fillRect(last5Array[a].x-1,last5Array[a].y,5,5); } }

function scaleRay(value) {
  if (value<10) { return Math.round(value*100)/100; }
  else if (value<100) { return Math.round(value*10)/10; }
  else { return Math.round(value); } }

function scaleRoot(value) { return Math.pow(value,1/4); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getRay") { lastEvent=event.target.responseText.split(",")[0]*1; min1Avg=event.target.responseText.split(",")[1]*1;
                                      min10Avg=event.target.responseText.split(",")[2]*1; histTime=event.target.responseText.split(",")[3]*1;
                                      doDisplay(); doDisplayRay(); doDisplayHist(); }
    else if (event.target.url=="getAlarm") { rayAlarm=event.target.responseText.split(",")[0]*1; doDisplay(); }
    else if (event.target.url=="clearRay") { id("clearBtn").style.color="#000000"; } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="gammaScoreinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x3">last Event</div>
     <div class="x3">1 min average</div>
     <div class="x3">10 min average</div>
<div><div class="x3" id="lastEvent"></div>
     <div class="x3" id="min1Avg"></div>
     <div class="x3" id="min10Avg"></div></div>
<div><div class="x1"><canvas id="rayFrame" width="720px" height="245px"></canvas></div></div>
<div><div class="x1"><canvas id="histFrame" width="720px" height="245px"></canvas></div></div>
<div><div class="x2" id="alarmBtn" onclick="setAlarm();">Acoustic Alarm</div>
     <div class="x2" id="clearBtn" onclick="clearRay();">Clear Measurement</div></div>
</div>

</body></html>

)";
