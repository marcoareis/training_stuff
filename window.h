
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QTextStream>
#include <QPushButton>
#include <QFile>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT
    
private:
    QFile inputFile;
    QTextStream stream;
    
    //push buttons
    QPushButton *next_button;
    QPushButton *previous_button;
    QPushButton *pause_button;
    
    //Label values
    QLabel *xValue;
    QLabel *yValue;
    QLabel *zValue;
    QLabel *rollValue;
    QLabel *pitchValue;
    QLabel *yawValue;
    QLabel *currentFrame;
    //store the poses from file
    std::vector<std::vector<QString> > poses;

    uint places;
    std::string s;
    std::vector<QString> readLine(bool &atEnd);
    void loadPoses();
    void layoutBuild();
    
public slots:
    void timeout();
    
private slots:
    void HandleButtonNext();
    void HandleButtonPrevious();
    void HandleButtonPause();
    
public:
    QGroupBox *createTheLabel();
    QGroupBox *createTheValue();
    bool isPaused;
    bool myValue;

    explicit Window(QWidget *parent = 0);
    ~Window();
};

#endif
