#ifndef SOUNDANALIZE_H
#define SOUNDANALIZE_H

#include <QString>
#include <QVector>

// Class perform Fourier transform and looking for correlation
class SoundAnalize
{
    // Note representation
    struct Sound {
        QString name;
        qreal   frequency;
        int     shift;      // 0 if equial, +/-1 if upper or lower

        Sound(QString n, qreal f, int sh) { name = n; frequency = f; shift = sh; }
    };

    // Complex number
    struct Complex {
        qreal real;
        qreal image;
    };

public:
    SoundAnalize(int rate);
    ~SoundAnalize();

    // read the parameters of note
    QString getNote()       { return notes.at(lastNote)->name; }
    qreal   getFrequency()  { return notes.at(lastNote)->frequency; }
    int     getShift()      { return notes.at(lastNote)->shift; }

    // Fourier transrormation of input data
    void transform(qreal* data, unsigned n);

private:    
    int sampleRate;        // sample frequency, Hz
    int lastNote;          // index of least note

    Complex *arr;          // spectr array

    QVector<Sound*> notes; // list of possible notes

    // searching maximum value
    int  findMaximum();
};

#endif // SOUNDANALIZE_H
