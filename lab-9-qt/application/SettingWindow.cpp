#include "SettingWindow.h"
#include <QFormLayout>
#include <QIcon>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTabWidget>
#include <QLabel>

void SettingsWindow::fruitChanged(qint32 value)  {
    emit changeF(value,false);
};

void SettingsWindow::difficultyChanged(qint32 value)  {
    emit changeD(value);
};


SettingsWindow::SettingsWindow(Settings& settings) : _settings(settings) {
    setWindowIcon(QIcon("resources/settings.png"));
    setWindowTitle(u8"Настройки");

    const auto rootLayout = new QVBoxLayout;
    const auto tabWidget = new QTabWidget;

    tabWidget->addTab(createFirstTab(), u8"Фрукт");
    tabWidget->addTab(createSecondTab(), u8"Сложность");

    const auto closeButton = new QPushButton(u8"Закрыть");
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    rootLayout->addWidget(tabWidget);
    rootLayout->addWidget(closeButton);
    rootLayout->setAlignment(closeButton, Qt::AlignRight);
    setLayout(rootLayout);
}

QWidget* SettingsWindow:: createFirstTab() {
    const auto widget = new QWidget;

    QRadioButton* raspberry = new QRadioButton(u8"Малина", widget);
    QRadioButton* pineapple = new QRadioButton(u8"Ананас", widget);
    QRadioButton* grape = new QRadioButton(u8"Виноград", widget);
    QRadioButton* apple = new QRadioButton(u8"Яблоко", widget);
    QRadioButton* pear = new QRadioButton(u8"Груша", widget);
    QRadioButton* strawberry = new QRadioButton(u8"Клубника", widget);
    QRadioButton* cherry = new QRadioButton(u8"Вишня", widget);
    QRadioButton* random = new QRadioButton(u8"Случайный", widget);

    QButtonGroup* group = new QButtonGroup;
    group->addButton(raspberry, 1);
    group->addButton(pineapple, 2);
    group->addButton(grape, 3);
    group->addButton(apple, 4);
    group->addButton(pear, 5);
    group->addButton(strawberry, 6);
    group->addButton(cherry, 7);
    group->addButton(random, 8);

    for (qint32 i = 1; i < 9; ++i) {
        connect(group->button(i), &QRadioButton::clicked, [=]() { this->fruitChanged(i); });
    }

    const auto rootLayout = new QFormLayout;
    const auto text = new QLabel;
    text->setText(u8"Настройка фрукта: ");

    rootLayout->addRow(text);
    rootLayout->addRow(raspberry);
    rootLayout->addRow(pineapple);
    rootLayout->addRow(grape);
    rootLayout->addRow(apple);
    rootLayout->addRow(pear);
    rootLayout->addRow(strawberry);
    rootLayout->addRow(cherry);
    rootLayout->addRow(random);
    widget->setLayout(rootLayout);
    return widget;
}
QWidget* SettingsWindow::createSecondTab() {
    const auto widget = new QWidget;
    const auto rootLayout = new QFormLayout;

    const auto text = new QLabel;
    text->setText(u8"Настройка сложности: ");
 
    QRadioButton* easy = new QRadioButton(u8"Легкая", widget);
    QRadioButton* medium = new QRadioButton(u8"Нормальная", widget);
    QRadioButton* hard = new QRadioButton(u8"Сложная", widget);

    QButtonGroup* group = new QButtonGroup;
    group->addButton(easy, 140);
    group->addButton(medium, 100);
    group->addButton(hard, 60);

    for (qint32 i = 140; i > 59; i -= 40) {
        connect(group->button(i), &QRadioButton::clicked, [=]() { this->difficultyChanged(i); });
    }

    rootLayout->addRow(text);
    rootLayout->addRow(easy);
    rootLayout->addRow(medium);
    rootLayout->addRow(hard);
    widget->setLayout(rootLayout);
  
    return widget;
}