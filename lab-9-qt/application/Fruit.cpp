#include "Fruit.h"

using namespace std;
Fruit::Fruit(const qint32 dotSize) : _random(random_device()()) {
	spawnFruit(dotSize);
}

void Fruit::spawnFruit(const qint32 dotSize ) {
	uniform_int_distribution<qint32> x(0, dotSize - 1);
	uniform_int_distribution<qint32> y(0, dotSize - 1);

	_fruitX = x(_random);
	_fruitY = y(_random);

	_fruitX *= dotSize;
	_fruitY *= dotSize;
}

qint32 Fruit::fruitX() const {
	return _fruitX;
}

qint32 Fruit::fruitY() const {
	return _fruitY;
}