#include "widget.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QPixmap>
#include <QCoreApplication>
#include <QFont>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 600);

    QFont font;
    font.setPointSize(18);

    labelCountdown = new QLabel(this);
    labelCountdown->setFont(font);
    labelCountdown->setAlignment(Qt::AlignCenter);

    labelPercent = new QLabel(this);
    labelPercent->setFont(font);
    labelPercent->setAlignment(Qt::AlignCenter);

    percentLabel = new QLabel(this);
    percentLabel->setFont(font);
    percentLabel->setAlignment(Qt::AlignCenter);

    // 相对路径处理
    QString resourceDir = QCoreApplication::applicationDirPath() + "/resources/";

    qDebug() << "图片路径:" << resourceDir + "589e3739474f834a7ced36d030883014.jpg";
    qDebug() << "视频路径:" << resourceDir + "mmexport1761618101928.mp4";

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    QPixmap pixmap(resourceDir + "589e3739474f834a7ced36d030883014.jpg");
    imageLabel->setPixmap(pixmap.scaled(600, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    videoWidget = new QVideoWidget(this);
    videoWidget->setFixedSize(600, 400);
    videoWidget->setVisible(false);

    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(1.0); // 最大音量
    mediaPlayer->setVideoOutput(videoWidget);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl::fromLocalFile(resourceDir + "mmexport1761618101928.mp4"));
    mediaPlayer->setLoops(QMediaPlayer::Infinite);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelCountdown);
    mainLayout->addWidget(labelPercent);
    mainLayout->addWidget(percentLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(videoWidget);
    setLayout(mainLayout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateCountdown);
    timer->start(1000);

    updateCountdown();
}

void Widget::updateCountdown()
{
    QDateTime target(QDate(2026, 2, 17), QTime(0, 0, 0));
    QDateTime now = QDateTime::currentDateTime();

    qint64 secsLeft = now.secsTo(target);
    int days = secsLeft / (24 * 3600);
    int hours = (secsLeft % (24 * 3600)) / 3600;
    int minutes = (secsLeft % 3600) / 60;
    int seconds = secsLeft % 60;

    QString countdownText;
    if (secsLeft > 0)
    {
        countdownText = QString("距离2026年过年还有：%1天 %2小时 %3分 %4秒")
                            .arg(days)
                            .arg(hours)
                            .arg(minutes)
                            .arg(seconds);
        imageLabel->setVisible(true);
        videoWidget->setVisible(false);
        mediaPlayer->stop();
    }
    else
    {
        countdownText = "刘德华已经解冻了！";
        imageLabel->setVisible(false);
        videoWidget->setVisible(true);
        if (mediaPlayer->playbackState() != QMediaPlayer::PlayingState)
            mediaPlayer->play();
    }
    labelCountdown->setText(countdownText);

    QDateTime start(QDate(2025, 1, 29), QTime(0, 0, 0));
    qint64 totalSecs = start.secsTo(target);
    qint64 passedSecs = start.secsTo(now);

    QString passedText;
    QString percentText;
    if (passedSecs < 0)
    {
        passedText = "还没到2025年过年！";
        percentText = "";
    }
    else if (passedSecs >= totalSecs)
    {
        passedText = "解冻进度100.000000%";
        percentText = "";
    }
    else
    {
        int p_days = passedSecs / (24 * 3600);
        int p_hours = (passedSecs % (24 * 3600)) / 3600;
        int p_minutes = (passedSecs % 3600) / 60;
        int p_seconds = passedSecs % 60;
        double percent = (double)passedSecs / totalSecs * 100.0;
        passedText = QString("距离2025年过年已经过去：%1天 %2小时 %3分 %4秒")
                         .arg(p_days)
                         .arg(p_hours)
                         .arg(p_minutes)
                         .arg(p_seconds);
        percentText = QString("刘德华解冻进度 %1%").arg(QString::number(percent, 'f', 6));
    }
    labelPercent->setText(passedText);
    percentLabel->setText(percentText);
}
