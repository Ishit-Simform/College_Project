char phone_no[]="7575897733";

void setup() {
Serial.begin(9600);
delay(200);

Serial.println("AT");
delay(1000);
Serial.print("ATD");
Serial.print(phone_no);
delay(8000);
Serial.print("ATH");


}

void loop() {
  // put your main code here, to run repeatedly:

}
