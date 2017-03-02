#include "tuned_note.h"

tuned_note::tuned_note() {
    this->pitch = -1;
    this->distance = -2;
}

tuned_note::tuned_note(int pitch, double distance) : pitch(pitch), distance(distance) {
    this->pitch = pitch;
    this->distance = distance;
}

int tuned_note::getPitch() const {
    return pitch;
}

void tuned_note::setPitch(int pitch) {
    tuned_note::pitch = pitch;
}

double tuned_note::getDistance() const {
    return distance;
}

void tuned_note::setDistance(double distance) {
    tuned_note::distance = distance;
}
