#include <math.h>
#include "stdlib.h"
#include "pitch_utils.h"
#include "note.h"
#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>

std::array<double, 88> get_pitch_freqs(double reference) {
    // pointer to an array that will hold the frequencies of the 88 notes
    std::array<double, 88> pitch_freqs;

    int A_ref_index = 48; // A is the 49th note on the keyboard
    pitch_freqs[A_ref_index] = reference; // set A to reference (typically 440 Hz)

    // set all other values equal to 2^(n / 12) * reference, where n = distance between reference and that note
    for (int i = 0; i < 88; i++) {
        int diff = i - A_ref_index;
        pitch_freqs[i] = pow(2, diff / 12.0) * reference;
    }

    return pitch_freqs;
}

std::array<note_name*, 88> get_pitch_names() {
    std::array<note_name*, 88> pitch_names;

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

note freq_to_note(double freq, std::array<double, 88> pitch_freqs) {
    note n; // initialize with dummy values
    if (freq < pitch_freqs[0] || freq > pitch_freqs[87]) {
        return n;
    }
    int i = 0;
    while (i < 88 && freq < pitch_freqs[i]) {
        i++;
    }


    double left = pitch_freqs[i];
    double right = pitch_freqs[i + 1];
    double middle = left + right / 2;
    if (freq <= middle) {
        n.setPitch(i);
        n.setDistance((freq - left) / (middle - left));
    } else {
        n.setPitch(i + 1);
        n.setDistance((freq - right) / (middle - right));
    }

    return n;
}