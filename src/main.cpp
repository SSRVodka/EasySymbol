#include <QtCore/QTextCodec>
#include <QtWidgets/QApplication>

#include "mainWindow.h"


int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough
    );
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(
        QTextCodec::codecForName("UTF-8")
    );

    mainWindow win;
    win.show();

    return app.exec();
}
