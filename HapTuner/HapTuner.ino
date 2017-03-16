#include <array>
#include <vector>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "pitch_utils.h"
#include "note_name.h"
#include "tuned_note.h"


AudioInputAnalog            adc;         
AudioAnalyzeNoteFrequency   notefreq;  
AudioConnection             patchCord1(adc, notefreq);


// declare reference arrays that are initialized in setup()
std::array<float, 88> pitch_freqs;
std::array<note_name *, 88> pitch_names;

int flat = 11; // pin 14
int sharp = 12; // pin 15

void setup() {
  Serial.begin(9600);
  AudioMemory(30);
  notefreq.begin(.15);

  // pitch_freqs[i] = frequency of the ith tuned_note on a piano (A0 = 0)
  float reference = 440.0;
  pitch_freqs = get_pitch_freqs(reference);

  // pitch_names[i] = *(tuned_note object with letter (ABCDEFG), modifier (n#b), and octave number for the ith tuned_note on a piano (A0 = 0))
  pitch_names = get_pitch_names();
  pinMode(flat, OUTPUT);
  pinMode(sharp, OUTPUT);
  delay(1000); // TODO: adjust!
}

float freq, prob;
int doit = 0;
double tolerance = .02; // acceptable distance from a note to be "in tune"

void loop() {
  if (notefreq.available()) {
    freq = notefreq.read();
    prob = notefreq.probability();

    // get the nearest note
    tuned_note n = freq_to_note(freq, pitch_freqs);
    int index = n.getPitch();
    double distance = n.getDistance();

    note_name note = *pitch_names[index];
    char name = note.getName();
    char modifier = note.getModifier();

    // useful print statements for debugging
    Serial.printf("freq %f\n", freq);
    Serial.printf("closest tuned_note %c%c\n", name, modifier);
    Serial.printf("distance to closest tuned_note %f\n\n", distance); // note that this ranges from -1 (most flat) to 1 (most sharp).

    if (distance < -tolerance) {
      digitalWrite(flat, HIGH);
      digitalWrite(sharp, LOW);
    } else if (distance > tolerance) {
      digitalWrite(flat, LOW);
      digitalWrite(sharp, HIGH);
    } else {
      digitalWrite(flat, LOW);
      digitalWrite(sharp, LOW);
    }
  }
}

