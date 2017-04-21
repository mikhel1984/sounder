#ifndef TUNER_H
#define TUNER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioInput>

class AudioInfo;

class Tuner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString note READ getNote NOTIFY noteChanged)
    Q_PROPERTY(int shift READ getShift NOTIFY noteChanged)
    Q_PROPERTY(qreal frequency READ getFrequency NOTIFY noteChanged)

public:
    explicit Tuner(QObject *parent = 0);
    ~Tuner();

    QString getNote();
    int     getShift();
    qreal   getFrequency();

private:
    QAudioDeviceInfo deviceInfo;
    QAudioFormat format;

    AudioInfo* audioInfo;
    QAudioInput* audioInput;


signals:
    void noteChanged();

private slots:
    void retranslate();

};

#endif // TUNER_H
