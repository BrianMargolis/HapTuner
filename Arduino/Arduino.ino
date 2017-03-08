/* FreqMeasure - Example with serial output
 * http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
 *
 * This example code is in the public domain.
 */

#include <array>
#include <vector>

#include <FreqMeasure.h>
#include "pitch_utils.h"
#include "note_name.h"
#include "tuned_note.h"

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
double sum=0;
int count=0;


  std::vector<float> freqs;
  std::vector<tuned_note> notes;
  
void loop() {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float frequency = FreqMeasure.countToFrequency(sum / count);

      freqs.push_back(frequency);

      // Find the nearest frequency and get that, as well as the distance from
      tuned_note n = freq_to_note(frequency, pitch_freqs);
      note_name name = *pitch_names[n.getPitch()];
      // Append it to the notes array
      notes.push_back(n);
      
      // Some useful print statements for debugging
      Serial.printf("freq %f", frequency);
      Serial.printf("closest tuned_note %c%c", name.getName(), name.getModifier());
      Serial.printf("distance to closest tuned_note %f", n.getDistance()); // note that this ranges from -1 (most flat) to 1 (most sharp).
      sum = 0;
      count = 0;
    }
  }
}

