#include "soundanalize.h"
#include <qmath.h>

#define NOTE_SIZE 45
#define EU_NOTES 12
#define THRESHOUDL 7
#define LIST_SIZE (3*NOTE_SIZE) // add upper and lower frequency shift for each note

#define Pi 3.1415926535897932384626433832795028

SoundAnalize::SoundAnalize(int rate) :
    sampleRate(rate),
    lastNote(0),
    arr(new Complex[LIST_SIZE])
{
    const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    notes.reserve(LIST_SIZE);

    // initial frequency
    qreal C2 = 65.41;
    // fill table
    for(int i = 0; i < NOTE_SIZE; ++i) {
        // central peak
        qreal freq = C2 * qPow(2.0, qreal(i)/EU_NOTES);
        int pos = i % EU_NOTES;
        // shift
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

// Fourier transformation
void SoundAnalize::transform(qreal *data, unsigned n) {

    qreal factor = 2 * Pi / sampleRate;
    // transformation
    for(int i = 0; i < notes.size(); ++i) {
        qreal freq = notes.at(i)->frequency;
        arr[i].image = arr[i].real = 0.0;        
        freq *= factor;
        for(unsigned t = 0; t < n; ++t) {            
            arr[i].real += data[t] * qCos(freq*t);
            arr[i].image += data[t] * qSin(freq*t);
        }
    }

    // note with maximum amplitude
    int index = findMaximum();
    if(index > -1) lastNote = index;
}

// get peak
int SoundAnalize::findMaximum() {
    qreal max = 0, amplituda, sum = 0;
    int res = 0;

    for(int i = 0; i < LIST_SIZE; ++i) {
        amplituda = arr[i].real*arr[i].real+arr[i].image*arr[i].image;
        if(amplituda > max) {
            max = amplituda;
            res = i;
        }
        sum += amplituda;
    }
    sum /= LIST_SIZE; // average value

    return max > THRESHOUDL*sum ? res : -1;
}



