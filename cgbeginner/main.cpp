#include "openglwidget.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat f = QSurfaceFormat::defaultFormat();
    f.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(f);

    OpenGLWidget w;
    w.show();

    return a.exec();
}
