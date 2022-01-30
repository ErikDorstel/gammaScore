unsigned long rayTimer; unsigned long deltaTimer; unsigned long minuteTimer;
volatile int rayCount; int rayCountArray[10]; volatile bool alarmEnable; hw_timer_t * timer0=NULL;

void IRAM_ATTR rayISR() { rayCount++; if (alarmEnable) { ledcWrite(0,128); } timerRestart(timer0); }
void IRAM_ATTR timer0ISR() { ledcWrite(0,0); }

struct rayStruct {
  int duration; bool alarmEnable;
  int lastEventCpm; int min1Cpm; int min10Cpm;
  float lastEventSv; float min1Sv; float min10Sv; }; struct rayStruct ray;

void initRay() {
  ray.alarmEnable=false; alarmEnable=ray.alarmEnable;
  rayCount=0; for (int x=0;x<=9;x++) { rayCountArray[x]=0; } ray.duration=1;
  pinMode(18,INPUT); attachInterrupt(18,rayISR,RISING);
  analogSetPinAttenuation(32,ADC_0db); //int a=analogRead(32); if (a>0) { Serial.println(map(a,0,4095,100,950)); }
  ledcSetup(0,100,8); ledcAttachPin(19,0);
  timer0=timerBegin(0,80,true); timerAttachInterrupt(timer0,&timer0ISR,true);
  timerAlarmWrite(timer0,10000,true); timerAlarmEnable(timer0);
  deltaTimer=millis();
  minuteTimer=millis()+60000;
  rayTimer=millis()+1000; }

void rayWorker() {
  if (millis()>=minuteTimer) { minuteTimer=millis()+60000;
    for (int x=8;x>=0;x--) { rayCountArray[x+1]=rayCountArray[x]; }
    rayCountArray[0]=0; if (ray.duration<10) { ray.duration++; } }
  if (millis()>=rayTimer) { rayTimer=millis()+1000; alarmEnable=ray.alarmEnable;
    if (rayCount>0) { int y=rayCount; rayCount=0; rayCountArray[0]+=y; int delta=millis()-deltaTimer; deltaTimer=millis(); ray.lastEventCpm=y; ray.lastEventSv=y*5000.0/delta; }
    ray.min1Cpm=rayCountArray[0]; ray.min1Sv=rayCountArray[0]/12.0;
    int y=0; for (int x=0;x<=9;x++) { y+=rayCountArray[x]; }
    ray.min10Cpm=y; ray.min10Sv=y/12.0/ray.duration;
    if (debug) {
      Serial.print("last Event: " + String(ray.lastEventSv) + " µSv/h");
      Serial.print(" - current Minute: " + String(ray.min1Sv) + " µSv/h");
      Serial.println(" - last " + String(ray.duration) + " Minutes: " + String(ray.min10Sv) + " µSv/h"); } } }
