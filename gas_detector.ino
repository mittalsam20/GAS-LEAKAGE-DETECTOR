#include <SoftwareSerial.h>
SoftwareSerial esp8266 =  SoftwareSerial(2,3); 

String API  = "3GIXCPZUZCURN567";         // API KEY TO THINGSPEAK.COM
String ssid ="Samaksh phone";             // WIFI NETWORK SSID
String PASS ="sammittal";                 // WIFI NETWORK PASSWORD
String HOST = "api.thingspeak.com";
String PORT = "80";

int redLed = 5;                           //LED THAT WILL BLINK WHEN LEAKAGE IS DETECTED
int buzzer = 7;
int smokeA0 = A5;
int sensorThres = 400;                    //threshold value OF DETECTION  

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);                     //BAUD RATE FOR ARDUINO
  esp8266.begin(115200);                  //BAUD RATE FOR ESP8266 

  sendCommand("AT",5,"OK");               //AT COMMANDS CHECK WETHER THE MODULE IS CONNECTED TO WIFI
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ ssid +"\",\""+ PASS +"\"",20,"OK");

}

void loop() {
  int analogSensor = analogRead(smokeA0);

//  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    tone(buzzer, 3000, 3000);
    String getData = "GET /update?api_key="+ API +"&field1="+analogSensor;
    sendCommand("AT+CIPMUX=1",5,"OK");                                          //AT COMMANDS CHECK WETHER THE MODULE IS CONNECTED TO WIFI
    sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");         //QUERY THE IP ADDRESS AND PORNT NUMBER
    sendCommand("AT+CIPSEND=0,"+String(getData.length()+4),4,">");              //SETS DATA LENGTH WHICH WILL BE SENT
    esp8266.println(getData);
    countTrueCommand++;
    sendCommand("AT+CIPCLOSE=0",5,"OK");
    delay(150);
  }
  else
  {
    digitalWrite(redLed, LOW);
    noTone(buzzer);
  }
  delay(200);
}


void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
