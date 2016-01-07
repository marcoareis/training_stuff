#include <QtWidgets>
#include <QCoreApplication>
#include "window.h"
#include <iostream>

Window::Window(QWidget *parent)
    : QWidget(parent)


{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createTheOrientation(), 0, 0);
    grid->addWidget(createThePosition(), 1, 0);
    grid->addWidget(firulinha(), 0, 1);
    setLayout(grid);

    setWindowTitle(tr("Boat Information"));
    resize(300, 200);
}

QGroupBox *Window::createTheOrientation()
{
    QGroupBox *groupBox = new QGroupBox(tr("Orientation"));

    QLabel *roll = new QLabel(tr("Roll"));
    QLabel *pitch= new QLabel(tr("Pitch"));
    QLabel *yaw = new QLabel(tr("Yaw"));


    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(roll);
    vbox1->addWidget(pitch);
    vbox1->addWidget(yaw);
    vbox1->addStretch(1);
    groupBox->setLayout(vbox1);

    return groupBox;
}

QGroupBox *Window::createThePosition()
{
    QGroupBox *groupBox = new QGroupBox(tr("Position"));

    QLabel *xPos = new QLabel(tr("X"));
    QLabel *yPos= new QLabel(tr("Y"));
    QLabel *zPos = new QLabel(tr("Z"));



    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(xPos);
    vbox2->addWidget(yPos);
    vbox2->addWidget(zPos);
    vbox2->addStretch(1);
    groupBox->setLayout(vbox2);

    return groupBox;
}






QGroupBox *Window::firulinha()
{
    QGroupBox *groupBox = new QGroupBox(tr("Testbereiche"));

     m_button = new QPushButton("o toque de cabeca", this);
     m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

     connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

return groupBox;
}




void Window::handleButton()
{
    m_button->setText("olha o gol");

    std::cout << "APERTOU NE VIADO!" << std::endl;

}













