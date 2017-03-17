#ifndef LARGEMOVIEWORKER_H
#define LARGEMOVIEWORKER_H

#include "jsonworker.h"

using namespace std;

class LargeMovieWorker : public JsonWorker
{
public:
    LargeMovieWorker(QString inputPath, QString outputPath, QString bddName_, QString lmrdPath, QString testPath, QString trainPath, QString negPath, QString posPath);
    void parseDirectory(QString dirPath, string scoreDegrad);
    bool launchWorker();

private:
    QString lmrdPath;
    QString testPath;
    QString trainPath;
    QString negPath;
    QString posPath;
};

#endif // LARGEMOVIEWORKER_H
