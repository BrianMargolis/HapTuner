#ifndef EECS_352_PROJECT_PITCH_UTILS_H
#define EECS_352_PROJECT_PITCH_UTILS_H

#include <array>

#include "note_name.h"
#include "tuned_note.h"


std::array<double, 88> get_pitch_freqs(double reference);

std::array<note_name *, 88> get_pitch_names();

tuned_note freq_to_note(double freq, std::array<double, 88> pitch_freqs);


#endif //EECS_352_PROJECT_PITCH_UTILS_H
