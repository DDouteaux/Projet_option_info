#include "largemovieworker.h"

/**
 *  Constructeur pour le worker de Large Movie Database.
 *  Ne fait rien mis à part prévenir l'utilisateur et déléguer la création
 *  attributs au constructeur hérité.
 *
 *  Params :
 *      - inputPath : chemin vers le fichier original à traiter --> ici vaudra "", car non utilisé.
 *      - outputPath : chemin vers le fichier de sortie de la BDD remaniée.
 *      - bddName_ : nom de la BDD étudiée.
 *      - lmrdPath : chemin vers la racine de cette BDD.
 *      - testPath : partie de chemin pour les répertoires de test.
 *      - trainPath : partie de chemin pour les répertoires d'apprentissage.
 *      - negPath : partie de chemin pour les répertoires d'avis négatifs.
 *      - posPath : partie de chemin pour les répertoires d'avis positifs.
 */
LargeMovieWorker::LargeMovieWorker(QString inputPath, QString outputPath, QString bddName_, QString lmrdPath, QString testPath, QString trainPath, QString negPath, QString posPath) : JsonWorker(inputPath, outputPath, bddName_){
    this->lmrdPath = lmrdPath;
    this->testPath = testPath;
    this->trainPath = trainPath;
    this->negPath = negPath;
    this->posPath = posPath;
}

/**
 *  Lancement du worker pour cette base de données. On sur-définie la version commune de
 *  JsonWorker, car les besoins sont ici particuliers
 *
 *  Params :
 *      - Aucun
 *
 *  Return :
 *      - True si tout s'est bien passé.
 */
bool LargeMovieWorker::launchWorker(){
    this->parseDirectory(this->lmrdPath + this->testPath + this->negPath, "0");
    this->parseDirectory(this->lmrdPath + this->testPath + this->posPath, "1");
    this->parseDirectory(this->lmrdPath + this->trainPath + this->negPath, "0");
    this->parseDirectory(this->lmrdPath + this->trainPath + this->posPath, "1");
    return true;
}

/**
 *  Fonction pour parser un répertoire en ouvrant et lisant chaque fichier du répertoire.
 *  Le besoin vient ici du fait que cette BDD soit éparpillée en répertoires de 12500 fichiers
 *  qu'il nous faut concaténer.
 *
 *  Params :
 *      - dirPath : le chemin du répertoire duquel on va lire tous les fichiers.
 *      - scoreDegrad : la valeur de score dégradée, dans la mesure où cette dernière
 *                      est directement fournie par les noms des répertoire (neg/pos).
 *
 *  Return :
 *      - Rien.
 */
void LargeMovieWorker::parseDirectory(QString dirPath, string scoreDegrad){
    cout << "INFO    : Lancement du scan de " << dirPath.toStdString() << "." << endl;

    // Récupération de la liste des fichiers du répertoire.
    QDir dir(dirPath);
    dir.setNameFilters(QStringList("*.txt"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    // Ouverture du flux vers le fichier de sortie.
    this->outputFile->open(QIODevice::Append | QIODevice::Text);
    QTextStream out(this->outputFile);
    out << "Comment\t RatingDegrad\t Rating\t TextType\t BDDName" << endl;

    // Parsing de chaque fichier à traiter dans le répertoire
    QStringList fileList = dir.entryList();
    for (int i=0; i<fileList.count(); i++){
        string score = fileList[i].toStdString().substr(fileList[i].toStdString().length()-5, 1);
        this->loadFile(dirPath + fileList[i]);
        if (this->inputFile->open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(this->inputFile);
            while(!in.atEnd()){
                string fileContent = this->removeSubstrs(in.readLine().toStdString(), string("<br />"));
                string newLine = "\"" + fileContent + "\"\t" + scoreDegrad + "\t" + score + "\t paragraph\t" + this->bddName.toStdString();
                out << QString::fromStdString(newLine) << endl;
            }
        }
    }

    // Nettoyage de l'espace de travail.
    this->outputFile->close();
    this->inputFile->close();
}
