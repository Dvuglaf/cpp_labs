#include <QApplication>
#include <QWidget>


#include "Snake.h"
#include <QBrush>
#include <QPalette>
#include <QPixmap>
#include "window.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow widge1t;
    widge1t.show();

    return QApplication::exec();
}
