CRGB colorscale(int pos, int droplength) {
  int middle = (droplength / 2);
  if (droplength % 2 != 0) {
    if (pos == middle) {
      return ColorFromPalette(gPal, 0);
    }
    else {
      return ColorFromPalette(gPal, abs(pos-middle));
    }
  }
  else { 
    if (pos == (middle - 1) or pos == middle) { 
      return ColorFromPalette(gPal, 0);
    }
    else {
      if (pos > middle) {
          return ColorFromPalette(gPal, abs(pos-middle)-1);;
      }
      else {
        return ColorFromPalette(gPal, abs(pos-middle));
      }
    }
  }
  
  
}


void dim() { 
  for (int i = 0; i < NUM_LEDS; i++) {
    if (flashedLEDS[i].flashing == true) {
      flashedLEDS[i].value = max(min(flashedLEDS[i].value+10*flashedLEDS[i].increment, MAXBRIGHTNESS), 0);
      if (flashedLEDS[i].value == 0) {
        flashedLEDS[i].increment = 1; 
        flashedLEDS[i].flashing = false;
      }
      if (flashedLEDS[i].value >= MAXBRIGHTNESS) { 
        flashedLEDS[i].increment = -1;
      }
  
      leds[i] = CHSV (0, 0, flashedLEDS[i].value);
    }
  }
}

void CheckNewRain() { 
  bool noFit = false;
  int newRow = random(NUM_ROWS);
  for (int i = 0; i < sizeof(RainLEDs)/sizeof(RainLEDs[0]); i++) { 
    if (RainLEDs[i].active == true and RainLEDs[i].row == newRow and RainLEDs[i].endpos < ROWLENGTH-RainLEDs[i].droplength*2) {
      noFit = true;
      break;
    }
   }
   if (noFit == false) {
    addRaindrop(newRow);
    return;
   }
}

void addRaindrop(int row) {
  for (int i = 0; i < sizeof(RainLEDs)/sizeof(RainLEDs[0]); i++) {
    if (RainLEDs[i].active == false) {
  
      RainLEDs[i].active = true;
      RainLEDs[i].droplength = random(MAX_DROPLENGTH);
      RainLEDs[i].endpos = ROWLENGTH+RainLEDs[i].droplength;
      RainLEDs[i].row = row;

      return;
    }
  }
  Serial.println("Alles inactive");
} 


void switchTo(int colormode) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();        
  switch (colormode) {
    case FIRE: {
      gPal = HeatColors_p;
    }; break;
    case WATER: {
      gPal = OceanColors_p;
    }; break;

    case SPARKLE: {
      
    }; break;

    case RAIN: {
      gPal = OceanColors_p;
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();   
    }; break;

    case MATRIX: {
      gPal = MatrixColors_p;
      fill_solid(leds, NUM_LEDS, CRGB::DarkGreen);
      FastLED.show();      
    }
  }
  
}
