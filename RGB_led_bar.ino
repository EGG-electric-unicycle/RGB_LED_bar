#include "FastLED.h"

static int speed = 0;
static int speed_temp1 = 0;
static int speed_temp2 = 0;
static int current = 0;
static int current_temp1 = 0;
static int current_temp2 = 0;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// How many leds in your strip?
#define NUM_LEDS 15

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(115200); //opens serial port, sets data rate to 115200 bps
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
//  // read data only when you receive data:
//  if (Serial.available() > 0)
//  {
//    // read the incoming byte
//    Serial.print(Serial.read());
//    Serial.print(" ");
//  }
  
  read_serial_data ();

  if (current < 1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

    leds[0] = CRGB::Green;
    leds[1] = CRGB::Green;
    leds[2] = CRGB::Green;
    leds[3] = CRGB::Green;
    leds[4] = CRGB::Green;
    leds[5] = CRGB::Green;
    leds[6] = CRGB::Green;
    leds[7] = CRGB::Green;
    leds[8] = CRGB::Green;
    leds[8] = CRGB::Green;
    leds[9] = CRGB::Green;
    leds[10] = CRGB::Green;
    leds[11] = CRGB::Green;
    leds[12] = CRGB::Green;
    leds[13] = CRGB::Green;    
    leds[14] = CRGB::Green;    
    FastLED.show();
  }
  else
  {
    digitalWrite(led, LOW);
    
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    leds[8] = CRGB::Black;
    leds[8] = CRGB::Black;
    leds[9] = CRGB::Black;
    leds[10] = CRGB::Black;
    leds[11] = CRGB::Black;
    leds[12] = CRGB::Black;
    leds[13] = CRGB::Black;    
    leds[14] = CRGB::Black;    
    FastLED.show();
  }
}

void read_serial_data (void)
{
  static unsigned int state = 0;
  int data;
  
  // read data only when you receive data:
  if (Serial.available() > 0)
  {
    // read the incoming byte
    data = Serial.read();
    
    switch (state)
    {
      // start by looking for the START sequence of bytes: 0x18 0x5a 0x5a 0x5a 0x5a 0x55 0xaa
      case 0:
      if (data == 24)
      {
        state++;
      }
      else state = 0; 
      break;
      
      case 1:
      if (data == 90)
      {
        state++;
      }
      else state = 0;
      break;
    
      case 2:
      if (data == 90)
      {
        state++;
      }
      else state = 0;
      break;

      case 3:
      if (data == 90)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 4:
      if (data == 90)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 5:
      if (data == 85)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 6:
      if (data == 170)
      {
        state++;
      }
      else state = 0;
      break;
     
      // next 2 bytes are voltage
      case 7:   
      state++;
      break;
     
      case 8:   
      state++;
      break;

      // next 2 bytes are speed
      case 9:   
      state++;
      speed_temp1 = (data << 8);
      break;
       
      case 10:   
      state++;
      speed_temp2 = speed_temp1 | data;
      break;      

      // next 4 bytes are trip distance
      case 11:
      state++;   
      break;
     
      case 12:   
      state++;
      break; 
      
      case 13:   
      state++;
      break;
     
      case 14:   
      state++;
      break;

      // next 2 bytes are current
      case 15:   
      state++;
      current_temp1 = (data << 8);
      break;
     
      case 16:   
      state++;
      current_temp2 = current_temp1 | data;      
      break;
      
      // next 2 bytes are temperature
      case 17:   
      state++;
      break;
     
      case 18:   
      state++;
      break;
      
      case 19:
      if (data == 0)
      {
        state++;
      }
      else state = 0; 
      break;
      
      case 20:
      if (data == 0)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 21:
      if (data == 255)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 22:
      if (data == 248)
      {
        state++;
      }
      else state = 0;
      break;
      
      case 23:
      if (data == 0)
      {
        state = 0;
        
        speed = speed_temp2;
        current = current_temp2;
      }
      else state = 0;
      break;
      
      default:
      state = 0;
      break;
    }
  }
}

