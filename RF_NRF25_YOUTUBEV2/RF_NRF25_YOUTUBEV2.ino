/* JoyStick module receiver code with Arduino Uno
 - CONNECTIONS: nRF24L01 Modules See:
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
 */
//-----( Import needed libraries )-----
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants for the NRF )-----*/
#define CE_PIN 6
#define CSN_PIN 8


const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


#define horn_Buzz    7     
/* Make sure this is PWM Pins */
#define ENA 3          // Enable/speed motor Front Right 
#define ENB 9          // Enable/speed motor Front Left

/* Do not use PIN 0,1 as they are for RX,TX  */
#define IN_1  5          // L298N #1 in 1 motor Front Right
#define IN_2  10          // L298N #1 in 2 motor Back Right
#define IN_3  2          // L298N #1 in 3 motor Front Left
#define IN_4  4          // L298N #1 in 4 motor Back Left

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[6];  // 6 element array holding Joystick readings
int speedRight = 0;
int speedLeft = 0;
int  xAxis, yAxis;
// the four button variables from joystick
int buttonUp;
int buttonRight;
int buttonDown;
int buttonLeft;

void setup()
{

  pinMode(horn_Buzz, OUTPUT);
    
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
    
  Serial.begin(9600);
  //Serial.println("Nrf24L01 Receiver Starting"); 
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

}

void loop()
{
  if ( radio.available() )
  {
      radio.read( joystick, sizeof(joystick) );
      xAxis = joystick[0];
      yAxis = joystick[1];
      
      // the four button variables from joystick array
      int buttonUp    = joystick[2];
      int buttonRight = joystick[3];
      int buttonDown  = joystick[4];
      int buttonLeft  = joystick[5];
      
      Serial.println(); // for debugging
      // Fetch the data payload - Debugging code below
  
      if (buttonUp == HIGH){digitalWrite(horn_Buzz, LOW);}
        else {digitalWrite(horn_Buzz, HIGH);}
/* Please callibrate the X and Y axis, Your values maynot match with mine. My Joystick pot at rest had values 347,334 */
// Y-axis used for forward and backward control
    if (yAxis < 470) {
    // Set Right Motors backward
    digitalWrite(IN_1, LOW);
    digitalWrite(IN_2, HIGH);
    digitalWrite(IN_3, LOW);
    digitalWrite(IN_4, HIGH);
    
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    speedRight  = map(yAxis,470,0, 0, 255);
    speedLeft   = map(yAxis,470,0, 0, 255);
     Serial.print("Inside code for backwards");
     Serial.print(speedRight);
  }

else if (yAxis > 550) {
    // Set Right Motors forward
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
    digitalWrite(IN_3, HIGH);
    digitalWrite(IN_4, LOW);

     // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    speedRight  = map(yAxis, 550, 700, 0, 255);
    speedLeft   = map(yAxis, 550, 700, 0, 255);
    Serial.print("Inside code for forward drive");
    Serial.print(speedRight);
  }
  // If joystick stays in middle the motors are not moving
  else {
    speedRight  = 0;
    speedLeft   = 0;

  } 

// X-axis used for left and right control
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    speedLeft = speedLeft - xMapped;
    speedRight = speedRight + xMapped;
    // Confine the range from 0 to 255
    if (speedLeft < 0) {
      speedLeft = 0;
    }
    if (speedRight > 255) {
      speedRight = 255;
    }
  }
  if (xAxis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 700, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    speedLeft = speedLeft + xMapped;
    speedRight = speedRight - xMapped;
    // Confine the range from 0 to 255
    if (speedLeft > 255) {
      speedLeft = 255;
    }
    if (speedRight < 0) {
      speedRight = 0;
    }
  }


  // Prevent buzzing at low speeds
  if (speedLeft < 50) {
    speedLeft = 0;
  }
  if (speedRight < 50) {
    speedRight = 0;
  }

  analogWrite(ENA, speedRight); // Send PWM signal to motor A
  analogWrite(ENB, speedLeft); // Send PWM signal to motor B

     
      Serial.print("X = ");
      Serial.print(xAxis);
      Serial.print(" Y = ");  
      Serial.print(yAxis);
      /*Serial.print(" Up = ");
      Serial.print(joystick[2]);
      Serial.print(" Right = ");  
      Serial.print(joystick[3]);
      Serial.print(" Down = ");
      Serial.print(joystick[4]);
      Serial.print(" Left = ");  
      Serial.println(joystick[5]); */
    
       
      }

         
  }













  
