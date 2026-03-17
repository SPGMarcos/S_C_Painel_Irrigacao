#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LittleFS.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -10800, 60000);

// Variáveis
bool desligaAutomacao = false;
int irrDay = 1;
bool valvula1 = false;
bool valvula2 = false;
int sH[3] = {17,0,0}, sM[3] = {25,0,0}, eH[3] = {17,0,0}, eM[3] = {26,0,0};
bool isIrrigating = false;

void sendRelay(byte relay, bool state) {
  byte cmd[4] = {0xA0, relay, (byte)(state ? 0x01 : 0x00), (byte)(0xA0 + relay + (state ? 0x01 : 0x00))};
  Serial.write(cmd, 4);
  Serial.flush();
}

void saveSettings() {
  File f = LittleFS.open("/config.txt", "w");
  if(f){
    f.println(desligaAutomacao); f.println(irrDay);
    for(int i=0;i<3;i++){ f.println(sH[i]); f.println(sM[i]); f.println(eH[i]); f.println(eM[i]); }
    f.close();
  }
}

void loadSettings() {
  if(LittleFS.exists("/config.txt")){
    File f = LittleFS.open("/config.txt", "r");
    if(f){
      desligaAutomacao = f.readStringUntil('\n').toInt();
      irrDay = f.readStringUntil('\n').toInt();
      for(int i=0;i<3;i++){
        sH[i]=f.readStringUntil('\n').toInt(); sM[i]=f.readStringUntil('\n').toInt();
        eH[i]=f.readStringUntil('\n').toInt(); eM[i]=f.readStringUntil('\n').toInt();
      }
      f.close();
    }
  }
}

const char htmlPage[] PROGMEM = R"=====(
<!DOCTYPE html><html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<style>
  body { background:#111; color:#e1e1e1; font-family:sans-serif; padding:15px; }
  .card { background:#1c1c1e; border-radius:12px; padding:18px; margin-bottom:15px; box-shadow:0 4px 10px rgba(0,0,0,0.5); }
  h2 { font-size:16px; color:#aeaeb2; text-transform:uppercase; margin-top:0; }
  .row { display:flex; justify-content:space-between; align-items:center; margin-bottom:18px; }
  .label-group { display:flex; align-items:center; gap:12px; }
  .icon { width:22px; height:22px; fill:#44739e; }
  .hidden { display:none; }
  .segmented-control { display:flex; background:#2c2c2e; border-radius:8px; padding:2px; width:120px; }
  .seg-btn { flex:1; border:none; background:none; color:#fff; padding:8px 0; border-radius:6px; font-weight:bold; }
  .seg-btn.active { background:#44739e; }
  .switch { position:relative; width:46px; height:26px; }
  .switch input { opacity:0; width:0; height:0; }
  .slider { position:absolute; cursor:pointer; top:0; left:0; right:0; bottom:0; background:#3e3e42; transition:.4s; border-radius:26px; }
  .slider:before { position:absolute; content:""; height:20px; width:20px; left:3px; bottom:3px; background:#fff; transition:.4s; border-radius:50%; }
  input:checked + .slider { background:#007aff; }
  input:checked + .slider:before { transform:translateX(20px); }
  input[type="time"] { background:#2c2c2e; color:#fff; border:1px solid #3e3e42; padding:8px; border-radius:8px; font-size:16px; }
</style></head>
<body>
<div class="card">
  <h2>Geral</h2>
  <div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12,2A10,10 0 0,0 2,12A10,10 0 0,0 12,22A10,10 0 0,0 22,12A10,10 0 0,0 12,2M12,4A8,8 0 0,1 20,12A8,8 0 0,1 12,20A8,8 0 0,1 4,12A8,8 0 0,1 12,4M12,6A6,6 0 0,0 6,12A6,6 0 0,0 12,18A6,6 0 0,0 18,12A6,6 0 0,0 12,6Z"/></svg><span>Auto Off</span></div><label class="switch"><input type="checkbox" id="autoOff" onchange="update('autoOff', this.checked)"><span class="slider"></span></label></div>
  <div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12,2L4.5,20.29L5.21,21L12,18L18.79,21L19.5,20.29L12,2Z"/></svg><span>Ciclos</span></div><div class="segmented-control"><button class="seg-btn" id="btn1" onclick="setCycles(1)">1</button><button class="seg-btn" id="btn2" onclick="setCycles(2)">2</button><button class="seg-btn" id="btn3" onclick="setCycles(3)">3</button></div></div>
  <div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12,20A6,6 0 0,1 6,14C6,10 12,3.25 12,3.25C12,3.25 18,10 18,14A6,6 0 0,1 12,20Z"/></svg><span>Válvula 1</span></div><label class="switch"><input type="checkbox" id="v1" onchange="update('v1', this.checked)"><span class="slider"></span></label></div>
  <div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12,20A6,6 0 0,1 6,14C6,10 12,3.25 12,3.25C12,3.25 18,10 18,14A6,6 0 0,1 12,20Z"/></svg><span>Válvula 2</span></div><label class="switch"><input type="checkbox" id="v2" onchange="update('v2', this.checked)"><span class="slider"></span></label></div>
</div>
<div id="c1" class="card"><h2>Irrigação 1</h2><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Início</span></div><input type="time" id="sT0" onchange="update('sT0',this.value)"></div><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24" style="fill:#cf6679"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Fim</span></div><input type="time" id="eT0" onchange="update('eT0',this.value)"></div></div>
<div id="c2" class="card hidden"><h2>Irrigação 2</h2><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Início</span></div><input type="time" id="sT1" onchange="update('sT1',this.value)"></div><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24" style="fill:#cf6679"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Fim</span></div><input type="time" id="eT1" onchange="update('eT1',this.value)"></div></div>
<div id="c3" class="card hidden"><h2>Irrigação 3</h2><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Início</span></div><input type="time" id="sT2" onchange="update('sT2',this.value)"></div><div class="row"><div class="label-group"><svg class="icon" viewBox="0 0 24 24" style="fill:#cf6679"><path d="M12.5,7V12.25L17,14.92L16.25,16.15L11,13V7H12.5Z"/></svg><span>Fim</span></div><input type="time" id="eT2" onchange="update('eT2',this.value)"></div></div>
<script>
function setCycles(v){ document.querySelectorAll('.seg-btn').forEach(b=>b.classList.remove('active')); document.getElementById('btn'+v).classList.add('active'); document.getElementById('c2').classList.toggle('hidden',v<2); document.getElementById('c3').classList.toggle('hidden',v<3); update('irrDay',v); }
function update(k,v){ fetch(`/set?${k}=${v}`); }
function load(){ fetch('/status').then(r=>r.json()).then(d=>{ document.getElementById('autoOff').checked=d.autoOff; setCycles(d.irrDay); document.getElementById('v1').checked=d.v1; document.getElementById('v2').checked=d.v2; for(let i=0;i<3;i++){ document.getElementById('sT'+i).value=d.sT[i]; document.getElementById('eT'+i).value=d.eT[i]; } }); }
window.onload=load; setInterval(load,5000);
</script></body></html>
)=====";

void handleStatus() {
  String json = "{ \"autoOff\":" + String(desligaAutomacao?"true":"false") + ",\"irrDay\":" + String(irrDay) + ",\"v1\":" + String(valvula1?"true":"false") + ",\"v2\":" + String(valvula2?"true":"false");
  json += ",\"sT\":["; for(int i=0;i<3;i++){ char b[10]; sprintf(b,"\"%02d:%02d\"%s",sH[i],sM[i],(i<2?",":"")); json+=b; }
  json += "],\"eT\":["; for(int i=0;i<3;i++){ char b[10]; sprintf(b,"\"%02d:%02d\"%s",eH[i],eM[i],(i<2?",":"")); json+=b; }
  json += "]}"; server.send(200, "application/json", json);
}

void handleSet() {
  bool ch = false;
  if(server.hasArg("autoOff")){ desligaAutomacao=(server.arg("autoOff")=="true"); ch=true; }
  if(server.hasArg("irrDay")){ irrDay=server.arg("irrDay").toInt(); ch=true; }
  if(server.hasArg("v1")){ valvula1=(server.arg("v1")=="true"); sendRelay(0x01,valvula1); }
  if(server.hasArg("v2")){ valvula2=(server.arg("v2")=="true"); sendRelay(0x02,valvula2); }
  for(int i=0;i<3;i++){
    String s="sT"+String(i), e="eT"+String(i);
    if(server.hasArg(s)){ sH[i]=server.arg(s).substring(0,2).toInt(); sM[i]=server.arg(s).substring(3,5).toInt(); ch=true; }
    if(server.hasArg(e)){ eH[i]=server.arg(e).substring(0,2).toInt(); eM[i]=server.arg(e).substring(3,5).toInt(); ch=true; }
  }
  if(ch) saveSettings();
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP); // Botão Flash do NodeMCU
  LittleFS.begin(); loadSettings();
  WiFiManager wm;
  wm.autoConnect("ESP_Irrigacao");
  if(MDNS.begin("esp_irrigacao")) Serial.println("mDNS iniciado");
  timeClient.begin();
  server.on("/", [](){ server.send(200, "text/html", htmlPage); });
  server.on("/status", handleStatus);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
  timeClient.update();
  MDNS.update();

  // RESET TOTAL: Segurar botão FLASH por 5 segundos
  if (digitalRead(0) == LOW) {
    delay(5000);
    if (digitalRead(0) == LOW) {
      WiFiManager wm;
      wm.resetSettings();
      LittleFS.format();
      ESP.restart();
    }
  }

  if (!desligaAutomacao) {
    int cur = timeClient.getHours() * 60 + timeClient.getMinutes();
    bool should = false;
    for(int i=0; i<irrDay; i++){
      if(cur >= (sH[i]*60+sM[i]) && cur < (eH[i]*60+eM[i])) { should=true; break; }
    }
    if(should && !isIrrigating){
      isIrrigating=true; sendRelay(0x01,true); delay(1000); sendRelay(0x02,true);
    } else if(!should && isIrrigating){
      isIrrigating=false; sendRelay(0x01,false); delay(1000); sendRelay(0x02,false);
    }
  }
}