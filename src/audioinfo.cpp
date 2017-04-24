#include <QtCore/qendian.h>

#include "audioinfo.h"
#include "soundanalize.h"

#define NOIZE_LEVEL 0.05

AudioInfo::AudioInfo(const QAudioFormat &format, QObject *parent)
    :   QIODevice(parent)
    ,   m_format(format)
    ,   m_maxAmplitude(0)
    ,   m_level(0.0)
    ,   buffer(new qreal[BUFFER_SIZE])

{
    Q_ASSERT(m_format.sampleSize() % 8 == 0);
    channelBytes = m_format.sampleSize() / 8;
    sampleBytes = m_format.channelCount() * channelBytes;

    analizator = new SoundAnalize(m_format.sampleRate());

    switch (m_format.sampleSize()) {
    case 8:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 255;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 127;
            break;
        default:
            break;
        }
        break;
    case 16:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 65535;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 32767;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

AudioInfo::~AudioInfo()
{
    delete analizator;
    delete [] buffer;
}

void AudioInfo::start()
{
    open(QIODevice::ReadWrite);
}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}


qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    if (m_maxAmplitude) {

        Q_ASSERT(len % sampleBytes == 0);
        const int numSamples = len / sampleBytes;

        quint16 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

        for (int i = 0; i < numSamples; ++i) {
            for(int j = 0; j < m_format.channelCount(); ++j) {
                quint16 value = 0;

                if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    value = *reinterpret_cast<const quint8*>(ptr);
                    buffer[i] = qreal(value) / m_maxAmplitude;
                } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    value = qAbs(*reinterpret_cast<const qint8*>(ptr));
                    buffer[i] = qreal(*reinterpret_cast<const qint8*>(ptr)) / m_maxAmplitude;
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint16>(ptr);
                    else
                        value = qFromBigEndian<quint16>(ptr);
                    buffer[i] = qreal(value) / m_maxAmplitude;
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian) {
                        value = qAbs(qFromLittleEndian<qint16>(ptr));
                        buffer[i] = qreal(qFromLittleEndian<qint16>(ptr));
                    } else {
                        value = qAbs(qFromBigEndian<qint16>(ptr));
                        buffer[i] = qreal(qFromBigEndian<qint16>(ptr));
                    }
                }

                maxValue = qMax(value, maxValue);
                ptr += channelBytes;

            }
        }

        maxValue = qMin(maxValue, m_maxAmplitude);
        m_level = qreal(maxValue) / m_maxAmplitude;

        if(m_level > NOIZE_LEVEL)
            analizator->transform(buffer, numSamples);

    }


    emit update();
    return len;
}

QString AudioInfo::getNote()      { return analizator->getNote(); }
int     AudioInfo::getShift()     { return analizator->getShift(); }
qreal   AudioInfo::getFrequency() { return analizator->getFrequency(); }
