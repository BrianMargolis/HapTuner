//
// Created by Brian Margolis on 3/1/17.
//

#include "note.h"

note::note() {
    this->pitch = -1;
    this->distance = -2;
}

note::note(int pitch, double distance) : pitch(pitch), distance(distance) {
    this->pitch = pitch;
    this->distance = distance;
}

int note::getPitch() const {
    return pitch;
}

void note::setPitch(int pitch) {
    note::pitch = pitch;
}

double note::getDistance() const {
    return distance;
}

void note::setDistance(double distance) {
    note::distance = distance;
}
