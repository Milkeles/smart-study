#include "presentation/views/MainWindow.h"
#include "utils/GuiUtils.h"
#include <QApplication>

#include <QFile>

/*
 * List only button types that are not controlled by layouts!
 * Layouts break the position when you take away their control and later return
 * it.
 */
namespace {
const QSet<QString> kAnimatedButtons = {"PrimaryButton", "SecondaryButton",
                                        "TopicsAddButton"};
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Load global stylesheet
  QFile styleFile(":/resources/styles/main.qss");
  if (styleFile.open(QFile::ReadOnly)) {
    const QString style = QLatin1String(styleFile.readAll());
    app.setStyleSheet(style);
  }

  // Global shadow effect – only for selected buttons
  GuiUtils::installGlobalEffect<QPushButton>(
      [](QWidget *w) {
        auto *btn = qobject_cast<QPushButton *>(w);
        if (!btn)
          return;

        if (!kAnimatedButtons.contains(btn->objectName()))
          return;

        GuiUtils::addShadowEffect(btn);
      },
      GuiUtils::WidgetState::Default);

  GuiUtils::installGlobalEffect<QPushButton>(
      [](QWidget *w) {
        auto *btn = qobject_cast<QPushButton *>(w);
        if (!btn)
          return;

        if (!kAnimatedButtons.contains(btn->objectName()))
          return;

        GuiUtils::addTranslateEffect(btn);
      },
      GuiUtils::WidgetState::Hover);

  MainWindow window;
  window.show();

  return app.exec();
}
