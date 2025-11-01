#ifndef LIFTBUTTON_H
#define LIFTBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>

class LiftButton : public QWidget {
    Q_OBJECT
public:
    explicit LiftButton(const QString& text, QWidget* parent = nullptr);

    // Forward sizing to ensure layout is respected.
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QPushButton* button() const { return m_button; }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QPushButton* m_button;
    QPropertyAnimation* m_anim;
    QVBoxLayout* m_layout;
};


#endif