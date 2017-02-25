#include <QApplication>
#include <QSurfaceFormat>

#include "openglwidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication a(argc, argv);

    QSurfaceFormat f = QSurfaceFormat::defaultFormat();
    f.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(f);

    OpenGLWidget w;
    w.show();

    return a.exec();
}
