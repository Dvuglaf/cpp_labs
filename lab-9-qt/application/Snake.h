#pragma once
#include <QWidget>
#include <QTimer>
#include "Fruit.h"
#include <QSize>
#include <QVector>
#include <QKeyEvent>
#include "Settings.h"
#include <random>
#include <QPainter>

/**
 * Виджет с игрой змейка.
 */
class Snake : public QWidget {
	Q_OBJECT

public:
	static const qint64 _DOT_SIZE = 24; /**< Размер одного объекта в виджете в пикселях. */
private:
	const QSize _size; /**< Размер окна. */
	std::mt19937 _random; /**< ГПСЧ. */
	enum class Directions {UP, LEFT, RIGHT, DOWN}; /**< Направление движения змейки. */
	bool _game = false; /**< Текущее состояние игры. */
	bool _left = false; /**< Нажата ли стрелка влево. */
	bool _right = false; /**< Нажата ли стрелка вправо. */
	bool _up = false; /**< Нажата ли стрелка вверх. */
	bool _down = false; /**< Нажата ли стрелка вниз. */
	bool  _randomFruit = true; /**< Генерировать ли изображение фрукта. */
	QImage _dot; /**< Изображение части змеи */
	Settings& _settings; /**< Настройки. */
	QTimer* _timer; /**< Таймер. */
	Fruit _fruit; /**< Фрукт. */
	Directions _direction ; /**< Текущее направление змейки. */
	qint32 _score = 0; /**< Количество собранных фруктов. */
	QVector<QPoint> _body; /**< Позиция всех фрагментов змейки. */

	/**
	 * Отображение надписи вначале игры.
	 *
	 * @params painter Рисовальщик.
	 */
	void pressStart(QPainter& painter);

	/**
	 * Проверка столкнования с фруктом.
	 */
	void eatFruit();

	/**
	 * Проверка столкнования с фрагментами змейки.
	 */
	void checkCollision();

	/**
	 * Процесс движения змейки.
	 */
	void move();


	/**
	 * Показать окно с реузьтатом при проигрыше.
	 */
	void showResult();

	/**
	 * Проигрыш.
	 */
	void gameOver();

	/**
	 * Событие, отвечающее за отрисовку кадра.
	 *
	 *@ params event Событие.
	 */
	void paintEvent(QPaintEvent* event);

	/**
	 * Событие, реагирующее на нажатия клавиш клавиатуры.
	 *
	 *@ params key Событие.
	 */
	void keyPressEvent(QKeyEvent* key);

	/**
	 * Получение пути изображения фрукта по индексу.
	 *
	 *@param index Индекс, определющий изображение фрукта.
	 *@return Путь к файлу.
	 */
	char* getPath(qint32 index);

private slots:
	/**
	 * Обработчик, отвечающий за обновление сцены.
	 */
	void updateScene();

	/**
	 * Обработчик, отвечающий за старт игры.
	 */
	void start();

	/**
	 * Обработчик, генерирующий сигнал о необходимости увеличить счёт.
	 */
	void scoreMustIncreament();

public slots:
	/**
	 * Обработчик, отвечающий за смену сложности.
	 *
	 *@param value Значение сложности.
	 */
	void changeDifficulty(qint32 value);

	/**
	* Обработчик, отвечающий за смену изображения фрукта.
	*
	* @param index Индекс, отвечающий за изображение фрукта.
	* @param random Флаг, отвечающей за то, является ли новое значение изображение рандомным.
	*/
	void changeFruitIcon(qint32 index , bool random);

signals:
	/**
	 * Сигнал о необходимости обновить состояние статус бара.
	 */
	void statusBarMustUpdate();

public:
	/**
	 * Получить текущий счет.
	 *
	 *@return Текущее значение счёта.
	 */
	int getScore();
public:
	/**
	 * Конструктор по умолчанию, задающий размер виджета 576х576.
	 *
	 *@paran parent Предок.
	 */
	Snake(Settings& settings, QWidget* parent = 0);

	/**
	 * Запрещённый конструктор копирования.
	 */
	Snake(const Snake&) = delete;

	/**
	 * Запрещённый оператор присваивания копированием.
	 */
	Snake& operator=(const Snake&) = delete;
};
