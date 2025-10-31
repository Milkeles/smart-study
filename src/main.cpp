#include <QApplication>
#include "presentation/views/MainWindow.h"
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load global stylesheet
    QFile styleFile("resources/styles/main.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
    }

    MainWindow window;
    window.show();

    return app.exec();
}