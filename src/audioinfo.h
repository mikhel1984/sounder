#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QIODevice>
#include <QAudioFormat>
#include <QDebug>

#define BUFFER_SIZE 4096

class SoundAnalize;

// Class for extracting information from audio frame
class AudioInfo : public QIODevice
{
    Q_OBJECT
public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();    

    // getters
    qreal   level() const { return m_level; }
    QString getNote();
    int     getShift();
    qreal   getFrequency();

    // overloaded methods
    void start();
    void stop();
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    // local copy of audio format
    const QAudioFormat m_format;
    // volume paremeters
    quint16 m_maxAmplitude;
    qreal m_level;

    // buffer with data for Fourier transformation
    qreal *buffer;
    // object for Fourier transformation
    SoundAnalize* analizator;

signals:
    // analize is completed
    void update();
};

#endif // AUDIOINFO_H
