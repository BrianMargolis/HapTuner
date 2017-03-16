#include <math.h>
#include <stdlib.h>
#include <string>


#include "pitch_utils.h"

// Given a reference for A (typically 440) in Hz, computes an array of the frequencies for each of the 88 piano keys
std::array<float, 88> get_pitch_freqs(float reference) {
    // pointer to an array that will hold the frequencies of the 88 notes
    std::array<float, 88> pitch_freqs;

    int A_ref_index = 48; // A is the 49th tuned_note on the keyboard
    pitch_freqs[A_ref_index] = reference; // set A to reference (typically 440 Hz)

    // set all other values equal to 2^(n / 12) * reference, where n = distance between reference and that tuned_note
    for (int i = 0; i < 88; i++) {
        int diff = i - A_ref_index;
        pitch_freqs[i] = pow(2, diff / 12.0) * reference;
    }

    return pitch_freqs;
}

// Computes an array of the names and octaves for each of the 88 piano keys
// Note that it currently writes everything as a sharp - TODO: make flats happen!
std::array<note_name *, 88> get_pitch_names() {
    std::array<note_name *, 88> pitch_names;

    char name = 'A';
    char modifier = 'n';
    int octave_number = 0;
    for (int i = 0; i < 88; i++) {
        pitch_names[i] = new note_name();
        pitch_names[i]->setName(name);
        pitch_names[i]->setModifier(modifier);
        pitch_names[i]->setOctave(octave_number);

        if (modifier == '#' && name == 'G') {
            name = 'A';
            modifier = 'n';
        } else if (name == 'B') {
            octave_number++;
            name = 'C';
        } else if (name == 'E') {
            name = 'F';
        } else if (modifier == 'n') {
            modifier = '#';
        } else if (modifier == '#') {
            modifier = 'n';
            name++;
        }
    }
    return pitch_names;
}

// Given a frequency, it:
// 1) finds the two pitches it sits between
// 2) finds the mid-point between those two frequencies
// 3) figures out which side of the midpoint it's on, and picks that note as its "correct" value
// 4) calculates the distance from the picked note, where:
// *  1 is maximally sharp (i.e. any higher and it would be -1 for the next highest note)
// * -1 is maximally flat (i.e. any lower and it would be 1 for the next lowest note)
// *  0 is in tune
tuned_note freq_to_note(float freq, std::array<float, 88> pitch_freqs) {
    tuned_note n; // initialize with dummy values that we'll use to indicate error
    if (freq < pitch_freqs[1] || freq > pitch_freqs[87]) { // confirm that the frequency is within piano range
        return n;
    }

    // Run up the keyboard until we've found the pitch right below our frequency
    int i = 1;
    while (freq > pitch_freqs[i]) {
        i++;
    }

    double left = pitch_freqs[i - 1];       // note to the left of our freq
    double right = pitch_freqs[i];  // note to the right of our freq
    double middle = (left + right) / 2;   // midpoint
    if (freq <= middle) {
        n.setPitch(i - 1);
        n.setDistance((freq - left) / (middle - left));
    } else {
        n.setPitch(i);
        n.setDistance((right - freq) / (middle - right));
    }

    return n;
}
