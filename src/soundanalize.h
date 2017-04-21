#ifndef SOUNDANALIZE_H
#define SOUNDANALIZE_H

#include <QString>
#include <QVector>


class SoundAnalize
{
    struct Sound {
        QString name;
        qreal   frequency;
        int     shift;

        Sound(QString n, qreal f, int sh) { name = n; frequency = f; shift = sh; }
    };

    struct Complex {
        qreal real;
        qreal image;
    };

public:
    SoundAnalize(int rate);
    ~SoundAnalize();

    QString getNote()       { return notes.at(lastNote)->name; }
    qreal   getFrequency()  { return notes.at(lastNote)->frequency; }
    int     getShift()      { return notes.at(lastNote)->shift; }

    void transform(qreal* data, unsigned n);

private:
    int sampleRate;
    int lastNote;

    Complex *arr;

    QVector<Sound*> notes;




    int  findMaximum();
};

#endif // SOUNDANALIZE_H
