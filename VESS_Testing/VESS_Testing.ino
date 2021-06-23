
// -------------------------------------------------------------
//
//

#include <FlexCAN_T4.h>
FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> Can0;
CAN_message_t msg;

byte speedmsb;
byte speedlsb;
int speedmph;
int constspeed;


// -------------------------------------------------------------
void setup(void)
{
  Can0.begin();
  Can0.setBaudRate(500000);


  delay(1000);
  Serial.println(F("Hello Teensy 3.2 CAN VESS Test."));
  speedmph = 1;
  Serial.println (speedmph);
}

// -------------------------------------------------------------
void loop(void)
{
/////// Send speed increasing by 1 every loop
constspeed = speedmph * 256;
speedlsb = lowByte (constspeed);
speedmsb = highByte (constspeed);
//byte msg2[8] = {0x60, 0x01, 0x12, 0xA0, 0x5A, 0x01, 0xC0, 0x02};
CAN_message_t txmsg;
txmsg.id = 0x524;
//memcpy (txmsg.buf, msg2, 8);
txmsg.len = 8;
txmsg.buf[0] = 0x60;
txmsg.buf[1] = 0x01; 
txmsg.buf[2] = speedmsb; 
txmsg.buf[3] = speedlsb;
txmsg.buf[4] = 0x5A;
txmsg.buf[5] = 0x01;
txmsg.buf[6] = 0xC0;
txmsg.buf[7] = 0x02;
Can0.write (txmsg);

Serial.print(txmsg.buf[0], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[1], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[2], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[3], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[4], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[5], HEX);
Serial.print(" , ");
Serial.print(txmsg.buf[6], HEX);
Serial.print(" , ");
Serial.println(txmsg.buf[7], HEX);
delay(200);

/////////////-----------Send Forward diretion message
unsigned char msg3[8] = {0x00, 0x28, 0x00, 0x10, 0x00, 0x3B, 0xD0, 0x00};
CAN_message_t txmsg2;
txmsg2.id = 0x200;
memcpy (txmsg2.buf, msg3, 8);
Can0.write (txmsg2);
///////////-------- increase speed

if ( speedmph < 31 ) {
speedmph = speedmph + 1;
/////// print data to check its working
Serial.println (speedmph);
Serial.println (constspeed);
Serial.println (speedmsb);
Serial.println (speedlsb);
}
else {
  speedmph = 1;
}



delay(500);


////////----------- Read canbus from VESS Module
 if ( Can0.read(msg) ) {
    Serial.print("CAN1 "); 
    Serial.print("MB: "); Serial.print(msg.mb);
    Serial.print("  ID: 0x"); Serial.print(msg.id, HEX );
    Serial.print("  EXT: "); Serial.print(msg.flags.extended );
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
} 
}
