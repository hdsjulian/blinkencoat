void Rain(CRGB basecolor) {
  static int RainTimer = 0;
   if (millis() > RainTimer + RAINTIME) { 
    int weird = millis();
    CheckNewRain();
    RainTimer = millis();
   }
  //alle tropfen durchgehen
  for (int i = 0; i < sizeof(RainLEDs)/sizeof(RainLEDs[0]); i++) {
    if (RainLEDs[i].endpos < ROWLENGTH/2 and ledMatrix[RainLEDs[i].row][RainLEDs[i].endpos] == 0) {
      
      
      RainLEDs[i].active = false;
    }
    if (RainLEDs[i].active == false) { 
      continue;
    }
    else { 
      //IRGENDWAS STIMMT MIT ENDPOS NICHT
      for (int j = 0; j< RainLEDs[i].droplength;j++) {
          if (RainLEDs[i].endpos+1 > 0 and RainLEDs[i].endpos+1 < ROWLENGTH) {

            leds[ledMatrix[RainLEDs[i].row][RainLEDs[i].endpos+1]] = basecolor;
          }
        if (RainLEDs[i].endpos-j > 0 and RainLEDs[i].endpos-j < ROWLENGTH) {
          
         if (RainLEDs[i].row != 0 and ledMatrix[RainLEDs[i].row][RainLEDs[i].endpos-j] == 0) {
          continue;
         }
         else {
          leds[ledMatrix[RainLEDs[i].row][RainLEDs[i].endpos-j]] = colorscale(j, RainLEDs[i].droplength);
         }
        }
      }
    }
    RainLEDs[i].endpos--;
  }
}


void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[sizeof(ledMatrix)/sizeof(ledMatrix[0])][FIRE_LEDS];
  // Step 1.  Cool down every cell a little
  for (int z = 0; z < sizeof(ledMatrix)/sizeof(ledMatrix[0]); z++) {

    for( int i = 0; i < FIRE_LEDS; i++) {
      heat[z][i] = qsub8( heat[z][i],  random8(0, ((COOLING * 10) / FIRE_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= FIRE_LEDS - 1; k >= 2; k--) {
      heat[z][k] = (heat[z][k - 1] + heat[z][k - 2] + heat[z][k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[z][y] = qadd8( heat[z][y], random8(160,255) );
    }
    
    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < FIRE_LEDS; j++) {
      //Serial.println("blub");
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[z][j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      leds[ledMatrix[z][j]] = color;
    }
    
  }
}


void sparkle() {
  static int lasttime = millis();
  static int lasttime2 = millis();
  
 if (millis() > lasttime+1) { 
  if (millis() > lasttime2+60 or lasttime2 == 0) { 
    while (true) { 
      int rando = random(NUM_LEDS);
      if (flashedLEDS[rando].flashing == false) {
        flashedLEDS[rando].flashing = true;
        break;
      }
    }
    lasttime2 = millis();
  }
  dim();
  lasttime = millis();
  FastLED.show();
 }
}
