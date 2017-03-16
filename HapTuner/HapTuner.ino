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

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=179,197
AudioAnalyzeNoteFrequency notefreq;      //xy=482,345
AudioConnection          patchCord1(adc1, notefreq);
// GUItool: end automatically generated code

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

// accumulated frequency and note arrays
std::vector<float> freqs;
std::vector<tuned_note> notes;

float freq, prob;
int doit = 0;
double tolerance = .01; // acceptable distance from a note to be "in tune"

void loop() {
  if (notefreq.available()) {
    freq = notefreq.read();
    prob = notefreq.probability();
//    Serial.printf("Note: %3.2f | Probability: %.2f\n", freq, prob);

    // get the nearest note
    tuned_note n = freq_to_note(freq, pitch_freqs);
    int index = n.getPitch();
    double distance = n.getDistance();

    note_name note = *pitch_names[index];
    char name = note.getName();
    char modifier = note.getModifier();

    // some useful print statements for debugging
    Serial.printf("freq %f\n", freq);
    Serial.printf("closest tuned_note %c%c\n", note.getName(), note.getModifier());
    Serial.printf("distance to closest tuned_note %f\n", n.getDistance()); // note that this ranges from -1 (most flat) to 1 (most sharp).

//    if (distance < -tolerance) {
//      digitalWrite(flat, HIGH);
//      digitalWrite(sharp, LOW);
//    } else if (distance > tolerance) {
//      digitalWrite(flat, LOW);
//      digitalWrite(sharp, HIGH);
//    } else {
//      digitalWrite(flat, LOW);
//      digitalWrite(sharp, LOW);
//    }

  }
}

