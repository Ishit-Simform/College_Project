#include <SoftwareSerial.h>
#include <SPI.h>
#include <millisDelay.h>
#include <stdlib.h>
SoftwareSerial mySerial(8, 9);
millisDelay sirenDelay, sirenDelay2, batteryDelay;
int i, b = 0, c = 0, val, d = 0, j, z;
String ch;
const int siren = 7;
const int sensor = 10;
int s = 0;
void shopopen();
void shopclose();
void ring();
void setup()
{
  pinMode(sensor, INPUT);//Initializing Pin input//
  pinMode(siren, OUTPUT);//Initializing Pin output//
  Serial.begin(57600);
  mySerial.begin(57600);
  delay(1000);
  val = digitalRead(sensor);//Shop Status//

  Serial.println("Initializing...");  //Activating GSM.//
  delay(20000);                       //Activating GSM.//
  Serial.println("Initialized...");   //Activating GSM.//
  while (mySerial.available())        //Activating GSM.//
  { //Activating GSM.//
    ch = mySerial.readString();     //Activating GSM.//
  }                                   //Activating GSM.//
  ch.remove('\0');                    //Activating GSM.//
  delay(1000);                        //Activating GSM.//
  mySerial.println("AT");             //Activating GSM.//

  digitalWrite(siren, HIGH);   //GSM Activated//
  delay(2000);                 //GSM Activated//
  digitalWrite(siren, LOW);    //GSM Activated//
  delay(1000);                 //GSM Activated//

  mySerial.println("AT+CLIP=1;");
  /*while (mySerial.available())        //Activating GSM.//
  { //Activating GSM.//
    ch = mySerial.readString();     //Activating GSM.//
  }                                   //Activating GSM.//
  ch.remove('\0');                    //Activating GSM.//*/
  delay(1000);

  if (val == LOW)//CALL if SHOP OPEN//
  { //CALL if SHOP OPEN//
    shopopen();  //CALL if SHOP OPEN//
  }              //CALL if SHOP OPEN//
}
void loop()
{

  val = digitalRead(sensor);
  if (val == LOW && c == 0)
  {
    shopopen();
  }

  if (sirenDelay.justFinished()) {////////////////////////////////////////DELAY1/////////////////////////////////////////
    digitalWrite(siren, LOW); // turn led off
    Serial.println("Turned Siren Off");
  }

  if (val == HIGH && c == 1)
  {
    c = 0;
    delay(1500);
  }

  while (mySerial.available())
  {
    ring();
  }

  if (sirenDelay2.justFinished()) {////////////////////////////////////////DELAY3/////////////////////////////////////////
    digitalWrite(siren, LOW); // turn led off
    Serial.println("Turned Siren Off");
  }

}

void shopopen()
{
  d = 0;
  for (j = 0; d != 1, c == 0; j++)
  {
    b = 0;
    mySerial.println("ATD7575897733;");
    for (i = 0; b != 1, c == 0; i++)
    {


      while (mySerial.available())
      {
        ch = mySerial.readString();
        Serial.print(ch);
      }

      char res[ch.length()];
      ch.toCharArray(res, ch.length());

      if (strstr(res, "ERROR"))
      {
        delay(3000);
        while (mySerial.available())
        {
          ch = mySerial.readString();
          Serial.print(ch);
          char res[ch.length()];
          ch.toCharArray(res, ch.length());
        }
        b = 1;
        d = 1;
        c = 1;
        Serial.print(res);
        Serial.println("CALL BUSY");
        ch.remove('\0');
        memset(res, 0, sizeof(res));
        break;
      }

      if (strstr(res, "NO ANSWER"))
      {
        b = 1;
        Serial.print(res);
        Serial.println("NOT ANSWERING");
        ch.remove('\0');
        memset(res, 0, sizeof(res));
        break;
      }
    }
  }


  i = 0;
  Serial.print("i=");
  Serial.print(i);
  j = 0;
  Serial.println("j=");
  Serial.print(j);
  /*i=0;
    j=0;*/
}





void ring()
{
  ch = mySerial.readString();
  char res[ch.length()];
  ch.toCharArray(res, ch.length());

  if (strstr(res, "RING"))
  {
    while (mySerial.available())
    {
      ch = mySerial.readString();
    }

    char res[ch.length()];
    ch.toCharArray(res, ch.length());

    if (strstr(res, "917575897733"))//"+CLIP: \"919409655489\",145,,,,1"//
    {
      mySerial.println("ATH");
      Serial.print(res);
      Serial.println("SHOP OWNER");
      digitalWrite(siren, HIGH);
      sirenDelay2.start(20000);
      ch.remove('\0');
      memset(res, 0, sizeof(res));
    } else /*if(strstr!=(res, "919409655489"))*/
    {
      mySerial.println("ATH");
      Serial.print(res);
      Serial.print("SOMEONE ELSE");
      ch.remove('\0');
      memset(res, 0, sizeof(res));
    }
  }
}
