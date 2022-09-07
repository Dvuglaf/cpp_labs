#include "SettingsWindow.h"

#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

/**
 * Создаёт горизонтальный ползунок с установленными пределами и начальной позицией.
 *
 * @param min Нижний предел, соответствующей крайней левой позиции ползунка.
 * @param max Верхний предел, соответствующей крайней правой позиции ползунка.
 * @param value Текущая позиция ползунка.
 * @return Горизонтальный ползунок с установленными пределами и начальной позицией.
 */
static QSlider *createSlider(const int min, const int max, const int value) {
    const auto slider = new QSlider(Qt::Horizontal);
    slider->setFixedWidth(150);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(value);
    return slider;
}

void SettingsWindow::fishCountChanged(const int value) {
    _settings.setFishCount(value);
};

void SettingsWindow::speedChanged(const int value) {
    _settings.setSpeed(value);
};

SettingsWindow::SettingsWindow(Settings &settings) : _settings(settings) {
    // Настройка заголовка окна
    setWindowIcon(QIcon("resources/icons/settings.png"));
    setWindowTitle(u8"Настройки");

    // Формирование макета окна: ползунки
    const auto fishCountSlider = createSlider(Settings::FISH_COUNT_MIN, Settings::FISH_COUNT_MAX, settings.fishCount());
    const auto speedSlider = createSlider(Settings::SPEED_MIN, Settings::SPEED_MAX, settings.speed());
    connect(fishCountSlider, &QSlider::valueChanged, this, &SettingsWindow::fishCountChanged);
    connect(speedSlider, &QSlider::valueChanged, this, &SettingsWindow::speedChanged);
    const auto formLayout = new QFormLayout;
    formLayout->addRow(u8"Количество рыб:", fishCountSlider);
    formLayout->addRow(u8"Скорость:", speedSlider);

    // Формирование макета окна: кнопка
    const auto closeButton = new QPushButton(u8"Закрыть");
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    // Формирование итогового макета окна
    const auto rootLayout = new QVBoxLayout;
    rootLayout->addLayout(formLayout);
    rootLayout->addWidget(closeButton);
    rootLayout->setAlignment(closeButton, Qt::AlignRight);
    setLayout(rootLayout);
}
