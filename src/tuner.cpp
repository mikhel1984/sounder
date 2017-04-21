
#include "tuner.h"
#include "audioinfo.h"

Tuner::Tuner(QObject *parent)
    : QObject(parent)
    , deviceInfo(QAudioDeviceInfo::defaultInputDevice())
    , audioInfo(0)
    , audioInput(0)
    , _input(0)
    , buffer(BUFFER_SIZE, 0)
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

    // audio data analizator
    audioInfo = new AudioInfo(format, this);
    // connect signals...

    // create audio input
    audioInput = new QAudioInput(deviceInfo, format, this);
    audioInfo->start();
    audioInput->start(audioInfo);

}

Tuner::~Tuner() {
    if(audioInfo) delete audioInfo;
}

void Tuner::readMore() {
    if(!audioInput) return;

    qint64 len = audioInput->bytesReady();
    if(len > BUFFER_SIZE) len = BUFFER_SIZE;

    qint64 l = _input->read(buffer.data(), len);
    if(l > 0) audioInfo->write(buffer.constData(), l);
}
