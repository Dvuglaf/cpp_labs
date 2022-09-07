#include "Settings.h"


Settings::Settings() :_background(new QImage), _fruit(new QImage) { 
    _background->load("resources/background.png");
    
}

QImage* Settings::background() const {
    return _background;
}

QImage* Settings::fruit() const {
    return _fruit;
}

void Settings::setBackground(QImage* index) {
    _background = index;
}

void Settings::setFruit(QImage* index) {
    _fruit = index;
}
qint32 Settings::difficulty() const {
    return _difficulty;
}

void Settings::setDifficulty(const qint32 value) {
    value >= MIN_DIFFICULTY? _difficulty = MIN_DIFFICULTY : _difficulty = value;
    value <= MAX_DIFFICULTY ? _difficulty = MAX_DIFFICULTY : _difficulty = value;
}
