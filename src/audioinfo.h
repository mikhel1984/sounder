#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QIODevice>
#include <QAudioFormat>
#include <QDebug>

#define BUFFER_SIZE 4096

class SoundAnalize;

class AudioInfo : public QIODevice
{
    Q_OBJECT
public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

    QString getNote();
    int     getShift();
    qreal   getFrequency();


private:
    const QAudioFormat m_format;
    quint16 m_maxAmplitude;
    qreal m_level;

    qreal *buffer;

    SoundAnalize* analizator;

signals:
    void update();
};

#endif // AUDIOINFO_H
