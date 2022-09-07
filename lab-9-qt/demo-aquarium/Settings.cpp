#include "Settings.h"

#include <stdexcept>

Settings::Settings() : _fishCount((FISH_COUNT_MIN + FISH_COUNT_MAX) / 2), _speed((SPEED_MIN + SPEED_MAX) / 2) {}

int Settings::fishCount() const {
    return _fishCount;
}

int Settings::speed() const {
    return _speed;
}

void Settings::setFishCount(const int fishCount) {
    if (fishCount < FISH_COUNT_MIN || fishCount > FISH_COUNT_MAX)
        throw std::invalid_argument("fishCount");
    _fishCount = fishCount;
}

void Settings::setSpeed(const int speed) {
    if (speed < SPEED_MIN || speed > SPEED_MAX)
        throw std::invalid_argument("speed");
    _speed = speed;
}
