#ifndef EECS_352_PROJECT_NOTE_H
#define EECS_352_PROJECT_NOTE_H

// Object returned by pitch_utils/freq_to_note(double freq, std::array<double, 88> pitch_freqs)

class tuned_note {
public:
    tuned_note(int pitch, double distance);

    tuned_note();

    int getPitch() const;

    void setPitch(int pitch);

    double getDistance() const;

    void setDistance(double distance);

private:
    // index of the closest pitch (ranges from 0 to 87)
    int pitch;
    // distance from pitch, where -1 represents maximally flat, 1 represents maximally sharp, and 0 represents in tune
    double distance;
};


#endif //EECS_352_PROJECT_NOTE_H
