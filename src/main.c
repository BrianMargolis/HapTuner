//
// Created by Brian Margolis on 2/25/17.
//

#include <stdlib.h>
#include "printf.h"
#include "main.h"
#include "dywapitchtrack.h"

int main() {
    struct _dywapitchtracker *s_p = malloc(sizeof(struct _dywapitchtracker));
    dywapitch_inittracking(s_p);

    int is_pitch_tracking = 1;
    double *samples = 0; // TODO: point to signal to pitch track
    int startsample = 0;
    int samplecount = 1024 * 4;

    while (is_pitch_tracking) {
        double freq = dywapitch_computepitch(s_p, samples, startsample, samplecount);
        printf("freq %f", freq);
    }
}
