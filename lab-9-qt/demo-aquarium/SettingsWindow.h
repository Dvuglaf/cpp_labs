#pragma once

#include <QWidget>

#include "Settings.h"

/**
 * Окно для отображения и возможного изменения настроек.
 */
class SettingsWindow : public QWidget {

Q_OBJECT

private:

    Settings &_settings; /**< Настройки аквариума. */

private slots:

    /**
     * Обработчик для события изменения ползунка, отвечающего за требуемое количество рыбок.
     *
     * @param value Новое значение ползунка.
     */
    void fishCountChanged(int value);

    /**
     * Обработчик для события изменения ползунка, отвечающего за скорость рыбок.
     *
     * @param value  Новое значение ползунка.
     */
    void speedChanged(int value);

public:

    /**
     * Конструктор.
     *
     * @param settings Настройки для отображения и возможного изменения.
     */
    explicit SettingsWindow(Settings &settings);

    /**
     * Запрещённый конструктор копирования.
     */
    SettingsWindow(const SettingsWindow &) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    SettingsWindow &operator=(const SettingsWindow &) = delete;

};
