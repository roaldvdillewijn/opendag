/* voorbeeld voor audio-input
   er wordt audio uit de mic binnengehaald
   in de serial monitor is zichtbaar aan de hoeveelheid
  '>>' hoe hard de audio is.
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//onderstaande code is door de audio-library-tool gegenereerd
//http://www.pjrc.com/teensy/gui/index.html

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=119,52
AudioAnalyzePeak         peak1;          //xy=379,43
AudioConnection          patchCord1(i2s1, 0, peak1, 0);
// GUItool: end automatically generated code

//elapsedMillis is een type dat elke ms optelt, kan je tijd mee bijhouden.
elapsedMillis fps;

void setup() {
  AudioMemory(4);
  Serial.begin(9600);
  Serial.println("testHallo");
}

//check elke 24ms of er audio beschikbaar is
//laat de 'meter' uitschieten n.a.v. amplitudelevel 

void loop() {
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      int monoPeak = peak1.read() * 30.0;
      Serial.print("|");
      for (int cnt=0; cnt<monoPeak; cnt++) {
        Serial.print(">");
      }

      Serial.println();
    }
  }
}