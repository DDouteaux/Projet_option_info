#include "rottenworker.h"

/**
 *  Constructeur pour le worker de Rotten Tomatoes.
 *  Ne fait rien mis à part prévenir l'utilisateur et déléguer la création
 *  attributs au constructeur hérité.
 *
 *  Params :
 *      - inputPath : chemin vers le fichier original à traiter.
 *      - outputPath : chemin vers le fichier de sortie de la BDD remaniée.
 *      - bddName_ : nom de la BDD étudiée.
 */
RottenWorker::RottenWorker(QString inputPath, QString outputPath, QString bddName_) : JsonWorker(inputPath, outputPath, bddName_){
    current_sentence = '0';
}

/**
 *  Parser associé à toute la base de données Rottent Tomatoes.
 *  Ce parser va aller chercher pour chaque phrase sa représentation
 *  d'un seul tenant ainsi que sa note et laisser tomber le découpage
 *  proposé dans le fichier.
 *
 *  Params :
 *      - line : une QString représentant la ligne à traiter.
 *
 *  Return :
 *      - La QString générée à partir de la ligne de BDD en entrée.
 *
 */
string RottenWorker::parseData(QString line){
    QStringList fields = line.split('\t');

    if(fields.at(1) == current_sentence || fields.at(1) == "SentenceId"){
        return (" ");
    } else {
        current_sentence = fields.at(1);
        int scoreDegrad = fields.at(3).toDouble() < 3.0 ? 0 : 1;
        QString scoreDegradS = QString::number(scoreDegrad);
        return ("\"" + fields.at(2).toStdString() + "\"\t" + scoreDegradS.toStdString() + "\t" + fields.at(3).toStdString() + "\t sentence\t" + this->bddName.toStdString());
    }
}
