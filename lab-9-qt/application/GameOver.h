#pragma once
#include <QWidget>

/**
 * Виджет с отображением счета при проигрыше.
 */
class GameOver :public QWidget {

Q_OBJECT

public:
    /**
     * Конструктор с параметрами.
     *
     *@param score Счет, выводимый на экран.
     *@param parent Предок
     */
	GameOver(qint64 score, QWidget* parent = 0);

    /**
     * Запрещённый конструктор копирования.
     */
    GameOver(const GameOver&) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    GameOver& operator=(const GameOver&) = delete;
};