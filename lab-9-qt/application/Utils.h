#pragma once

#include <iostream>

#include <QObject>

/**
 * Вспомогательная функция для отслеживания момента вызова деструктора какого-либо объекта-наследника QObject.
 *
 * @param object Объект, у которого необходимо отследить момент вызова деструктора.
 * @param message Сообщение для вывода на экран.
 */
void trackDestructor(QObject *object, const char *message) {
    QObject::connect(object, &QObject::destroyed, object, [&message]() { std::cout << message << std::endl; });
}
