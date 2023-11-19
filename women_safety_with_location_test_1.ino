
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "SPI.h"
TinyGPSPlus gps;

SoftwareSerial ss (3, 4);

SoftwareSerial mySerial (5, 6);

int push = 2;

int led = 7;

long int number=0;

int i = 0;

long writingTimer = 120;

long startTime = 0;

long waitTime = 0;

int s=0;

void
setup () 
{
  
 
Serial.begin (9600);
  
mySerial.begin (9600);
  
 
ss.begin (9600);    // Setting the baud rate of GSM Module  
  Serial.println ("AT+CNMI=2,2,0,0,0");
  
Serial.begin (9600);
  
pinMode (push, INPUT);
  
pinMode (led, OUTPUT);
  

 
} 
void

loop () 
{
  
 
if (ss.available () > 0)
    
    {
      
gps.encode (ss.read ());
    
}
  
int val = digitalRead (push);
  
if (mySerial.available () > 0)
    
    {
      
Serial.write (mySerial.read ());
    
 
 
}
  
Serial.println (push);
  
if (digitalRead (push) == 0)
    
    {
      
i = i + 1;
    
 
}
  
if (digitalRead (push) == 0 && i == 1)
    
    {
      
 
double_blink ();
      
 
SendMessage ();
    
 
}
  
 
if (i == 3)
    
    {
      
callLed ();
      
MakeCall ();
    
 
}
  
if (digitalRead (push) == 0 && i == 3)
    
    {
      
digitalWrite (led, LOW);
      
i = 0;
    
 
}
  
waitTime = millis () - startTime;
  
if (waitTime > (writingTimer * 500) && i == 0)
    
    {
      
gprs ();
      
startTime = millis ();
    
}

}


 
bool SendMessage () 
{
  
 
 
String msg =
    "I'm in Danger at \nlatitude:" + String (gps.location.lat (),
               6) + "\nlongitude:" +
    String (gps.location.lng (), 6) + "\n   " + String (gps.location.lat (),
              6) + "," +
    String (gps.location.lng (),
      6) + "\ncopy this and put in maps to get location";
  
mySerial.println ("AT+CMGF=1"); //Sets the GSM Module in Text Mode
  delay (1000);     // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CSMP=17,167,0,0\r");
  delay(1000);
  mySerial.println ("AT+CMGS=\"+916374808089\"\r"); // Replace x with mobile number
  delay (1000);
  
mySerial.println (msg); // The SMS text you want to send
  delay (100);
  
mySerial.println ((char) 26); // ASCII code of CTRL+Z
  delay (100);
  
Serial.println (msg);

 
} 
bool MakeCall () 
{
  
mySerial.println ("ATD+916374808089;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println ("Calling  "); // print response over serial port
  delay (1000);

} 
bool double_blink () 
{
  
digitalWrite (led, HIGH);
  
delay (250);
  
digitalWrite (led, LOW);
  
delay (400);
  
digitalWrite (led, HIGH);
  
delay (250);
  
digitalWrite (led, LOW);

 
} 
bool triple_blink () 
{
  
digitalWrite (led, HIGH);
  
delay (250);
  
digitalWrite (led, LOW);
  
delay (400);
  
digitalWrite (led, HIGH);
  
delay (250);
  
digitalWrite (led, LOW);
  
delay (400);
  
digitalWrite (led, HIGH);
  
delay (250);
  
digitalWrite (led, LOW);

 
} 
boolean callLed () 
{
  
for (int s = 0; s < 41; s++)
    
    {
      
digitalWrite (led, HIGH);
      
delay (50);
      
digitalWrite (led, LOW);
      
delay (50);

}} 
void

gprs () 
{
  
if (mySerial.available ())
    
Serial.write (mySerial.read ());
  
digitalWrite (led, HIGH);
  
 
mySerial.println ("AT");
  
delay (1000);
  
 
mySerial.println ("AT+CPIN?");
  
delay (1000);
  
 
mySerial.println ("AT+CREG?");
  
delay (1000);
  
 
mySerial.println ("AT+CGATT?");
  
delay (1000);
  
 
mySerial.println ("AT+CIPSHUT");
  
delay (1000);
  
 
mySerial.println ("AT+CIPSTATUS");
  
delay (2000);
  
 
mySerial.println ("AT+CIPMUX=0");
  
delay (2000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CSTT=\"airtelgprs.com\"");  //start task and setting the APN,
  delay (1000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIICR");  //bring up wireless connection
  delay (3000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIFSR");  //get local IP adress
  delay (2000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIPSPRT=0");
  
delay (3000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\""); //start up the connection
  delay (6000);
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIPSEND");  //begin send data to remote server
  delay (4000);
  
ShowSerialData ();
 if(i!=0)
{
  int s=1;
}
else
{
   int s=0;
} 
 
String str =
    "GET https://api.thingspeak.com/update?api_key=6JASOBJ9S95JBL17&field1=" +
    String (gps.location.lat (),
      6) + "&field2=" + String (gps.location.lng (), 6)+"&field3="+String (s);
  
Serial.println (str);
  
mySerial.println (str); //begin send data to remote server
  
delay (4000);
  
ShowSerialData ();
  
 
mySerial.println ((char) 26); //sending
  delay (5000);     //waitting for reply, important! the time is base on the condition of internet 
  mySerial.println ();
  
 
ShowSerialData ();
  
 
mySerial.println ("AT+CIPSHUT");  //close the connection
  delay (100);
  
ShowSerialData ();
  
 
digitalWrite (led, LOW);

 
} 
void

ShowSerialData () 
{
  
  {
    
while (mySerial.available () != 0)
      
Serial.write (mySerial.read ());
    
delay (500);
  
 
 
}

}
