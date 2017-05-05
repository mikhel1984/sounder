#ifndef TUNER_H
#define TUNER_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioInput>

class AudioInfo;

// Main class for audio processing
class Tuner : public QObject
{
    Q_OBJECT
    // note name
    Q_PROPERTY(QString note READ getNote NOTIFY noteChanged)
    // direction of tone shift from central note
    Q_PROPERTY(int shift READ getShift NOTIFY noteChanged)
    // given frequency
    Q_PROPERTY(qreal frequency READ getFrequency NOTIFY noteChanged)
    // sound level
    Q_PROPERTY(qreal level READ getLevel NOTIFY noteChanged)

public:
    explicit Tuner(QObject *parent = 0);
    ~Tuner();

    // getters
    QString getNote();
    int     getShift();
    qreal   getFrequency();
    qreal   getLevel();

private:
    // information about audio device
    QAudioDeviceInfo deviceInfo;
    // information about audio format
    QAudioFormat format;

    // sound analizer
    AudioInfo* audioInfo;
    // audio device
    QAudioInput* audioInput;

signals:
    void noteChanged();

private slots:
    // emitter for noteChanged()
    void retranslate();

};

#endif // TUNER_H
