#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPixmap>
#include <QSize>

#include <list>
#include <vector>
#include <random>

#include "Settings.h"

/**
 * Основное окно аквариума.
 */
class AquariumWindow : public QMainWindow {

Q_OBJECT

private:

    const int _timerInterval = 50;                 /**< Интервал, с котороым будет вызываться метод обновления сцены. */
    const QSize _maxBackgroundSize;                /**< Максимальный размер для фона аквариума. */
    const QSize _maxFishSize;                      /**< Максимальный размер для изображения рыбки. */
    Settings _settings;                            /**< Настройки аквариума. */
    QGraphicsScene *_scene;                        /**< Сцена аквариума (содержит фон и рыбки). */
    QSize _backgroundSize;                         /**< Актуальный размер отображаемого фона аквариума. */
    std::vector<QPixmap> _fishes;                  /**< Изображения рыбок, успешно загруженных из 'resources/fishes'. */
    std::list<QGraphicsPixmapItem *> _sceneFishes; /**< Объекты рыбок, добавленных на сцену. */
    std::mt19937 _random;                          /**< ГПСЧ. */

private slots:

    /**
     * Показывает окно настроек.
     */
    void showSettings();

    /**
     * Обновляет сцену: пересчитывает координаты рыбок, удаляет и добавляет рыбок при необходимости.
     */
    void updateScene();

public:

    /**
     * Конструктор по умолчанию. Задаёт максимальный размер фона - (1024, 768), максимальный размер рыбки - (64, 64).
     */
    AquariumWindow();

    /**
     * Конструктор с явным заданием максимальных размеров фона и рыбок.
     * @param maxBackgroundSize Максимальный размер фона.
     * @param maxFishSize Максимальный размер рыбки.
     */
    AquariumWindow(const QSize &maxBackgroundSize, const QSize &maxFishSize);

    /**
     * Запрещённый конструктор копирования.
     */
    AquariumWindow(const AquariumWindow &) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    AquariumWindow &operator=(const AquariumWindow &) = delete;

};
