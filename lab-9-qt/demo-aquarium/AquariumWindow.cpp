#include "AquariumWindow.h"

#include <QAction>
#include <QDir>
#include <QIcon>
#include <QGraphicsView>
#include <QMenuBar>
#include <QTimer>

#include "SettingsWindow.h"

using namespace std;

/**
 * Пропорционально уменьшает размеры изображения, чтобы они не превосходили указанные максимальные размеры.
 *
 * @param bitmap Изображение для масштабирования.
 * @param maxSize Максимальные размеры.
 */
void static scale(QPixmap &bitmap, const QSize &maxSize) {
    auto size = bitmap.size();
    while (size.width() > maxSize.width() || size.height() > maxSize.height()) {
        size /= 2;
        bitmap = bitmap.scaled(size);
    }
}

void AquariumWindow::showSettings() {
    const auto settingsWindow = new SettingsWindow(_settings);
    settingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    settingsWindow->setFixedSize(settingsWindow->sizeHint());
    settingsWindow->setParent(this);
    settingsWindow->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    settingsWindow->setWindowModality(Qt::WindowModal);
    settingsWindow->show();
}

void AquariumWindow::updateScene() {
    // Обновление координат каждой рыбки на сцене и удаление при необходимости
    auto it = _sceneFishes.begin();
    while (it != _sceneFishes.end()) {
        auto sceneFish = *it;
        auto p = sceneFish->pos();
        p.setX(p.x() + static_cast<qreal>(_settings.speed()) / _timerInterval);
        if (p.x() > _backgroundSize.width()) {
            it = _sceneFishes.erase(it);
            _scene->removeItem(sceneFish);
            delete sceneFish;
        } else {
            sceneFish->setPos(p);
            ++it;
        }
    }

    // Добавление новых рыбок при необходимости
    if (_fishes.empty())
        return;
    const auto firstUpdate = _sceneFishes.empty();
    uniform_int_distribution<int> fishDist(0, static_cast<int>(_fishes.size()) - 1);
    uniform_int_distribution<int> xDist(0, _backgroundSize.width() - _maxFishSize.width() - 1);
    uniform_int_distribution<int> yDist(0, _backgroundSize.height() - _maxFishSize.height() - 1);
    while (static_cast<int>(_sceneFishes.size()) < _settings.fishCount()) {
        const auto fish = _fishes[fishDist(_random)];
        const auto sceneFish = new QGraphicsPixmapItem(fish);
        const auto x = firstUpdate ? xDist(_random) : -fish.width();
        const auto y = yDist(_random);
        sceneFish->setPos(x, y);
        _scene->addItem(sceneFish);
        _sceneFishes.push_back(sceneFish);
    }
}

AquariumWindow::AquariumWindow() :
        AquariumWindow(QSize(1024, 768), QSize(64, 64)) {}

AquariumWindow::AquariumWindow(const QSize &maxBackgroundSize, const QSize &maxFishSize) :
        _maxBackgroundSize(maxBackgroundSize), _maxFishSize(maxFishSize), _random(random_device()()) {
    // Настройка заголовка окна и меню
    setWindowIcon(QIcon("resources/icons/aquarium.png"));
    setWindowTitle(u8"Аквариум");
    const auto fileMenu = menuBar()->addMenu(u8"Файл");
    const auto showSettingsAction = fileMenu->addAction(QIcon("resources/icons/settings.png"), u8"Настройки аквариума");
    const auto exitAction = fileMenu->addAction(u8"Выход");
    connect(showSettingsAction, &QAction::triggered, this, &AquariumWindow::showSettings);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Загрузка фонового изображения
    QPixmap background("resources/background.jpg");
    scale(background, maxBackgroundSize);
    _backgroundSize = background.size();

    // Загрузка рыбок
    QDir dir("resources/fishes");
    for (const auto &fishFile: dir.entryInfoList(QDir::Files)) {
        QPixmap fish(fishFile.absoluteFilePath());
        if (!fish.isNull()) {
            scale(fish, maxFishSize);
            _fishes.push_back(fish);
        }
    }

    // Создание сцены с фоновым изображением и её отображение в окне
    _scene = new QGraphicsScene(this);
    _scene->addItem(new QGraphicsPixmapItem(background));
    const auto view = new QGraphicsView;
    view->setScene(_scene);
    view->setFrameShape(QFrame::Shape::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view);

    // Создание таймера для регулярного обновления сцены
    const auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AquariumWindow::updateScene);
    timer->start(_timerInterval);
}
