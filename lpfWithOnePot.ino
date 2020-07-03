/*  Example of filtering a wave,
    using Mozzi sonification library.

    Demonstrates LowPassFilter().

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.com/Mozzi/

		Mozzi documentation/API
		https://sensorium.github.io/Mozzi/doc/html/index.html

		Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/chum9_int8.h> // recorded audio wavetable
#include <tables/cos2048_int8.h> // for filter modulation
#include <LowPassFilter.h>
#include <mozzi_rand.h>

Oscil<CHUM9_NUM_CELLS, AUDIO_RATE> aCrunchySound(CHUM9_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kFilterMod(COS2048_DATA);

LowPassFilter lpf;

//  Added
int cutoffPot = A2;    // cut-off pot will be on A2
int cutVal = 0; //a value to store cutoff freq amount


void setup(){
  startMozzi();
  aCrunchySound.setFreq(2.f);
  kFilterMod.setFreq(1.3f);
  lpf.setResonance(200);
}

void loop(){
  audioHook();
}

void updateControl(){
//  if (rand(CONTROL_RATE/2) == 0){ // about once every half second
//    kFilterMod.setFreq((float)rand(255)/64);  // choose a new modulation frequency
//  }
//  // map the modulation into the filter range (0-255)
//  byte cutoff_freq = 100 + kFilterMod.next()/2;
//  lpf.setCutoffFreq(cutoff_freq);

    cutVal = mozziAnalogRead(cutoffPot);
    cutVal = map(cutVal, 0, 1023, 0, 240);
    byte cutoff_freq = cutVal;
    lpf.setCutoffFreq(cutoff_freq);


}

int updateAudio(){
  char asig = lpf.next(aCrunchySound.next() >>1);
  return (int) asig;
}