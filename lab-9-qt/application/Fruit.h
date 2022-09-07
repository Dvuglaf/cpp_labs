#pragma once
#include <QWidget>
#include <random>

/**
 * Случайно генерируемый фрукт, иконка - квадратная.
 */
class Fruit : public QWidget {

	qint32 _fruitX; /**< Позиция фрукта на оси ОХ. */
	qint32 _fruitY; /**< Позиция фрукта на оси ОУ. */
	std::mt19937 _random; /**< ГПСЧ. */

public:
	/**
	 * Конструктор с параметром.
	 *
	 * @param dotSize Занимаемый размер в окне в пикселях.
	 */
	Fruit(qint32 dotSize = 24);

	/**
	 * Запрещенный конструктор копирования.
	 */
	Fruit(const Fruit& ) = delete;

	/**
	 * Запрещенный оператор присваивания копированием.
	 */
	Fruit &operator= (const Fruit&) = delete;

	/**
	 * Создает фрукт со случайной позицией.
	 *
	 * @param dotSize Занимаемый размер в окне в пикселях
	 */
	void spawnFruit(qint32 dotSize);

	/**
	 * Получить позицию фрукта по оси ОХ.
	 *
	 * @return Позиция фрукта по оси ОХ.
	 */
	qint32 fruitX() const;

	/**
	 * Получить позицию фрукта по оси ОУ.
	 *
	 * @return Позиция фрукта по оси ОУ.
	 */
	qint32 fruitY() const;
};