#include "UbidotsESPMQTT.h"
#include<ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define TOKEN "BBFF-YIZBlh8tYkhhIue43uUFaJvCyUXplm" // Put here your Ubidots TOKEN
#define WIFISSID "****"       
#define PASSWORD "*********"
Ubidots client(TOKEN);
#define AnalogPin A0
#define buzzPin 3
#define True_pass_indicator_led_pin 1
#define False_pass_indicator_led_pin 4
#define servo_pin 2
#define flame_pin D10
#define temp_sensor_pin A0
#define SS_PIN D8
#define RST_PIN D9
MFRC522 mfrc522(SS_PIN, RST_PIN);
const int dataPin = D0; //Outputs the byte to transfer
const int loadPin = D3; //Controls the internal transference of data in SN74HC595 internal registers
const int clockPin = D4;
int flame;
String recived;
Servo myservo;
//*********************************************************************Choose what will
use i2c module or without********************
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //to use the lcd without i2c
LiquidCrystal_I2C lcd(0x27,16,2); // to use i2c module of the lcd
//***********************************************************************************
************************************************
const int tol=15;//Tolerance for the analog read
int counter=0;//
int state=0;
int keyVals[16] = {665, 768, 877, 1024, 414, 454, 487, 534, 304, 322, 336, 356, 243, 254, 262, 274};
//Array to store keypad numerical values
char keys [16] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'}; //Key characters corressponding to
each numerical value
void shift_reg(int x,boolean y);
bool return_val(){int x=analogRead(AnalogPin); if(x>100){ return true;}else{return false;}}//Function
which return state of keypad if button is pressed will return True else return False
int val(){int x=analogRead(AnalogPin);for(int i=0;i<16;i++){if(x<=keyVals[i]+tol&&x>=keyVals[i]-tol){
return i; delay(100);}}}//Function returns which key is pressed
void buzz(){shift_reg(buzzPin,HIGH); delay(100); shift_reg(buzzPin,LOW);}//Function to operate the
buzzer for 100milisec and turn it off
void astric(){lcd.print("*");}//Function to print an * every press
void True_pass_indicator_led(){shift_reg(True_pass_indicator_led_pin,HIGH);
delay(1000);shift_reg(True_pass_indicator_led_pin,LOW);}
void False_pass_indicator_led(){shift_reg(False_pass_indicator_led_pin,HIGH);
delay(1000);shift_reg(False_pass_indicator_led_pin,LOW);}
void servo_move(){int pos; for (pos = 0; pos <= 180; pos += 1) { myservo.write(pos);delay(15);} for (pos =180; pos >= 0; pos -= 1) { myservo.write(pos);delay(15);}}
void send_alert(){client.add("alert",100);client.ubidotsPublish("device3");
delay(1000);client.add("alert",0);client.ubidotsPublish("device3");}
void send_data(){
float temp = analogRead(temp_sensor_pin);
float mv = ( temp/1024.0)*5000;
float cel = mv/10;
flame=digitalRead(flame_pin);
//Serial.println(cel);
Serial.println(flame);
client.add("temp", cel);
client.add("flame", flame);
client.ubidotsPublish("device3");
}
void callback(char* topic, byte* payload, unsigned int length) {
recived="";
recived=topic;
if(recived.indexOf("nodemcu-2/relay")>-1){
if((char)payload[0]=='1'){shift_reg(5,LOW);}
else{shift_reg(5,HIGH);}
}
}
String pass=""; //variable for saved the pass
const String saved="4444";//Password of the door
void setup() {
SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init(); // Initiate MFRC522
//*********************************************************************Choose what will
use i2c module or without********************************
// *******************lcd_intialitazion for I2C module of lcd************
lcd.init();
lcd.init();
lcd.backlight();
// **********************************************************************
// *******************lcd_intialitazion without i2c module************
lcd.begin(16, 2);
//**********************************************************************
//***********************************************************************************
*************************************************************
Serial.begin(115200);
//pinMode(False_pass_indicator_led_pin,OUTPUT);
//pinMode(True_pass_indicator_led_pin,OUTPUT);
//pinMode(buzzPin,OUTPUT);
myservo.attach(servo_pin);
client.wifiConnection(WIFISSID, PASSWORD);
//client.setDataSourceName("NodeMCU-1");
//client.setDataSourceLabel("NodeMCU-1");
client.setDebug(true);
client.begin(callback);
client.ubidotsSubscribe("nodemcu-2","relay");
pinMode(flame_pin,INPUT);

pinMode(dataPin, OUTPUT);
pinMode(loadPin, OUTPUT);
pinMode(clockPin, OUTPUT);

}
void loop() {
if(!client.connected()){

client.reconnect();
client.ubidotsSubscribe("nodemcu-2","relay");
}
state_rf();

if(state==1){

lcd.setCursor(0,0);
lcd.print("Enter pass: ");
int j=val();
if(return_val()==1){
lcd.setCursor(counter,1);
pass=pass+keys[j];
astric();
counter++;
Serial.println(pass);
buzz();
if(pass.length()==saved.length()) //check if the two password is equal in length
{
counter=0;
if (pass==saved) { //check if input password equal to the saved pass
lcd.clear();
lcd.print("Hello to home");
pass="";
True_pass_indicator_led();
servo_move();
state=0;
}
else{

lcd.clear();
lcd.print("Wrong pass");
pass="";
False_pass_indicator_led();
send_alert();
state=0;
}}

}
}
else{lcd.setCursor(0,0); ;lcd.print("please put id");}
delay(100);
send_data();
client.loop();
}

void shift_reg(int x,boolean y){
byte data;
if(x==1&&y==1){ data = B00000001;}
if(x==2&&y==1){ data = B00000010;}
if(x==3&&y==1){ data = B00000100;}
if(x==4&&y==1){ data = B00001000;}
if(x==5&&y==1){ data = B00010000;}
if(x==6&&y==1){ data = B00100000;}
if(x==7&&y==1){ data = B01000000;}
if(x==8&&y==1){ data = B10000000;}
//////////////////////////////////
if(x==1&&y==0){ data = B00000000;}
if(x==2&&y==0){ data = B00000000;}

if(x==3&&y==0){ data = B00000000;}
if(x==4&&y==0){ data = B00000000;}
if(x==5&&y==0){ data = B00000000;}
if(x==6&&y==0){ data = B00000000;}
if(x==7&&y==0){ data = B00000000;}
if(x==8&&y==0){ data = B00000000;}
///////////////////////////////////

digitalWrite(loadPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, data);
digitalWrite(loadPin, HIGH);

}
void state_rf(){

// Look for new cards
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return ;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return ;
}
//Show UID on serial monitor
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)

{
//Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
// Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
// Serial.println();
// Serial.print("Message : ");
content.toUpperCase();
if (content.substring(1) == "57 FF 21 12" ||content.substring(1) == "15 97 4E D3") //change here the
UID of the card/cards that you want to give access
{
state=1;
}

else{ state=0;}

}
