#include <QApplication>

#include "AquariumWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Возможные улучшения:
    // 1) дать каждой рыбке свою скорость;
    // 2) добавить возможность рыбке двигаться не только слева направо, но и справа налево;
    // 3) добавить возможность рыбке двигаться не строго по горизонтали, а под некоторым небольшим углом.

    AquariumWindow aquariumWindow;
    aquariumWindow.setFixedSize(aquariumWindow.sizeHint());
    aquariumWindow.show();

    return QApplication::exec();
}
