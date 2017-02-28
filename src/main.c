#include "stdlib.h"
#include "printf.h"
#include "main.h"
#include "dywapitchtrack.h"
#include "pitch_utils.h"

int main() {
    struct _dywapitchtracker *s_p = malloc(sizeof(struct _dywapitchtracker));
    dywapitch_inittracking(s_p);

    double *pitch_freqs = get_pitch_freqs(440.0);

    int is_pitch_tracking = 1;
    double *samples = 0; // TODO: point to signal to pitch track
    int startsample = 0;
    int samplecount = 1024 * 4;

    while (is_pitch_tracking) {
        double freq = dywapitch_computepitch(s_p, samples, startsample, samplecount);
        printf("freq %f", freq);

        note n = freq_to_note(freq, pitch_freqs);
        printf("closest note %d", n.pitch);
        printf("distance to closest note %f", n.distance);
    }
}
