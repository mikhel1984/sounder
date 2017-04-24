#include "soundanalize.h"
#include <qmath.h>

#define NOTE_SIZE 40
#define EU_NOTES 12
#define DEPTH 5

#define Pi 3.1415926535897932384626433832795028

SoundAnalize::SoundAnalize(int rate) :
    sampleRate(rate),
    lastNote(0),
    arr(new Complex[3*NOTE_SIZE])
{
    const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    notes.reserve(3*NOTE_SIZE);

    qreal C2 = 65.41;

    for(int i = 0; i < NOTE_SIZE; ++i) {
        qreal freq = C2 * qPow(2.0, qreal(i)/EU_NOTES);
        int pos = i % EU_NOTES;

        for(int j = -1; j <= 1; ++j) {
            notes.append(new Sound(QString(names[pos]), freq*qPow(2.0, qreal(j)/(4*EU_NOTES)), j));
        }
    }

}

SoundAnalize::~SoundAnalize() {
    for(int i = 0; i < notes.size(); ++i) {
        delete notes[i];
        notes[i] = NULL;
    }

    if(arr) delete [] arr;
}

void SoundAnalize::transform(qreal *data, unsigned n) {
    qreal factor = 2 * Pi / sampleRate;

    for(int i = 0; i < notes.size(); ++i) {
        qreal freq = notes.at(i)->frequency;
        arr[i].image = arr[i].real = 0.0;

        freq *= factor;
        for(unsigned t = 0; t < n; ++t) {            
            arr[i].real += data[t] * qCos(freq*t);
            arr[i].image += data[t] * qSin(freq*t);
        }
    }

    lastNote = findMaximum();

    //lastNote = smooth(lastNote);
}

int SoundAnalize::findMaximum() {
    qreal max = 0, amplituda;
    int res = 0;

    for(int i = 0; i < 3*NOTE_SIZE; ++i) {
        amplituda = arr[i].real*arr[i].real+arr[i].image*arr[i].image;
        if(amplituda > max) {
            max = amplituda;
            res = i;
        }
    }

    return res;
}
/*
int SoundAnalize::smooth(int val) {
    filter.enqueue(val);
    int f_size = filter.size();
    if(f_size > DEPTH) filter.dequeue();

    int sum = 0;
    foreach(int v, filter) {
        sum += v;
    }

    return int(sum / f_size);
}*/



