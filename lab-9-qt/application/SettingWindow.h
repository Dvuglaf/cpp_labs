#pragma once

#include <QImage>
#include <QWidget>
#include "Settings.h"

/**
 * Окно для отображения и возможного изменения настроек.
 */
class SettingsWindow : public QWidget {

Q_OBJECT

    Settings& _settings; /**< Настройки аквариума. */

private:
    /**
    * Создаёт виджет отображения настроек изображения фрукта.
    *
    * @return Виджет с PushButtons, отвечающий за изображение фрукта.
    */
    QWidget* createFirstTab();

    /**
    * Создаёт виджет отображения настроек сложности.
    *
    * @return Виджет с PushButtons, отвечающий за сложность игры.
    */
    QWidget* createSecondTab();

signals:
    /**
    * Сигнал генерируется, когда сложность необходимо изменить.
    *
    * @param index Значение cложности.
    */
    void changeD(qint32 index) ;

signals:
    /**
    * Сигнал генерируется, когда сложность необходимо изменить.
    *
    * @param index Индекс, отвечающий за изображение фрукта.
    * @param random Флаг, отвечающей за то, является ли новое значение изображение рандомным.
    */
    void changeF(qint32 index, bool random) ;

private slots:

    /**
    * Обработчик для события нажатия кнопки, отвечающей за сложность.
    *
    * @param index Новое значение cложности.
    */
    void difficultyChanged(qint32 index) ;

    /**
    * Обработчик для события нажатия кнопки, отвечающей за изображение фрукта .
    *
    * @param index Индекс, определющий изображение фрукта.
    */
    void fruitChanged(qint32 index) ;

public:

    /**
     * Конструктор.
     *
     * @param settings Настройки для отображения и возможного изменения.
     */
    explicit SettingsWindow(Settings& settings);

    /**
     * Запрещённый конструктор копирования.
     */
    SettingsWindow(const SettingsWindow&) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    SettingsWindow& operator=(const SettingsWindow&) = delete;

};