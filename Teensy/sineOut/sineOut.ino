/*
  klein voorbeeld van audio uit, pitch aangestuurd met potmeter
  sluit de potmeter aan op pin 14/A0
*/


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//onderstaande code is door de audio-library-tool gegenereerd
//http://www.pjrc.com/teensy/gui/index.html

// GUItool: begin automatically generated code
AudioSynthWaveformSine sine1;    //xy=152,263
AudioOutputPT8211_2 pt8211_2_1;  //xy=497,254
AudioConnection patchCord1(sine1, 0, pt8211_2_1, 0);
AudioConnection patchCord2(sine1, 0, pt8211_2_1, 1);
// GUItool: end automatically generated code

//elapsedMillis is een type dat elke ms optelt, kan je tijd mee bijhouden.
elapsedMillis fps;

void setup() {
  pinMode(A0, INPUT);
  AudioMemory(32);

  //pas amplitude aan, begin laag, kijk daarna wat gewenst is
  sine1.amplitude(0.1);

  //de basisfrequentie van de sinus
  sine1.frequency(220);
}


//lees elke 24ms de potmeterdata
//map het naar freq-bereik, pas frequentie van sine1 aan.
void loop() {
  if (fps > 24) {
    fps = 0;
    int potIn = analogRead(A0);
    int freq = map(potIn, 0, 1023, 110, 550);
    sine1.frequency(freq);
  }
}