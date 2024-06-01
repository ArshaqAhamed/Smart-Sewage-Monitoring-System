#define BLYNK_TEMPLATE_ID "TMPL6AxaUl4Qg"
#define BLYNK_TEMPLATE_NAME "Sewage Monitoring"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial 
#define USE_NODE_MCU_BOARD
//#define APP_DEBUG

#include "BlynkEdgent.h"

#define echoPin D7
#define trigPin D6
#define redled D8
#define floatsensor D4

long duration;
int distance; 
int buttonState;

void ultrasonic()
{
    digitalWrite(redled, HIGH); 
    delay(1000);
    digitalWrite(redled, LOW); 
    
  // for ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    Serial.print("Distance: ");
    Serial.println(distance);
    Blynk.virtualWrite(V0, distance);

  //for float sensor
    buttonState = digitalRead(floatsensor);  // read the value of float sensor
    Blynk.virtualWrite(V1, buttonState);

  //trigger conditions
    if (buttonState == HIGH){                                       
    Serial.println( "WATER LEVEL - HIGH");
    Blynk.logEvent("overflow_alert");
    Serial.println( "Overflow Alert!" );           
    }
    else if(distance<=20){
    Blynk.logEvent("blockage_alert");
    Serial.println( "Block Detected!" );
    }
    else {
    Serial.println( "WATER LEVEL - LOW" ); 
    Serial.println( "No Block Detected" );
    }
}
void setup()
{
  Serial.begin(9600);
  Serial.println("Serial begin at 9600");

  pinMode(trigPin, OUTPUT); 
  pinMode(34, INPUT);
  pinMode(echoPin, INPUT); 
  pinMode(redled, OUTPUT);
  pinMode(floatsensor, INPUT_PULLUP); //Arduino Internal Resistor 10K
  BlynkEdgent.begin();
  delay(2000); 
}

void loop() 
{
  BlynkEdgent.run();
  ultrasonic();
}
