#pragma GCC push_options
#pragma GCC optimize ("O0")

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

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

struct Data_EUC {
   int voltage;
   int speed;
   int current;
   int flag;
} data_euc;  

void setup()
{
  Serial.begin(115200); //opens serial port, sets data rate to 115200 bps
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  pixels.begin(); // This initializes the NeoPixel library.
}

void read_serial_data (void)
{
  volatile static unsigned int state = 0;
  volatile int data;
  
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
      data_euc.speed = (data << 8);
      break;
       
      case 10:   
      state++;
      data_euc.speed |= data;
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
      data_euc.current = (data << 8);
      break;
     
      case 16:   
      state++;
      data_euc.current |= data;
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
        data_euc.flag = 1;
      }
      else state = 0;
      break;
      
      default:         
      state = 0;
      break;
    }
  }
}

void led_brake (void)
{
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

void pixels_step (void)
{
  static unsigned int step = 0;
  unsigned int next_step = 0;
  
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
  
  if (step > 0) step--;
  else step = NUMPIXELS - 1;
  next_step = step;
  pixels.setPixelColor(step, pixels.Color(150,150,0));

  if (step > 0) step--;
  else step = NUMPIXELS - 1;
  pixels.setPixelColor(step, pixels.Color(150,0,150));  

  if (step > 0) step--;
  else step = NUMPIXELS - 1;
  pixels.setPixelColor(step, pixels.Color(0,150,150));
 
  step = next_step;
 
  pixels.show(); // This sends the updated pixel color to the hardware. 
}

void loop()
{  
  volatile static unsigned long next_step_time = 0;
  static int speed;
  static int brake;

  read_serial_data ();

  if (data_euc.flag == 1)
  {
    data_euc.flag = 0;
    speed = data_euc.speed;
    
    // current = data_euc.current; // THIS BREAKS, seems there is a bug on Arduino compiler

    if (data_euc.current < 1)
    {
      led_brake ();
      brake = 1;
    }
    else
    {
      brake = 0;
    }
  }

  if (brake == 0)
  {
    if (speed > 30)
    {
      if (speed > 1000) speed = 2000;
      
      // verify if we need to make next step
      if (millis () > next_step_time)
      {
        next_step_time = millis() + (14000 / speed);
        pixels_step ();
      }
    }
  }
}

#pragma GCC pop_options

