#ifndef AMAZONWORKER_H
#define AMAZONWORKER_H

#include "jsonworker.h"

using namespace std;

class AmazonWorker : public JsonWorker
{
public:
    AmazonWorker(QString inputPath, QString outputPath, QString bddName_);
    string parseData(QString line);
};

#endif // AMAZONWORKER_H
