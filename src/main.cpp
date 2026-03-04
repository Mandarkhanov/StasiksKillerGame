#include <QGuiApplication>

#include "core/stasiksKillerApplication.h"



int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    StasiksKillerApplication gameApp;

    return app.exec();
}
