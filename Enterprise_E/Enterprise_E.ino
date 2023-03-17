#include "FastLED.h"

// Pride2015
// Animated, ever-changing rainbows.
// by Mark Kriegsman

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    9
#define DATA_PIN2   3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    100
#define BRIGHTNESS  255
#define STROBE_OUT5 5
#define STROBE_OUT6 6
#define STROBE_OUT7 7
#define STROBE_OUT8 8


CRGB hullleds[NUM_LEDS];
CRGB engineleds[NUM_LEDS];


void setup() {
// put your setup code here, to run once:
  pinMode(STROBE_OUT5, OUTPUT);  
  pinMode(STROBE_OUT6, OUTPUT);  
  pinMode(STROBE_OUT7, OUTPUT);  
  pinMode(STROBE_OUT8, OUTPUT);  
  delay(3000); // 3 second delay for recovery

  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(hullleds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);


 FastLED.addLeds<LED_TYPE,DATA_PIN2,COLOR_ORDER>(engineleds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);


  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

int count1 = 1;
int count2 = 1;
int engine = 0;

void loop()
{
  
  fill_solid(hullleds, NUM_LEDS, CRGB(BRIGHTNESS,BRIGHTNESS,BRIGHTNESS));

  FastLED.show();
  strobe1(2,150); // fast
  strobe2(100,100);  // slow
  //strobe2(2,100);  // slow
  engineEffect(120,230);
}



void strobe1(int off,int on) // SLOW STROBE
  {
    int t1=off;
    int t2=off+on;
    if (count1 <= t1){
          digitalWrite(STROBE_OUT5, HIGH); // turn LED on (output 5V)
    }
    
    else if ((count1 > t1) && (count1 <= t2)){
          digitalWrite(STROBE_OUT5, LOW); // turn LED on (output 5V)      
    }

    else{
      count1 = 0;
    }
    
    delay(1);
    count1++;
  
  }

  
void strobe2(int off, int on) //FAST STROBE
  {
    int t1=off;
    int t2=off+on;
    if (count2 <= t1){
          digitalWrite(STROBE_OUT6, HIGH); // turn LED on (output 5V)
          digitalWrite(STROBE_OUT7, HIGH); // turn LED on (output 5V)
          digitalWrite(STROBE_OUT8, HIGH); // turn LED on (output 5V)
          
    }
    
    else if ((count2 > t1) && (count2 <= t2)){
          digitalWrite(STROBE_OUT6, LOW); // turn LED on (output 5V)      
          digitalWrite(STROBE_OUT7, LOW); // turn LED on (output 5V)      
          digitalWrite(STROBE_OUT8, LOW); // turn LED on (output 5V)      
    }

    else{
      count2 = 0;
    }
    
    delay(1);
    count2++;


  
  }

    void engineEffect(int low, int high){
       static int count = 0;
       bool execute = false;
       int stepsize=5;
       count++;
       if(count % 1 == 0){
        execute = true;
       }
       else{
        execute = false;
       }
       static int engine[10] = {low,low,low,low,low,low,low,low,low,low};
       static bool dir[10] = {true,true,true,true,true,true,true,true,true,true};
       if(execute){
           int r = rand() % 10;
           stepsize=r/2;
           for(int i=0;i<r;i++){
           
             if(engine[r]>=high){
              engine[r]=high;
              dir[r]=false;
             }
             else if(engine[r] <= low){
              engine[r]=low;
              dir[r]=true;
             }
             if(dir[r]==true){
              engine[r]=engine[r]+stepsize;
             }
             else{
              engine[r]=engine[r]-stepsize;
             }
             fill_solid( engineleds, 1, CRGB(engine[0],engine[0],engine[0]));
             fill_solid( engineleds+1, 1, CRGB(engine[1],engine[1],engine[1]));
             fill_solid( engineleds+2, 1, CRGB(engine[2],engine[2],engine[2]));
             fill_solid( engineleds+3, 1, CRGB(engine[3],engine[3],engine[3]));
             fill_solid( engineleds+4, 1, CRGB(engine[4],engine[4],engine[4]));
             fill_solid( engineleds+5, 1, CRGB(engine[5],engine[5],engine[5]));
             fill_solid( engineleds+6, 1, CRGB(engine[6],engine[6],engine[6]));
             fill_solid( engineleds+7, 1, CRGB(engine[7],engine[7],engine[7]));
             fill_solid( engineleds+8, 1, CRGB(engine[8],engine[8],engine[8]));
             fill_solid( engineleds+9, 1, CRGB(255,255,255));
           }
       } 
         
      
    }


  
  
    
  

  
