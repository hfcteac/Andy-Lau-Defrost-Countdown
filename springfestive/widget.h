#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

private slots:
    void updateCountdown();

private:
    QTimer *timer;
    QLabel *labelCountdown;
    QLabel *labelPercent;
    QLabel *percentLabel;
    QLabel *imageLabel;
    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
};

#endif // WIDGET_H