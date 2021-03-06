#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <string>
#include <vector>
#include <iostream>
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)           //Constructor -->Prevent data usage that hasn't been initialized
{
    inputFile.open(fopen("/home/jubaskete/ufba/bir/poses.txt", "r"), QIODevice::ReadOnly);
    stream.setDevice(&inputFile);
    
    isPaused = false;
    loadPoses();
    places = 0;
    std::string s;


    //creating the timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(500);

    layoutBuild();

}

void Window::layoutBuild(){

    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *display_layout = new QHBoxLayout;
    QHBoxLayout *control_layout = new QHBoxLayout;

    display_layout->addWidget(createTheLabel());
    display_layout->addWidget(createTheValue());

    previous_button = new QPushButton ("Previous", this);
    previous_button->setEnabled(false);
    control_layout->addWidget(previous_button);
    connect(previous_button, SIGNAL (released()), this, SLOT (HandleButtonPrevious()));

    pause_button = new QPushButton ("Pause", this);
    control_layout->addWidget(pause_button);
    connect(pause_button, SIGNAL (released()), this, SLOT (HandleButtonPause()));

    next_button = new QPushButton ("Next", this);
    next_button->setEnabled(false);
    control_layout->addWidget(next_button);
    connect(next_button, SIGNAL (released()), this, SLOT (HandleButtonNext()));

    main_layout->addLayout(display_layout);
    main_layout->addLayout(control_layout);

    setLayout(main_layout);

    setWindowTitle(tr("Boat Information"));
    resize(350, 300);




}


Window::~Window() {         //Destructor - I wont need this class anymore, so i will delete it
    inputFile.close();
}

std::vector<QString> Window::readLine(bool &atEnd){        //readLine() is a function, that the guys call METHOD, inside Window
    
    std::vector<QString> moments_storage;
    std::string temp_string;
    
    if (!stream.atEnd())
    {
        atEnd = false;
        std::string line = stream.readLine().toStdString();
        for (uint k1 = 0; k1 <= line.size(); ++k1) {        // each loop is a caracter
            
            if (k1 != line.size() && line.at(k1) != ',' ) {  //if the caracter is a number
                temp_string.push_back(line.at(k1));
            } else {
                moments_storage.push_back(QString::fromStdString(temp_string)); //if the caracter a comma or the end of the line
                temp_string.clear();
            }
        }
    }
    else
    {
        atEnd = true;
    }
    
    return moments_storage;
    
}

void Window::loadPoses()
{
    bool atEnd = false;
    while (!atEnd) {
        std::vector<QString> pose = readLine(atEnd);
        if (pose.size() == 6) {
            poses.push_back(pose);
        }
    }
}

QGroupBox* Window::createTheLabel()     // display the followings degrees of freedom labels
{
    QGroupBox *groupBox = new QGroupBox(tr("DOF"));

    QLabel *xPos = new QLabel(tr("X"));
    QLabel *yPos= new QLabel(tr("Y"));
    QLabel *zPos = new QLabel(tr("Z"));
    QLabel *roll = new QLabel(tr("Roll"));
    QLabel *pitch= new QLabel(tr("Pitch"));
    QLabel *yaw = new QLabel(tr("Yaw"));

    QLabel *currentFrame = new QLabel(tr("Frame: "));

    QVBoxLayout *vboxLabel = new QVBoxLayout;
    vboxLabel->addWidget(xPos);
    vboxLabel->addWidget(yPos);
    vboxLabel->addWidget(zPos);
    vboxLabel->addWidget(roll);
    vboxLabel->addWidget(pitch);
    vboxLabel->addWidget(yaw);
    vboxLabel->addWidget(currentFrame);
    vboxLabel->addStretch(1);
    groupBox->setLayout(vboxLabel);
    return groupBox;
}

QGroupBox* Window::createTheValue() // create the BOXES, which will be filled with  the values
{
    QGroupBox *groupBox = new QGroupBox(tr("Value"));

    xValue = new QLabel();
    yValue = new QLabel();
    zValue = new QLabel();
    rollValue = new QLabel();
    pitchValue = new QLabel();
    yawValue = new QLabel();
    currentFrame = new QLabel();

    QVBoxLayout *vboxValue = new QVBoxLayout;
    vboxValue->addWidget(xValue);
    vboxValue->addWidget(yValue);
    vboxValue->addWidget(zValue);
    vboxValue->addWidget(rollValue);
    vboxValue->addWidget(pitchValue);
    vboxValue->addWidget(yawValue);
    vboxValue->addWidget(currentFrame);
    vboxValue->addStretch(1);
    groupBox->setLayout(vboxValue);

    return groupBox;
}

void Window::timeout() {            // this is executed every time a second is elapsed, so each second corresponds to a line

//    if (places > 17){
//        places = 0;
//    }

    if (!isPaused)
    {
        s = std::to_string(places);

        if (places < poses.size()) {
            xValue->setText(poses[places][0]);
            yValue->setText(poses[places][1]);
            zValue->setText(poses[places][2]);
            rollValue->setText(poses[places][3]);
            pitchValue->setText(poses[places][4]);
            yawValue->setText(poses[places][5]);
            currentFrame->setText((QString::fromStdString(s)));
            places = places + 1;
        }
    }


//    if (places == 0){
//        places = 17;
//    }
}

void Window::HandleButtonPrevious()
{
    if (places == 0 )
        places = poses.size();

    places = places - 1;
    s = std::to_string(places);

    xValue->setText(poses[places][0]);
    yValue->setText(poses[places][1]);
    zValue->setText(poses[places][2]);
    rollValue->setText(poses[places][3]);
    pitchValue->setText(poses[places][4]);
    yawValue->setText(poses[places][5]);
    currentFrame->setText((QString::fromStdString(s)));

}

void Window::HandleButtonPause()
{
    isPaused = !isPaused;

    if (isPaused){
        places = places - 1;
        previous_button->setEnabled(true);
        next_button->setEnabled(true);
        pause_button->setText("Play again");

    } else{
        previous_button->setEnabled(false);
        next_button->setEnabled(false);
        pause_button->setText("Pause");
    }
}

void Window::HandleButtonNext()
{

    if (places == poses.size() - 1)
        places = -1;

    places = places + 1;
    s = std::to_string(places);

    xValue->setText(poses[places][0]);
    yValue->setText(poses[places][1]);
    zValue->setText(poses[places][2]);
    rollValue->setText(poses[places][3]);
    pitchValue->setText(poses[places][4]);
    yawValue->setText(poses[places][5]);
    currentFrame->setText((QString::fromStdString(s)));

}
