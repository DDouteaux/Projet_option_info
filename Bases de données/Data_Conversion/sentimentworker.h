#ifndef SENTIMENTWORKER_H
#define SENTIMENTWORKER_H

#include "jsonworker.h"
#include <QRegExp>

using namespace std;

class SentimentWorker : public JsonWorker
{
public:
    SentimentWorker(QString inputPath, QString outputPath, QString bddName_);
    string parseData(QString line);
};

#endif // SENTIMENTWORKER_H
