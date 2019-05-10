#include <Time.h>
#include <TimeLib.h>
#include <XBee.h>
#include <SoftwareSerial.h>
XBee xbee = XBee();
//////////////////////////

byte ledPin =  5; // Pino do LED
boolean ledState = false; // Estado do LED: False = desligado ou true = ligado
long prevMillis = 0; // Última mudança de estado
long interval = 2000; // intervalo desejado para o blink

//////////////////////////////////////////////////////

//SoftwareSerial XBee(3,2);
ZBRxResponse zbRx = ZBRxResponse();

union u_tag {
    uint8_t b[4];
    float fval;
} u;

void setup () {
  
  Serial.begin(9600);
  xbee.begin(Serial);
  pinMode(ledPin, OUTPUT);
  setTime(4,1,00,12,9,2018);

  }

void loop () {
///////////////////////////////////////////
  unsigned long curMillis = millis(); //millis atual
  if(curMillis - prevMillis < interval) {
    prevMillis = curMillis;  
    ledState = !ledState;
    digitalWrite(ledPin, ledState);}

/////////////////////////////////

time_t t = now();//Declaramos la variable time_t t
String sample;
xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    //Serial.println("Packet available"); 
    } 
if (xbee.getResponse().isAvailable()) {
      //Serial.println(xbee.getResponse().getApiId());
      //Serial.println();
      //Serial.print("Frame Type is ");
      //Serial.println(xbee.getResponse().getApiId(), HEX);
      }

      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(zbRx);
        /////////////////////////////////////////////////
         // now that you know it's a receive packet
        // fill in the values
     
      
        // this is how you get the 64 bit address out of
        // the incoming packet so you know which device
        // it came from
        //Serial.print("Got an rx packet from: ");
        XBeeAddress64 senderLongAddress = zbRx.getRemoteAddress64();
        //Serial.print(senderLongAddress.getMsb());
        //Serial.print(" ");
        //Serial.print(senderLongAddress.getLsb());
      
        // this is how to get the sender's
        // 16 bit address and show it
        uint16_t senderShortAddress = zbRx.getRemoteAddress16();
        //Serial.print(" (");
        //Serial.print(senderShortAddress);
        //Serial.print(")");
        //Serial.print(" ");
      
        // The option byte is a bit field
        if (zbRx.getOption() & ZB_PACKET_ACKNOWLEDGED)
            // the sender got an ACK
          //Serial.println("packet acknowledged");
        if (zbRx.getOption() & ZB_BROADCAST_PACKET)
          // This was a broadcast packet
          //Serial.println("broadcast Packet");
        
        //Serial.print("checksum is ");
        //Serial.println(zbRx.getChecksum(), HEX);
      
        // this is the packet length
        //Serial.print("packet length is ");
        //Serial.print(zbRx.getPacketLength(), DEC);
      
        // this is the payload length, probably
        // what you actually want to use
        //Serial.print(", data payload length is ");
        //Serial.println(zbRx.getDataLength(),DEC);
      
        // this is the actual data you sent
        //Serial.println("Received Data: ");
        //for (int i = 0; i < zbRx.getDataLength(); i++) {
          //Serial.print(zbRx.getData()[i]);
          //Serial.print(' ');

       
        ///////////////////////////////////////////////
       // for (int i = 0; i < zbRx.getDataLength(); i++) {
        //sample += (char)zbRx.getData(i);
       
          u.b[0]= zbRx.getData(0);
          u.b[1]= zbRx.getData(1);
          u.b[2]= zbRx.getData(2);
          u.b[3]= zbRx.getData(3);
       //}


        
//////////////////////////////////////////////////////////////////
        //Serial.println(sample);

        //Serial.print("Temperatura: ");
        //Serial.print("Temperatura: ");
        Serial.print(senderLongAddress.getLsb());
        Serial.print(",");
        Serial.print(u.fval);
        Serial.print(",");
        Serial.print(day(t));
    Serial.print(+ "/") ;
    Serial.print(month(t));
    Serial.print(+ "/") ;
    Serial.print(year(t)); 
    Serial.print( " ") ;
    Serial.print(hour(t));  
    Serial.print(+ ":") ;
    Serial.print(minute(t));
    Serial.print(":") ;
    Serial.println(second(t));
        
        //Serial.println(xbee.getResponse().getApiId());
         /////////////////////////
      

         ////////////////////////
      }

      delay(10000);
}

