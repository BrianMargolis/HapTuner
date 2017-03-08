#include "note_name.h"

note_name::note_name(char name, char modifier, int octave) : name(name), modifier(modifier), octave(octave) {
    this->name = name;
    this->modifier = modifier;
    this->octave = octave;
}

char note_name::getName() const {
    return name;
}

void note_name::setName(char name) {
    note_name::name = name;
}

char note_name::getModifier() const {
    return modifier;
}

void note_name::setModifier(char modifier) {
    note_name::modifier = modifier;
}

int note_name::getOctave() const {
    return octave;
}

void note_name::setOctave(int octave) {
    note_name::octave = octave;
}

note_name::note_name() {

}


