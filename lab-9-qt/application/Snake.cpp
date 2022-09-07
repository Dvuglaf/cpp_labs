#include <QTimer>
#include "Snake.h"
#include <QPushButton>
#include <QObject>
#include <QVBoxLayout>
#include "GameOver.h"
#include <QIcon>
#include "SettingWindow.h"
#include <algorithm>

using namespace std;
Snake::Snake(Settings& settings, QWidget* parent) : QWidget(parent), _size(576, 576),  _random(random_device()()), _timer(new QTimer),  _direction(Directions::RIGHT), _settings(settings) {
    setFixedSize(_size);
    setFocusPolicy(Qt::StrongFocus);

    uniform_int_distribution<qint32> index(1, 7);
    changeFruitIcon(index(_random), true);

    resize(_size.width(), _size.height());
}
void Snake::start() {
    _score = 0;
    _fruit.spawnFruit(_DOT_SIZE);
    _game = true;
    _direction = Directions::RIGHT;

    _left = false;
    _right = false;
    _up = false;
    _down = false;

    delete _timer;
    _timer = new QTimer;

    connect(_timer, &QTimer::timeout, this, &Snake::updateScene);
    _timer->start(_settings.difficulty());


    _body.push_back(QPoint((qint64)288, (qint64)288));
    _body.push_back(QPoint((qint64)264, (qint64)288));
    _body.push_back(QPoint((qint64)240, (qint64)288));
    _body.push_back(QPoint((qint64)216, (qint64)288));

    //сигнал для обнуления статус бара
    emit statusBarMustUpdate();

}

void Snake::eatFruit() {

    if ((_body[0].x() == _fruit.fruitX()) && (_body[0].y() == _fruit.fruitY()) && _game) {
        _body.push_back(QPoint(_body[_body.size() - 1].x(), _body[_body.size() - 1].y()));
        _fruit.spawnFruit(_DOT_SIZE);
        ++_score;
        scoreMustIncreament();
        if (_randomFruit) {
            uniform_int_distribution<qint32> index(1, 7);
            changeFruitIcon(index(_random), true);
        }
    }
}

qint32 Snake::getScore() {
    return _score;
}

void Snake::move() {//
    if (_game) {
        for (auto it = end(_body) - 1; it != begin(_body); --it){
            *it = *(it - 1);
        }
    }
    switch (_direction) {
    case Directions::LEFT:
        _body[0].setX(_body[0].x() - _DOT_SIZE);
        _left = false;
        break;

    case Directions::UP:
        _body[0].setY(_body[0].y() - _DOT_SIZE);
        _up = false;
        break;

    case Directions::RIGHT:
        _body[0].setX(_body[0].x() + _DOT_SIZE);
        _right = false;
        break;

    case Directions::DOWN:
        _body[0].setY(_body[0].y() + _DOT_SIZE);
        _down = false;
        break;
    }
}

void Snake::checkCollision() {

    //столкновение с частями
    auto it = _body.begin() + 1;
    auto ret = std::find(it, _body.end(), *(_body.begin()));
    if (ret != _body.end()) {
        _game = false;
    }
    //

    //выход за края
    if (_body[0].y() >= _size.height()) {
        _game = false;
    }
    if (_body[0].y() < 0) {
        _game = false;
    }
    if (_body[0].x() >= _size.width()) {
        _game = false;
    }
    if (_body[0].x() < 0) {
        _game = false;
    }
    //

    if (!_game) {
        gameOver();
    }
}

void Snake::gameOver() {
    _timer->stop();
    _body.clear();
    showResult();
}


void Snake::pressStart(QPainter& painter) {

    QString message = "Press \"Enter\" to start.";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    qint32 textWidth = fm.width(message);

    painter.setPen(QColor(Qt::black));
    painter.setFont(font);
    painter.drawText(QPoint(textWidth/2, height()/2), message);
    painter.end();
}

void Snake::keyPressEvent(QKeyEvent* event) {
    qint64 key = event->key();

    if (key == Qt::Key_Enter-1 && !_game) {
        start();
    }
    if ((key == Qt::Key_Left) && (_direction != Directions::RIGHT) && !_right && !_up && !_left && !_down) {
        _left = true;
        _direction = Directions::LEFT;
    }

    if ((key == Qt::Key_Right) && (_direction != Directions::LEFT) && !_right && !_up && !_left && !_down) {
        _right = true;
        _direction = Directions::RIGHT;

    }

    if ((key == Qt::Key_Up) && (_direction != Directions::DOWN) && !_right && !_up && !_left && !_down) {

        _up = true;
        _direction = Directions::UP;

    }

    if ((key == Qt::Key_Down) && (_direction != Directions::UP) && !_right && !_up && !_left && !_down) {
        _down = true;
        _direction = Directions::DOWN;

    }
    QWidget::keyPressEvent(event);
}
void Snake::scoreMustIncreament() {

    emit statusBarMustUpdate();

}
void Snake::updateScene() {

    checkCollision();
    if (_game) {

        eatFruit();
        move();
    }
    repaint();
}

char* Snake::getPath(qint32 index) {
    if (index == 1) {
        return "resources/fruits/fruit1.png";
    }
    else if (index == 2) {
        return "resources/fruits/fruit2.png";
    }
    else if (index == 3) {
        return "resources/fruits/fruit3.png";
    }
    else if (index == 4) {
        return "resources/fruits/fruit4.png";
    }
    else if (index == 5) {
        return "resources/fruits/fruit5.png";
    }
    else if (index == 6) {
        return "resources/fruits/fruit6.png";
    }
    else if (index == 7) {
        return "resources/fruits/fruit7.png";
    }
    else
        return nullptr;
}

void Snake::changeFruitIcon(qint32 index, bool random) {
    if (!random) {
        _randomFruit = false;;
    }

    char* path = getPath(index);

    if (index == 8) {
        uniform_int_distribution<qint32> xDist(1, 7);
        path = getPath(xDist(_random));
        _settings.fruit()->load(path);
        _randomFruit = true;
        return;
    }
    _settings.fruit()->load(path);
}

void Snake::changeDifficulty(qint32 index) {
    _settings.setDifficulty(index);
}
void Snake::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawImage(0, 0, *(_settings.background()));

    if (!_game)
        pressStart(painter);

    if (_game) {

        painter.drawImage(_fruit.fruitX(), _fruit.fruitY(), *(_settings.fruit()));

        for (int i = 0; i < _body.size(); i++) {
            if (i == 0) {
                if (_direction == Directions::UP) {
                    _dot.load("resources/snake/head_up.png");
                }
                else if (_direction == Directions::LEFT) {
                    _dot.load("resources/snake/head_left.png");
                }
                else if (_direction == Directions::RIGHT) {
                    _dot.load("resources/snake/head_right.png");
                }
                else if (_direction == Directions::DOWN) {
                    _dot.load("resources/snake/head_down.png");
                }
            }
            else if (i == _body.size() - 1) {
                QPoint previous = _body[i - 1]; // Previous segment
                if (previous.y() < _body[i].y()) {
                    // Up
                    _dot.load("resources/snake/tail_down.png");
                }
                else if (previous.x() > _body[i].x()) {
                    // Right
                    _dot.load("resources/snake/tail_left.png");
                }
                else if (previous.y() > _body[i].y()) {
                    // Down
                    _dot.load("resources/snake/tail_up.png");
                }
                else if (previous.x() < _body[i].x()) {
                    // Left
                    _dot.load("resources/snake/tail_right.png");
                }
                painter.drawImage(_body[i].x(), _body[i].y(), _dot);

            }
            else {
                QPoint previous = _body[i - 1]; // Previous segment
                QPoint next = _body[i + 1]; // Next segment
                if (previous.x() < _body[i].x() && next.x() > _body[i].x() || next.x() < _body[i].x() && previous.x() > _body[i].x()) {
                    // Horizontal
                    _dot.load("resources/snake/right_left.png");
                }
                else if (previous.x() < _body[i].x() && next.y() > _body[i].y() || next.x() < _body[i].x() && previous.y() > _body[i].y()) {
                    _dot.load("resources/snake/down_left.png");
                }
                else if (previous.y() < _body[i].y() && next.y() > _body[i].y() || next.y() < _body[i].y() && previous.y() > _body[i].y()) {
                    // Vertical
                    _dot.load("resources/snake/up_down.png");
                }
                else if (previous.y() < _body[i].y() && next.x() < _body[i].x() || next.y() < _body[i].y() && previous.x() < _body[i].x()) {
                    _dot.load("resources/snake/up_left.png");
                }
                else if (previous.x() > _body[i].x() && next.y() < _body[i].y() || next.x() > _body[i].x() && previous.y() < _body[i].y()) {
                    _dot.load("resources/snake/up_right.png");
                }
                else if (previous.y() > _body[i].y() && next.x() > _body[i].x() || next.y() > _body[i].y() && previous.x() > _body[i].x()) {
                    _dot.load("resources/snake/down_right.png");
                }
            }
            painter.drawImage(_body[i].x(), _body[i].y(), _dot);

        }
    }
}

void Snake::showResult() {
    const auto finalsWindow = new GameOver(_score, this);
    finalsWindow->setAttribute(Qt::WA_DeleteOnClose);
    finalsWindow->setFixedSize(finalsWindow->sizeHint());
    finalsWindow->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    finalsWindow->setWindowModality(Qt::WindowModal);
    finalsWindow->show();
}