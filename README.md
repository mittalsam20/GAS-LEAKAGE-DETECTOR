# GAS-LEAKAGE-DETECTOR
A LPG gas leakage detector which sends message to the user phone if there is a gas leakage

##HARDWARE REQUIRED
ARDUINO UNO
ESP8266 WIFI MODULE
MQ2/3/5/6/132 GAS SENSOR
BUZZER
LED
JUMPER WIRES

##PLATFORM USED
THINGSPEAK (AN IOT PLATFORM)
PUSHBULLET (NOTIFICATION APP FOR PC/PHONE)
ARDUINO IDE

The project is coded in arduino IDE,first the mq2 sensor senses the gas and starts a local alert by switching on led and buzzer and then it sends the value of gas (pe ppm)
sensed by the mq2 sensor to Thingspeak.com (an IOT platform) from there it sends a message to PUSHBULLET (an notification and messaging) which alerts the user about
gas leak.

P.S:- You need to configure thingspeak first then use your api key in the code for sending the message from esp8266 to thingspeak.com
      for pushbullet u need to link both of them via api of pushbullet.

