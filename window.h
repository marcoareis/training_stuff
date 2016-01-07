
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>

class QGroupBox;

class Window : public QWidget
{
    Q_OBJECT

public:
//    Window(QWidget *parent = 0);

    QGroupBox *createTheOrientation();
    QGroupBox *createThePosition();
    QGroupBox *firulinha();

explicit Window(QWidget *parent = 0);

private slots:
    void handleButton();
private:
    QPushButton *m_button;
};

#endif
