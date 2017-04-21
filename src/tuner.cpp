
#include "tuner.h"
#include "audioinfo.h"

Tuner::Tuner(QObject *parent)
    : QObject(parent)
    , deviceInfo(QAudioDeviceInfo::defaultInputDevice())
    , audioInfo(0)
    , audioInput(0)
{
    // audio initialization
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if(!info.isFormatSupported(format)) {
        qDebug() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }

    qDebug() << "Rate: " << format.sampleRate();
    qDebug() << "Channels: " << format.channelCount();
    qDebug() << "Size: " << format.sampleSize();

    // audio data analizator
    audioInfo = new AudioInfo(format, this);
    connect(audioInfo, SIGNAL(update()), this, SLOT(retranslate()));

    // create audio input
    audioInput = new QAudioInput(deviceInfo, format, this);
    audioInfo->start();
    audioInput->start(audioInfo);

}

Tuner::~Tuner() {
    if(audioInfo) delete audioInfo;
}

void Tuner::retranslate() {
    emit noteChanged();
}


QString Tuner::getNote()     { return audioInfo->getNote(); }
int     Tuner::getShift()    { return audioInfo->getShift(); }
qreal   Tuner::getFrequency(){ return audioInfo->getFrequency(); }
