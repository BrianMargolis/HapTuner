#include <array>
#include "stdlib.h"
#include "printf.h"
#include "main.h"
#include "dywapitchtrack.h"
#include "pitch_utils.h"

int main() {
    dywapitchtracker pitchtracker;
    dywapitch_inittracking(&pitchtracker);
    printf("main\n");

    std::array<double, 88> pitch_freqs = get_pitch_freqs(440.0);
    std::array<note_name*, 88> pitch_names = get_pitch_names();

    for (int i = 0; i < 88; i++) {
        printf("f: %f \n", pitch_freqs[i]);
        printf("f: %c%c \n", pitch_names[i]->getName(), pitch_names[i]->getModifier());
    }

    int is_pitch_tracking = 0;
    double *samples = 0; // TODO: point to signal to pitch track
    int startsample = 0;
    int samplecount = 1024 * 4;

    while (is_pitch_tracking) {
        double freq = dywapitch_computepitch(&pitchtracker, samples, startsample, samplecount);
        printf("freq %f", freq);

        note n = freq_to_note(freq, pitch_freqs);
        printf("closest note %d", n.getPitch());
        printf("distance to closest note %f", n.getDistance());
    }

    return 1;
}
