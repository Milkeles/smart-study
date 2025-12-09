#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "presentation/widgets/FlashCardManager.h"
#include "presentation/widgets/FlashCard.h" 

class FlashCardEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit FlashCardEditorWidget(FlashCardManager *manager,
                                   QWidget *parent = nullptr);

signals:
    void cardCreated(const QString &setName);
    void startFlashcardsRequested();

private slots:
    void onSave();
    void onStart();

private:
    FlashCardManager *manager;

    QVector<FlashCard> cards;
    int currentIndex = 0;

    QLineEdit *questionEdit;
    QTextEdit *answerEdit;
    QComboBox *setSelector;
    QPushButton *saveBtn;
    QPushButton *startBtn; 
    QLabel *questionLabel;
    QLabel *answerLabel;
    QPushButton *nextBtn;
    QPushButton *prevBtn;

    void loadSets();
};
