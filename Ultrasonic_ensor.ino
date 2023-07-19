/*************************************************************

  You’ll need:
   - Blynk IoT app (download from App Store or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Fill-in information from Blynk Device Info here */

int trig=4;
int echo = 5;
int buzzer = 0;

#define BLYNK_TEMPLATE_ID "TMPL621s1mpIo"
#define BLYNK_TEMPLATE_NAME "Ultrasonic"
#define BLYNK_AUTH_TOKEN "7b1HMdmAUASLd-TIIpA_6wUfRMJdhRv7"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Shaz_Sohail";
char pass[] = "Keshwani321";

BlynkTimer timer;


void setup()
{
  // Debug console
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(115200);
  delay(100);
  timer.setInterval(2500L, sendSensor);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
  
 
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

void sendSensor(){
  digitalWrite(trig,LOW);

  delayMicroseconds(5);


  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  long duration = pulseIn(echo,HIGH);
  long distance = ((duration*0.034)/2);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Blynk.virtualWrite(V0,distance);
  if (distance<10){
    digitalWrite(buzzer,HIGH);
    Blynk.logEvent("anonmous_person_detection", "Alert! Someone is in the room");
    }
   else{
    digitalWrite(buzzer,LOW);
   }
}
