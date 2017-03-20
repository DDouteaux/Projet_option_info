#include "amazonworker.h"

/**
 *  Constructeur pour le worker d'Amazon.
 *  Ne fait rien mis à part prévenir l'utilisateur et déléguer la création
 *  attributs au constructeur hérité.
 *
 *  Params :
 *      - inputPath : chemin vers le fichier original à traiter.
 *      - outputPath : chemin vers le fichier de sortie de la BDD remaniée.
 *      - bddName_ : nom de la BDD étudiée.
 */
AmazonWorker::AmazonWorker(QString inputPath, QString outputPath, QString bddName_) : JsonWorker(inputPath, outputPath, bddName_){
}

/**
 *  Parser associé à toute la base de données Amazon. Ce parser va extraire de chaque
 *  objet Json passé en paramètre les informations suivantes :
 *      - Commentaire
 *      - Note dégradée (0 : négatif ; 1 : positif)
 *      - Note (de 0 (très négatif) à 5 (très positif)
 *      - Type de données (phrase ou paragraphe)
 *      - Nom BDD
 *
 *  Params :
 *      - line : une QString représentant la ligne à traiter.
 *
 *  Return :
 *      - La QString générée à partir de la ligne de BDD en entrée.
 *
 */
string AmazonWorker::parseData(QString line){
    QJsonDocument doc(QJsonDocument::fromJson(line.toUtf8()));
    QJsonObject json = doc.object();

    double score = json["overall"].toDouble();
    int scoreDegrad = score < 3.0 ? 0 : 1;
    QString scoreS = QString::number(score);
    QString scoreDegradS = QString::number(scoreDegrad);
    return ("\"" + json["reviewText"].toString().toStdString() + "\"\t" + scoreDegradS.toStdString() + "\t" + scoreS.toStdString() + "\t paragraph\t" + this->bddName.toStdString());
}
