#include <array>
#include <vector>

#include "pitch_utils.h"
#include "dywapitchtrack.h"

int main() {
    // Initialize a pitch tracker object as per the dywapitchtracker documentation (found in dywapitchtracker.h)
    dywapitchtracker pitchtracker;
    dywapitch_inittracking(&pitchtracker);

    // pitch_freqs[i] = frequency of the ith tuned_note on a piano (A0 = 0)
    double reference = 440.0;
    std::array<double, 88> pitch_freqs = get_pitch_freqs(reference);

    // pitch_names[i] = *(tuned_note object with letter (ABCDEFG), modifier (n#b), and octave number for the ith tuned_note on a piano (A0 = 0))
    std::array<note_name *, 88> pitch_names = get_pitch_names();

    /* BEGIN TESTING *
    for (int i = 0; i < 88; i++) {
        printf("f: %f \n", pitch_freqs[i]);
        printf("f: %c%c \n", pitch_names[i]->getName(), pitch_names[i]->getModifier());
    }
     /* END TESTING */

    // Values that will come from the signal loader function
    int n_samples = 0;
    double *samples_p = 0;

    // Parameters for binning the signal
    int startsample = 0;            // start at the beginning of the signal - TODO: allow user defined offset in secs, convert to samples, set as initial value for startsample
    int samplecount = 1024 * 4;     // bin length; good to use powers of 2 - TODO: use dywapitch_neededsamplecount(int minFreq) to get an actual value, then round up to nearest power of 2

    // Create vectors to accumulate the bin frequencies and tuned notes
    // TODO: calculate size on onset to save time by avoiding costly resizes
    std::vector<double> freqs;
    std::vector<tuned_note> notes;

    // For each bin in the signal (ignore the last bin if it's undersized)
    while (startsample + samplecount < n_samples) {
        // Get the frequency from dywapitch
        double freq = dywapitch_computepitch(&pitchtracker, samples_p, startsample, samplecount);
        // Append it to the freq array
        freqs.push_back(freq);

        // Find the nearest frequency and get that, as well as the distance from
        tuned_note n = freq_to_note(freq, pitch_freqs);
        note_name name = *pitch_names[n.getPitch()];
        // Append it to the notes array
        notes.push_back(n);

        // Some useful print statements for debugging
        printf("freq %f", freq);
        printf("closest tuned_note %c%c", name.getName(), name.getModifier());
        printf("distance to closest tuned_note %f",
               n.getDistance()); // note that this ranges from -1 (most flat) to 1 (most sharp).

        // Jump to the next bin
        startsample += samplecount;
    }

    // Print out freq and note vector values
    for (int i = 0; i < freqs.size(); i++) {
        printf("freq in window %d was %f; ", i, freqs[i]);
        printf("note  was %c%c\n", pitch_names[notes[i].getPitch()]->getName(),
               pitch_names[notes[i].getPitch()]->getModifier());
    }

    return 1;
}
