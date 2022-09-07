#include "window.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsScene>
#include <QLabel>
#include "SettingWindow.h"

MainWindow::MainWindow() {
    setFixedSize(QSize(576, 576));
    setWindowIcon(QIcon("resources/snake-icon.png"));
    setWindowTitle("Snake");
    const auto fileMenu = menuBar()->addMenu(u8"Настройки");
    const auto showSettingsAction = fileMenu->addAction(QIcon("resources/settings.png"), u8"Настройки");
    const auto exitAction = fileMenu->addAction(u8"Выход");


    connect(showSettingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);


    _snake = new Snake(_settings, this);
    _statusBar = new QLabel;
               
    setCentralWidget(_snake);
    connect(_snake, &Snake::statusBarMustUpdate, this, &MainWindow::refreshStatusBar);

    refreshStatusBar();
}

void MainWindow::refreshStatusBar() {
    
    QString text;
    text = QString(u8"Ваш текущий результат: %1").arg(_snake->getScore());
    _statusBar->setText(text);
    statusBar()->addWidget(_statusBar);
    setFixedSize(sizeHint());
}

void MainWindow::showSettings() {
    const auto settingsWindow = new SettingsWindow(_settings);
    connect(settingsWindow, &SettingsWindow::changeF, _snake, &Snake::changeFruitIcon);
    connect(settingsWindow, &SettingsWindow::changeD, _snake, &Snake::changeDifficulty);
    settingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    settingsWindow->setFixedSize(settingsWindow->sizeHint());
    settingsWindow->setParent(this);
    settingsWindow->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    settingsWindow->setWindowModality(Qt::WindowModal);
    settingsWindow->show();
}
