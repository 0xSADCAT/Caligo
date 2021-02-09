#ifndef CONTROLS_H
#define CONTROLS_H

#include <QtWidgets>
#include <QMediaPlayer>

#include <Widgets/timeslider.h>

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QMediaPlayer *mp, QWidget *parent = nullptr);

    void setSizes(int v);

    void setVolume(int v);
    int getVolume();

signals:
    void next();
    void prev();
    void settings();
    void about();
    void help();
    void fullScreen();

public slots:
    void playPause();
    void mute();
    void stop();

    void plusVol();
    void minusVol();

private:
    QMediaPlayer *player;

    TimeSlider *timeSlider;
    QLabel *posLabel;
    QLabel *durLabel;
    QHBoxLayout *topLayout;

    QPushButton *settingsButton;
    QPushButton *aboutButton;
    QPushButton *prevButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *nextButton;
    QPushButton *fullScreenButton;
    QPushButton *muteButton;
    QSlider *volumeSlider;
    QHBoxLayout *botLayout;

    QVBoxLayout *l;

private slots:
    void mediaState(QMediaPlayer::State s);
    void mutedState(bool v);

    void setDur(qint64 v);
    void setPos(qint64 v);

    QString msToStr(qint64 ms);

    void videoAvailable(bool v);
};

#endif // CONTROLS_H
