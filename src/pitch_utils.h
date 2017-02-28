#ifndef EECS_352_PROJECT_PITCH_UTILS_H
#define EECS_352_PROJECT_PITCH_UTILS_H


typedef struct _note {
    // index of the closest pitch (ranges from 0 to 87)
    int pitch;
    // distance from pitch, where -1 represents maximally flat, 1 represents maximally sharp, and 0 represents in tune
    double distance;
} note;

double *get_pitch_freqs(double reference);

note freq_to_note(double freq, double *pitch_freqs);


#endif //EECS_352_PROJECT_PITCH_UTILS_H
