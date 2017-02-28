#include <math.h>
#include "stdlib.h"
#include "pitch_utils.h"


double *get_pitch_freqs(double reference) {
    // pointer to an array that will hold the frequencies of the 88 notes
    double *pitch_freqs = malloc(sizeof(double) * 88);

    pitch_freqs[48] = reference; // set A to reference (typically 440 Hz)

    // set all other values equal to 2^(n / 12) * reference, where n = distance between reference and that note
    for (int i = 0; i < 88; i++) {
        int diff = i - 48;
        pitch_freqs[i] = pow(2, diff / 12.0) * pitch_freqs[48];
    }

    return pitch_freqs;
}

note freq_to_note(double freq, double *pitch_freqs) {
    note n;

    int i = 0;
    while (i < 88 && freq < pitch_freqs[i]) {
        i++;
    }

    if (i + 1 < 88) {
        double left = pitch_freqs[i];
        double right = pitch_freqs[i + 1];
        double middle = left + right / 2;
        if (freq <= middle) {
            n.pitch = i;
            n.distance = (freq - left) / (middle - left);
        } else {
            n.pitch = i + 1;
            n.distance = (freq - right) / (middle - right);
        }
    } else {
        n.pitch = -1;
        n.distance = -2;
    }

    return n;
}