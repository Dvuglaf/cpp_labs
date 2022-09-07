#pragma once

/**
 * Настройки аквариума.
 */
class Settings final {
    int _fishCount; /**< Требуемое количество рыбок на сцене. */
    int _speed;     /**< Скорость рыбок. */

public:
    static const int FISH_COUNT_MIN = 2;   /**< Минимальное количество рыбок на сцене. */
    static const int FISH_COUNT_MAX = 100; /**< Максимальное количество рыбок на сцене. */
    static const int SPEED_MIN = 50;       /**< Минимальная скорость рыбок. */
    static const int SPEED_MAX = 300;      /**< Максимальная скорость рыбок. */

    /**
     * Конструктор по умолчанию.
     */
    Settings();

    /**
     * Запрещённый конструктор копирования.
     */
    Settings(const Settings &) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    Settings &operator=(const Settings &) = delete;

    /**
     * Возвращает требуемое количество рыбок на сцене.
     *
     * @return Требуемое количество рыбок на сцене.
     */
    int fishCount() const;

    /**
     * Возвращает скорость рыбок на сцене.
     *
     * @return Скорость рыбок на сцене.
     */
    int speed() const;

    /**
     * Устанавливает требуемое количество рыбок на сцене.
     *
     * @param fishCount Требуемое количество рыбок на сцене.
     */
    void setFishCount(int fishCount);

    /**
     * Устанавливает скорость рыбок.
     *
     * @param speed Скорость рыбок.
     */
    void setSpeed(int speed);
};
