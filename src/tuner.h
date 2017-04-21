#ifndef TUNER_H
#define TUNER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QByteArray>

class AudioInfo;

class Tuner : public QObject
{
    Q_OBJECT
public:
    explicit Tuner(QObject *parent = 0);
    ~Tuner();

    Q_INVOKABLE QString getNote();
    Q_INVOKABLE int     getShift();
    Q_INVOKABLE qreal   getFrequency();

private:
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;

    AudioInfo* audioInfo;
    QAudioInput* audioInput;
    QIODevice* _input;
    QByteArray buffer;


signals:

public slots:

private slots:
    void readMore();
};

#endif // TUNER_H
