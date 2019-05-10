#include <OneWire.h>
#include <DallasTemperature.h>
#include <TMP36.h>
#include <XBee.h>
//TMP36 tmp36(A0,5);
XBee xbee = XBee();

//////////////////////////

byte ledPin =  5; // Pino do LED
boolean ledState = false; // Estado do LED: False = desligado ou true = ligado
long prevMillis = 0; // Última mudança de estado
long interval = 2000; // intervalo desejado para o blink

//////////////////////////////////////////////////////
const int pinDatosDQ = 2;

// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
uint8_t payload[4] ={0,0,0,0};

union u_tag {
    uint8_t b[4];
    float fval;
} u;
 
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x041085ad3);
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x041085f96);
ZBTxRequest tx = ZBTxRequest(addr64, payload, sizeof(payload));

int statusLed = 13;
int errorLed = 13;
 
void flashLed(int pin, int times, int wait) {
 
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);
 
    if (i + 1 < times) {
      delay(wait);
    }
  }
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial.begin(9600);
  xbee.setSerial(Serial);
// Iniciamos el bus 1-Wire
    sensorDS18B20.begin(); 
    pinMode(ledPin, OUTPUT);

  
}

void loop() {



  ///////////////////////////////////////////
  unsigned long curMillis = millis(); //millis atual
  if(curMillis - prevMillis < interval) {
    prevMillis = curMillis;  
    ledState = !ledState;
    digitalWrite(ledPin, ledState);}

/////////////////////////////////
  //float tmp = tmp36.getTempC();
sensorDS18B20.requestTemperatures();

float tmp = sensorDS18B20.getTempCByIndex(0);
    
  if (!isnan(tmp)) {
    // same for the temperature
    u.fval = tmp;
    for (int i=0;i<4;i++){
      payload[i]=u.b[i];
    }
  
  }
  //payload[0]='T';
  //payload[1]='e';
  //payload[2]='m';
  //payload[3]='p';
    
  xbee.send(tx);
  flashLed(statusLed, 1, 100);
  //Serial.println(tmp);
  delay (60000);

}



