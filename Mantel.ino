#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERRUPT_RETRY_COUNT 1
#include <FastLED.h>
#define NUM_LEDS 497
#define DATA_PIN D7
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define FIRE_LEDS    20
#define MAXBRIGHTNESS 255
#define BRIGHTNESS  180
#define FRAMES_PER_SECOND 60
#define COOLING  55
#define SPARKING 120
#define NUM_ROWS  19
#define ROWLENGTH 29
#define RAINTIME 30
#define MAX_DROPLENGTH 10
#define FIRE 1
#define WATER 2
#define SPARKLE 3
#define RAIN 4
#define MATRIX 5
#define NUM_MODES 5


struct Flash {
  int value = 0;
  int increment = 1;
  bool flashing = false;
};

int ledMatrix [19][29] = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26},
{55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27},
{56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83},
{106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84},
{107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127},
{148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128},
{149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175},
{203,202,201,200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176},
{204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232},
{261,260,259,258,257,256,255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233},
{262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290},
{319,318,317,316,315,314,313,312,311,310,309,308,307,306,305,304,303,302,301,300,299,298,297,296,295,294,293,292,291},
{320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346},
{367,366,365,364,363,362,361,360,359,358,357,356,355,354,353,352,351,350,349,348,347},
{368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388},
{414,413,412,411,410,409,408,407,406,405,404,403,402,401,400,399,398,397,396,395,394,393,392,391,390,389},
{415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443},
{469,468,467,466,465,464,463,462,461,460,459,458,457,456,455,454,453,452,451,450,449,448,447,446,445,444},
{470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496}
};


extern const TProgmemRGBPalette16 MatrixColors_p FL_PROGMEM = {
  CRGB::Black,
  CRGB::Black,
  CRGB::DarkGreen,
  CRGB::DarkGreen,
  CRGB::ForestGreen,
  CRGB::ForestGreen
};

struct Raindrop { 
  int droplength = 5;
  int endpos = 0;
  int row = 0;
  int speed = 0;
  bool active = false;
};
Flash* flashedLEDS = new Flash[NUM_LEDS];
Raindrop RainLEDs[NUM_ROWS*3];

bool gReverseDirection = false;
CRGBPalette16 gPal;


CRGB leds[NUM_LEDS];
int modeswitch = 0;
int colormode = 1;

void setup() {
  Serial.begin(9600);
  delay(3000); // sanity delay
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  modeswitch = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  random16_add_entropy( random(65500));
  switch (colormode) { 
     case FIRE: {
      Fire2012WithPalette();
     }; break;
     case WATER: {
      Fire2012WithPalette();
     }; break;
     case RAIN: {
      Rain(CRGB::Black);
     }; break;
     case MATRIX: {
      Rain(CRGB::Green);
     }; break;
     case SPARKLE: {
      sparkle();
     }; break;
  }
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  if (millis() > modeswitch+10000) {
    if (colormode == NUM_MODES) {
      colormode = 1;
    }
    else {
      colormode++;
      Serial.print ("New Colormode ");
      Serial.println(colormode);
    }
    switchTo(colormode);
    modeswitch = millis();
  }
  
}
