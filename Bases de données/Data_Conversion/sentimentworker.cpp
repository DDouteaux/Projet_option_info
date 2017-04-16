#include "sentimentworker.h"

/**
 *  Constructeur pour le worker de Sentiment Analysis Dataset.
 *  Ne fait rien mis à part prévenir l'utilisateur et déléguer la création
 *  attributs au constructeur hérité.
 *
 *  Params :
 *      - inputPath : chemin vers le fichier original à traiter.
 *      - outputPath : chemin vers le fichier de sortie de la BDD remaniée.
 *      - bddName_ : nom de la BDD étudiée.
 */
SentimentWorker::SentimentWorker(QString inputPath, QString outputPath, QString bddName_) : JsonWorker(inputPath, outputPath, bddName_){
}

/**
 *  Parser associé à toute la base de données Sentiment Analysis Dataset.
 *  Ce parser va transformer les arbres syntaxiques proposés dans le corps
 *  fichier en des couples (critique, note associée) au format présenté.
 *
 *  /!\ Le découpage est un peu violent, puisque l'on supprime toutes les
 *      parenthèses des phrases, ce qui peut en biaiser certaines (qui
 *      disposaient de "vraies" parenthèses. Cependant, dans la mesure où
 *      ces cas seront rares nous nous le permettons (toujours avec l'idée
 *      que cette BDD sera utilisée avec celle d'Amazon, donc les 10-15
 *      erreurs potentielles seront largement occultées!).
 *
 *  Params :
 *      - line : une QString représentant la ligne à traiter.
 *
 *  Return :
 *      - La QString générée à partir de la ligne de BDD en entrée.
 *
 */
string SentimentWorker::parseData(QString line){
    QString scoreS = line.at(1);
    line = line.remove(")").remove(QRegExp("[(][0-9][ ]"));

    double score = scoreS.toDouble();
    int scoreDegrad = score < 3.0 ? 0 : 1;
    QString scoreDegradS = QString::number(scoreDegrad);
    return ("\"" + line.toStdString() + "\"\t" + scoreDegradS.toStdString() + "\t" + scoreS.toStdString() + "\t sentence\t" + this->bddName.toStdString());
}
