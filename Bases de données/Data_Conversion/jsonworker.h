#ifndef JSONWORKER_H
#define JSONWORKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>
#include <QCoreApplication>

using namespace std;

class JsonWorker
{
public:
    JsonWorker(QString inputPath, QString outputPath, QString bddName_);
    QFile *inputFile;
    QFile *outputFile;
    QString bddName;

    virtual string parseData(QString line) { cout << "Methode generique" << endl; }
    bool launchWorker();

private:
    bool fileExists(QString path);
    void loadFile(QString path);
    void createOutputFile(QString path);
};

#endif // JSONWORKER_H
