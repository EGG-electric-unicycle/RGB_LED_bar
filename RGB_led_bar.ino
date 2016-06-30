#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      15

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

static int speed = 0;
static int speed_temp1 = 0;
static int speed_temp2 = 0;
static int current = 0;
static int current_temp1 = 0;
static int current_temp2 = 0;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setup()
{
  Serial.begin(115200); //opens serial port, sets data rate to 115200 bps
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  pixels.begin(); // This initializes the NeoPixel library.
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
  
  read_serial_data_and_process();
}

void read_serial_data_and_process (void)
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
        
        update_LEDs ();
      }
      else state = 0;
      break;
      
      default:
      state = 0;
      break;
    }
  }
}

void update_LEDs (void)
{
  if (current < 1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

    pixels.setPixelColor(0, pixels.Color(150,0,0));
    pixels.setPixelColor(1, pixels.Color(150,0,0));
    pixels.setPixelColor(2, pixels.Color(150,0,0));
    pixels.setPixelColor(3, pixels.Color(150,0,0));
    pixels.setPixelColor(4, pixels.Color(150,0,0));
    pixels.setPixelColor(5, pixels.Color(150,0,0));
    pixels.setPixelColor(6, pixels.Color(150,0,0));
    pixels.setPixelColor(7, pixels.Color(150,0,0));
    pixels.setPixelColor(8, pixels.Color(150,0,0));
    pixels.setPixelColor(9, pixels.Color(150,0,0));
    pixels.setPixelColor(10, pixels.Color(150,0,0));
    pixels.setPixelColor(11, pixels.Color(150,0,0));
    pixels.setPixelColor(12, pixels.Color(150,0,0));
    pixels.setPixelColor(13, pixels.Color(150,0,0));
    pixels.setPixelColor(14, pixels.Color(150,0,0));
    pixels.setPixelColor(15, pixels.Color(150,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  else
  {
    digitalWrite(led, LOW);
    
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.setPixelColor(4, pixels.Color(0,0,0));
    pixels.setPixelColor(5, pixels.Color(0,0,0));
    pixels.setPixelColor(6, pixels.Color(0,0,0));
    pixels.setPixelColor(7, pixels.Color(0,0,0));
    pixels.setPixelColor(8, pixels.Color(0,0,0));
    pixels.setPixelColor(9, pixels.Color(0,0,0));
    pixels.setPixelColor(10, pixels.Color(0,0,0));
    pixels.setPixelColor(11, pixels.Color(0,0,0));
    pixels.setPixelColor(12, pixels.Color(0,0,0));
    pixels.setPixelColor(13, pixels.Color(0,0,0));
    pixels.setPixelColor(14, pixels.Color(0,0,0)); 
    pixels.setPixelColor(15, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}


