
// -------------------------------------------------------------
//
//

#include <FlexCAN_T4.h>
FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> can0;
CAN_message_t txmsg, txmsg2, rxmsg;

int speedmsb;
int speedlsb;
int speedmph;
int constspeed;


// -------------------------------------------------------------
void setup(void)
{
  can0.begin();
  can0.setBaudRate(500000);


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
speedlsb = constspeed & 0xFF;
speedmsb = constspeed >> 8;
signed char msg2[8] = {0x60, 0x01, speedmsb, speedlsb, 0x5A, 0x01, 0xC0, 0x02};
strcpy (txmsg.buf, msg2);
txmsg.id = 0x524;
Serial.print(txmsg.buf[0], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[1], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[2], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[3], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[4], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[5], HEX);
//Serial.print(" , ");
Serial.print(txmsg.buf[6], HEX);
//Serial.print(" , ");
Serial.println(txmsg.buf[7], HEX);
can0.write (txmsg);
delay(200);

/////////////-----------Send Forward diretion message
signed char msg3[8] = {0x00, 0x28, 0x00, 0x10, 0x00, 0x3B, 0xD0, 0x00};
txmsg2.id = 0x200;
strcpy (txmsg2.buf, msg3);
can0.write (txmsg2);
speedmph = speedmph + 1;
Serial.println (speedmph);
delay(500);


////////----------- Read canbus from VESS Module
can0.read(rxmsg);
//Serial.print("  ID ");
Serial.print(rxmsg.id, HEX);
Serial.print(" Data ");
Serial.print(rxmsg.buf[0]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[1]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[2]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[3]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[4]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[5]);
//Serial.print(" , ");
Serial.print(rxmsg.buf[6]);
//Serial.print(" , ");
Serial.println(rxmsg.buf[7]);

} 
