#include "presentation/views/MainWindow.h"
#include "utils/GuiUtils.h"
#include <QApplication>

#include <QFile>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Load global stylesheet
  QFile styleFile(":/resources/styles/main.qss");
  if (styleFile.open(QFile::ReadOnly)) {
    QString style = QLatin1String(styleFile.readAll());
    app.setStyleSheet(style);
  }

  GuiUtils::installGlobalEffect<QPushButton>(
      [](QWidget *w) { GuiUtils::addShadowEffect(w); },
      GuiUtils::WidgetState::Default);

  GuiUtils::installGlobalEffect<QPushButton>(
      [](QWidget *w) { GuiUtils::addTranslateEffect(w); },
      GuiUtils::WidgetState::Hover);

  // GuiUtils::installGlobalEffect<QPushButton>([](QWidget* w){
  // GuiUtils::addTranslateEffect(w, {0, }, 1); },
  //                                            GuiUtils::WidgetState::Pressed);

  MainWindow window;
  window.show();

  return app.exec();
}