# RF-Arduino-car-with-nRF24L01 

This is a work in progress of a nRF24L01 RF robot car with Arduino UNO. Refer the transmitter and receiver code in the main project. Any issues you can comment in the issues section.

Receiver RF Car connections are as below

   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
   
   [![IMAGE ALT TEXT](http://img.youtube.com/vi/9q4_YfoUSUU/0.jpg)](http://www.youtube.com/watch?v=v=9q4_YfoUSUU "RF-Arduino-car-with-NRFL01")
   
   Update on 22th Aug 2020:
   a) Do not use the RX and TX in arduino to use for L298 pins
   b) You would need to callibrate your transmitter for the rest position, I had x as 347 and y as 334
   
   Code walkthrough and testing videos uploaded below
   
   
   [![IMAGE ALT TEXT](http://img.youtube.com/vi/XI8eSj_gIkw/0.jpg)](http://www.youtube.com/watch?v=v=XI8eSj_gIkw "PS2 Vs nRF24L01 which robot is better?")
   
