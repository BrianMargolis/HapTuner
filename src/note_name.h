#ifndef EECS_352_PROJECT_NOTE_NAME_H
#define EECS_352_PROJECT_NOTE_NAME_H

// Object used to keep track of the note name, modifier (i.e. sharp/flat/natural) and octave for a specific piano key

class note_name {
public:
    note_name();

    note_name(char name, char modifier, int octave);

    char getName() const;

    void setName(char name);

    char getModifier() const;

    void setModifier(char modifier);

    int getOctave() const;

    void setOctave(int octave);

private:
    // e.g. A, B, C...
    char name;
    // e.g. #, b
    char modifier;
    // octave number based on piano
    int octave;
};


#endif //EECS_352_PROJECT_NOTE_NAME_H
