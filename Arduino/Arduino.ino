#include <array>
#include <vector>

#include <FreqMeasure.h>
#include "pitch_utils.h"
#include "note_name.h"
#include "tuned_note.h"

// declare reference arrays that are initialized in setup()
std::array<double, 88> pitch_freqs;
std::array<note_name *, 88> pitch_names;

void setup() {
  Serial.begin(57600);
  FreqMeasure.begin();

  // pitch_freqs[i] = frequency of the ith tuned_note on a piano (A0 = 0)
  double reference = 440.0;
  pitch_freqs = get_pitch_freqs(reference);

  // pitch_names[i] = *(tuned_note object with letter (ABCDEFG), modifier (n#b), and octave number for the ith tuned_note on a piano (A0 = 0))
  pitch_names = get_pitch_names();
}

// accumulators
double sum = 0;
int count = 0;

// accumulated frequency and note arrays
std::vector<float> freqs;
std::vector<tuned_note> notes;

void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      // tune the averaged frequency
      float frequency = FreqMeasure.countToFrequency(sum / count);
      // append it to the frequency array
      freqs.push_back(frequency);

      // get the nearest frequency and the distance from it
      tuned_note n = freq_to_note(frequency, pitch_freqs);
      note_name name = *pitch_names[n.getPitch()];
      // append it to the notes array
      notes.push_back(n);
      
      // some useful print statements for debugging
      Serial.printf("freq %f", frequency);
      Serial.printf("closest tuned_note %c%c", name.getName(), name.getModifier());
      Serial.printf("distance to closest tuned_note %f", n.getDistance()); // note that this ranges from -1 (most flat) to 1 (most sharp).

      // reset accumulators
      sum = 0;
      count = 0;
    }
  }
}
