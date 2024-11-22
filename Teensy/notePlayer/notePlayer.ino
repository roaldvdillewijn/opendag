/*
Deze code soeelt een melodie af, de klank wordt gefilterd.
elke keer als je in de code hieronder een rij streepjes ziet, kan je het deel tot aan 
de rij met +-tekens aanpassen
draai aan een van de twee draaiknoppen om te horen welk effect het heeft.
*/ 

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioSynthWaveform       waveform1;      //xy=189,266
AudioFilterStateVariable filter1;        //xy=382,278
AudioOutputPT8211_2      pt8211_2_1;     //xy=765,379
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, pt8211_2_1, 0);
AudioConnection          patchCord3(filter1, 0, pt8211_2_1, 1);
int loopCounter = 0;
elapsedMillis waitTime;




//--------------------------------------------------------------------------------
//vul hieronder een lijst in met midinoten
int midiNotes[] = {60, 62, 64, 67, 69, 70};

//vul hieronder in hoe lang elke noot moet duren in miliseconden
unsigned long dur[] = {500, 1000, 250, 125, 250, 500};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




int loopLength = sizeof(midiNotes) / sizeof(midiNotes[0]);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  AudioMemory(32);

  //--------------------------------------------------------------------------------
  /*bepaal de golfvorm van de oscillator
  kies uit: 
    WAVEFORM_SINE
    WAVEFORM_SAWTOOTH
    WAVEFORM_SQUARE
    WAVEFORM_TRIANGLE
    WAVEFORM_PULSE
  */
  waveform1.begin(WAVEFORM_SAWTOOTH);

  //pas amplitude aan, begin laag, kijk daarna wat gewenst is
  waveform1.amplitude(0.1);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




  waveform1.frequency(220);
  filter1.frequency(330);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}


//lees elke 24ms de potmeterdata
//map het naar freq-bereik, pas frequentie van sine1 aan.
void loop() {
  int inOne = analogRead(A0);
  int inTwo = analogRead(A1);

  //--------------------------------------------------------------------------------
  // transformeer de data van de draaiknoppen naar bruikbare waarden
  int filterFreq = map(inTwo,0,1023,100,1500);
  float speedOffset = map(inOne,0,1023,0.1,2.0);
  if (waitTime > speedOffset * dur[loopCounter]) {
    waveform1.frequency(mtof(midiNotes[loopCounter]));
    filter1.frequency(filterFreq);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    
    
    waitTime = 0;
    if (loopCounter < loopLength - 1) {
      loopCounter++;
    }
    else {
      loopCounter = 0;
    }
  }
}

float mtof(int midi) {
  float result = exp(0.057762265 * (midi - 69));
  return 440 * result;
}

float floatMap(float in, float inMin, float inMax, float outMin, float outMax) {
  int tempOutMin = outMin * 1000;
  int tempOutMax = outMax * 1000;
  float result = map(in,inMin,inMax,tempOutMin,tempOutMax);
  result = result / 1000.;
  return result;
}