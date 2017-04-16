#ifndef ROTTENWORKER_H
#define ROTTENWORKER_H

#include "jsonworker.h"
#include <QRegExp>

using namespace std;

class RottenWorker : public JsonWorker
{
public:
    RottenWorker(QString inputPath, QString outputPath, QString bddName_);
    string parseData(QString line);

    QString current_sentence;
};

#endif // ROTTENWORKER_H
