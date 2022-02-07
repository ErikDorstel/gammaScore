unsigned long rayTimer; unsigned long deltaTimer; unsigned long sec6Timer; unsigned long min1Timer;
volatile int rayCount; int rayCountArray1[10]; int rayCountArray10[10]; volatile bool alarmEnable; hw_timer_t * timer0=NULL;

void IRAM_ATTR rayISR() { rayCount++; if (alarmEnable) { ledcWrite(0,128); } timerRestart(timer0); }
void IRAM_ATTR timer0ISR() { ledcWrite(0,0); }

struct rayStruct {
  int duration1; int duration10; bool alarmEnable;
  int lastEventClicks; int min1Clicks; int min10Clicks;
  float lastEventSv; float min1Sv; float min10Sv; }; struct rayStruct ray;

void initRay() {
  ray.alarmEnable=false; alarmEnable=ray.alarmEnable; ray.duration1=1; ray.duration10=1; rayCount=0;
  for (int x=0;x<=9;x++) { rayCountArray1[x]=0; rayCountArray10[x]=0; }
  pinMode(18,INPUT); attachInterrupt(18,rayISR,RISING);
  analogSetPinAttenuation(32,ADC_0db); //int a=analogRead(32); if (a>0) { Serial.println(map(a,0,4095,100,950)); }
  ledcSetup(0,100,8); ledcAttachPin(19,0);
  timer0=timerBegin(0,80,true); timerAttachInterrupt(timer0,&timer0ISR,true);
  timerAlarmWrite(timer0,10000,true); timerAlarmEnable(timer0);
  deltaTimer=millis();
  sec6Timer=millis()+6000;
  min1Timer=millis()+60000;
  rayTimer=millis()+1000; }

void rayWorker() {
  if (millis()>=sec6Timer) { sec6Timer=millis()+6000;
    for (int x=8;x>=0;x--) { rayCountArray1[x+1]=rayCountArray1[x]; }
    rayCountArray1[0]=0; if (ray.duration1<10) { ray.duration1++; } }
  if (millis()>=min1Timer) { min1Timer=millis()+60000;
    for (int x=8;x>=0;x--) { rayCountArray10[x+1]=rayCountArray10[x]; }
    rayCountArray10[0]=0; if (ray.duration10<10) { ray.duration10++; } }
  if (millis()>=rayTimer) { rayTimer=millis()+1000; alarmEnable=ray.alarmEnable;
    if (rayCount>0) { int y=rayCount; rayCount=0; rayCountArray1[0]+=y; rayCountArray10[0]+=y;
      int delta=millis()-deltaTimer; deltaTimer=millis(); ray.lastEventClicks=y; ray.lastEventSv=y*5000.0/delta; }
    int y=0; for (int x=0;x<=9;x++) { y+=rayCountArray1[x]; }
    ray.min1Clicks=y; ray.min1Sv=y/1.2/ray.duration1;
    y=0; for (int x=0;x<=9;x++) { y+=rayCountArray10[x]; }
    ray.min10Clicks=y; ray.min10Sv=y/12.0/ray.duration10;
    if (debug) {
      Serial.print("last Event: " + String(ray.lastEventSv) + " µSv/h");
      Serial.print(" - 1 Minute average: " + String(ray.min1Sv) + " µSv/h");
      Serial.println(" - " + String(ray.duration10) + " Minutes average: " + String(ray.min10Sv) + " µSv/h"); } } }
