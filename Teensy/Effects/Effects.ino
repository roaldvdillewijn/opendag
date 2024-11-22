/*
Deze code voegt een delay- en sample-rate-reductie toe aan de microfoon-input
elke keer als je in de code hieronder een rij streepjes ziet, kan je het deel tot aan 
de rij met +-tekens aanpassen
draai aan een van de twee draaiknoppen om te horen welk effect het heeft.
*/ 



#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;                 //xy=231,129
AudioEffectDelay delay1;            //xy=413,198
AudioMixer4 mixer1;                 //xy=658,173
AudioEffectBitcrusher bitcrusher1;  //xy=832,210
AudioOutputPT8211_2 pt8211_2_1;     //xy=1030,174
AudioConnection patchCord1(i2s1, 0, delay1, 0);
AudioConnection patchCord2(delay1, 0, mixer1, 0);
AudioConnection patchCord3(delay1, 1, mixer1, 1);
AudioConnection patchCord4(delay1, 2, mixer1, 2);
AudioConnection patchCord5(delay1, 3, mixer1, 3);
AudioConnection patchCord6(mixer1, bitcrusher1);
AudioConnection patchCord7(bitcrusher1, 0, pt8211_2_1, 0);
AudioConnection patchCord8(bitcrusher1, 0, pt8211_2_1, 1);
// GUItool: end automatically generated code


void setup() {
  // put your setup code here, to run once:

  AudioMemory(240);
  delay1.delay(0, 50);
  delay1.delay(1, 100);
  delay1.delay(2, 200);
  delay1.delay(3, 300);
  delay1.disable(4);
  delay1.disable(5);
  delay1.disable(6);
  delay1.disable(7);
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  int inOne = analogRead(A0);
  int inTwo = analogRead(A1);


  //--------------------------------------------------------------------------------
  // transformeer de data van de draaiknoppen naar bruikbare waarden
  int sampleRate = floatMap(inOne, 0, 1023, 100, 44100);
  float delayOffset = floatMap(inTwo, 0, 1023, 0.1, 1.5);

  //bepaal de samplerate (minimaal 100, maximaal 44100)
  bitcrusher1.sampleRate(sampleRate);

  //bepaal de delaytijd van de vier delays (minimaal 10, maximaal 500)
  delay1.delay(0, 50 * delayOffset);
  delay1.delay(1, 100 * delayOffset);
  delay1.delay(2, 200 * delayOffset);
  delay1.delay(3, 300 * delayOffset);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


}

float floatMap(float in, float inMin, float inMax, float outMin, float outMax) {
  int tempOutMin = outMin * 1000;
  int tempOutMax = outMax * 1000;
  float result = map(in,inMin,inMax,tempOutMin,tempOutMax);
  result = result / 1000.;
  return result;
}
